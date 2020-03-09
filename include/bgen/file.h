/** Open, close, and query bgen file.
 * @file bgen/file.h
 */
#ifndef BGEN_FILE_H
#define BGEN_FILE_H

#include "bgen/str.h"
#include "bgen_export.h"
#include <stdint.h>
#include <stdbool.h>

/** Bgen file handler.
 * @struct bgen_file
 */
struct bgen_file;

/** Open a file and return a bgen file handler.
 *
 * Remember to call @ref bgen_close to close the file and release
 * resources after the interaction has finished.
 *
 * @param filepath File path to the bgen file.
 * @return Bgen file handler.
 */
BGEN_EXPORT struct bgen_file* bgen_file_open(char const* filepath);
/** Close a bgen file handler.
 *
 * @param bgen Bgen file handler.
 */
BGEN_EXPORT void bgen_file_close(struct bgen_file* bgen);
/** Get the number of samples.
 *
 * @param bgen Bgen file handler.
 * @return Number of samples.
 */
BGEN_EXPORT uint32_t bgen_file_nsamples(struct bgen_file const* bgen);
/** Get the number of variants.
 *
 * @param bgen Bgen file handler.
 * @return Number of variants.
 */
BGEN_EXPORT uint32_t bgen_file_nvariants(struct bgen_file const* bgen);
/** Check if the file contain sample identifications.
 *
 * \rst
 * .. seealso::
 *     Please, refer to the |bgen format specification| for more details.
 * \endrst
 *
 * @param bgen Bgen file handler.
 * @return `1` if bgen file contains the sample ids; `0` otherwise.
 */
BGEN_EXPORT bool bgen_contain_samples(struct bgen_file const* bgen);
/** Return array of sample identifications.
 *
 * The size of this array is given be the @ref bgen_nsamples function.
 *
 * @param bgen Bgen file handler.
 * @param verbose `1` to show progress; `0` otherwise.
 * @return Array of sample ids.
 */
BGEN_EXPORT struct bgen_str* bgen_read_samples(struct bgen_file* bgen, int verbose);
/** Free array of sample identifications.
 *
 * @param bgen Bgen file handler.
 * @param sample_ids Array of sample ids.
 */
BGEN_EXPORT void bgen_free_samples(struct bgen_file const* bgen, struct bgen_str* sample_ids);

#endif
