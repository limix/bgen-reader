#include "file.h"
#include "athr.h"
#include "bgen/file.h"
#include "free.h"
#include "genotype.h"
#include "io.h"
#include "layout1.h"
#include "layout2.h"
#include "report.h"
#include "samples.h"
#include "str.h"
#include <inttypes.h>
#include <stdbool.h>

struct bgen_file
{
    char*    filepath;
    FILE*    stream;
    uint32_t nvariants;
    uint32_t nsamples;
    unsigned compression;
    unsigned layout;
    bool     contain_sample;
    OFF_T    samples_start;
    OFF_T    variants_start;
};

static int read_bgen_header(struct bgen_file* bgen);

struct bgen_file* bgen_file_open(char const* filepath)
{
    struct bgen_file* bgen = malloc(sizeof(struct bgen_file));
    bgen->filepath = strdup(filepath);

    if (!(bgen->stream = fopen(bgen->filepath, "rb"))) {
        bgen_perror("could not open bgen file %s", bgen->filepath);
        goto err;
    }

    if (fread_off(bgen->stream, &bgen->variants_start, 4)) {
        bgen_error("could not read the `variants_start` field");
        goto err;
    }

    bgen->variants_start += 4;

    if (read_bgen_header(bgen)) {
        bgen_error("could not read bgen header");
        goto err;
    }

    /* if they actually exist */
    bgen->samples_start = LONG_TELL(bgen->stream);

    return bgen;
err:
    bgen_file_close(bgen);
    return NULL;
}

void bgen_file_close(struct bgen_file* bgen)
{
    if (bgen->stream != NULL && fclose(bgen->stream))
        bgen_perror("could not close %s file", bgen->filepath);
    free_c(bgen->filepath);
    free_c(bgen);
}

uint32_t bgen_file_nsamples(struct bgen_file const* bgen) { return bgen->nsamples; }

uint32_t bgen_file_nvariants(struct bgen_file const* bgen) { return bgen->nvariants; }

bool bgen_file_contain_samples(struct bgen_file const* bgen) { return bgen->contain_sample; }

struct bgen_samples* bgen_file_read_samples(struct bgen_file* bgen, int verbose)
{
    struct athr* at = NULL;

    LONG_SEEK(bgen->stream, bgen->samples_start, SEEK_SET);

    if (!bgen->contain_sample) {
        bgen_warning("file does not contain sample ids");
        return NULL;
    }

    struct bgen_samples* samples = bgen_samples_create(bgen->nsamples);

    if (LONG_SEEK(bgen->stream, 8, SEEK_CUR)) {
        bgen_perror("could not fseek eight bytes forward");
        goto err;
    }

    if (verbose) {
        at = athr_create(bgen->nsamples, "Reading samples", ATHR_BAR);
        if (!at) {
            bgen_error("could not create a progress bar");
            goto err;
        }
    }

    for (uint32_t i = 0; i < bgen->nsamples; ++i) {
        if (verbose)
            athr_consume(at, 1);

        struct bgen_str const* sample_id = bgen_str_fread(bgen->stream, 2);
        if (sample_id == NULL) {
            bgen_error("could not read the %" PRIu32 "lu-th sample id", i);
            goto err;
        }
        bgen_samples_set(samples, i, sample_id);
    }

    if (verbose)
        athr_finish(at);

    bgen->variants_start = LONG_TELL(bgen->stream);
    return samples;

err:
    if (at)
        athr_finish(at);
    bgen_samples_free(samples);
    return NULL;
}

struct bgen_genotype* bgen_file_open_genotype(struct bgen_file const* bgen,
                                              uint64_t const          offset)
{
    struct bgen_genotype* vg = create_vg();
    vg->layout = bgen->layout;
    vg->offset = offset;

    if (offset > OFF_T_MAX)
        bgen_die("offset overflow");

    if (LONG_SEEK(bgen_file_stream(bgen), (OFF_T)offset, SEEK_SET)) {
        bgen_perror("could not seek a variant in %s", bgen_file_filepath(bgen));
        free_c(vg);
        return NULL;
    }

    struct bgen_vi vi = BGEN_VI(bgen);

    if (bgen_file_layout(bgen) == 1) {
        bgen_layout1_read_header(&vi, vg, bgen_file_stream(bgen));
    } else if (bgen_file_layout(bgen) == 2) {
        bgen_layout2_read_header(&vi, vg, bgen_file_stream(bgen));
    } else {
        bgen_error("unrecognized layout type %d", bgen_file_layout(bgen));
        free_c(vg);
        return NULL;
    }

    return vg;
}

FILE* bgen_file_stream(struct bgen_file const* bgen_file) { return bgen_file->stream; }

char const* bgen_file_filepath(struct bgen_file const* bgen_file)
{
    return bgen_file->filepath;
}

unsigned bgen_file_layout(struct bgen_file const* bgen_file) { return bgen_file->layout; }

unsigned bgen_file_compression(struct bgen_file const* bgen_file)
{
    return bgen_file->compression;
}

int bgen_file_seek_variants_start(struct bgen_file* bgen_file)
{
    if (LONG_SEEK(bgen_file->stream, bgen_file->variants_start, SEEK_SET)) {
        bgen_perror("could not jump to the variants start");
        return 1;
    }
    return 0;
}

/*
 * Read the header block defined as follows:
 *
 *   header length: 4 bytes
 *   number of variants: 4 bytes
 *   number of samples: 4 bytes
 *   magic number: 4 bytes
 *   unused space: header length minus 20 bytes
 *   bgen flags: 4 bytes
 */
static int read_bgen_header(struct bgen_file* bgen)
{
    uint32_t header_length;
    uint32_t magic_number;
    uint32_t flags;

    if (fread_ui32(bgen->stream, &header_length, 4)) {
        bgen_error("could not read the header length");
        return 1;
    }

    if (fread_ui32(bgen->stream, &bgen->nvariants, 4)) {
        bgen_error("could not read the number of variants");
        return 1;
    }

    if (fread_ui32(bgen->stream, &bgen->nsamples, 4)) {
        bgen_error("could not read the number of samples");
        return 1;
    }

    if (fread_ui32(bgen->stream, &magic_number, 4)) {
        bgen_error("could not read the magic number");
        return 1;
    }

    if (magic_number != 1852139362)
        bgen_warning("magic number mismatch");

    if (LONG_SEEK(bgen->stream, header_length - 20, SEEK_CUR)) {
        bgen_error("fseek error while reading a BGEN file");
        return 1;
    }

    if (fread_ui32(bgen->stream, &flags, 4)) {
        bgen_error("could not read the bgen flags");
        return 1;
    }

    bgen->compression = flags & 3;
    bgen->layout = (flags & (15 << 2)) >> 2;
    bgen->contain_sample = ((flags & ((uint32_t)1 << 31)) >> 31) == 1;

    return 0;
}
