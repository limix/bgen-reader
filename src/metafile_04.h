/** Create and query a metafile.
 * @file bgen/metafile_04.h
 *
 * A bgen metafile is defined as follows:
 *
 * [ char[13] : signature (e.g. "bgen index 04") ], \
 * [ uint32_t : number of variants ],               | Header block
 * [ uint32_t : number of partitions ],             /
 * [                                                \
 *   [                                              |
 *     uint64_t : partition offset (this file)      | Offsets block
 *   ], ...                                         |
 * ]                                                /
 * [                                                \
 *   uint64_t        : genotype offset (bgen file)  |
 *   uint16_t, str,  : variant id                   |
 *   uint16_t, str,  : variant rsid                 |
 *   uint16_t, str,  : variant chrom                |
 *   uint32_t,       : genetic position             | Metadata block
 *   uint16_t,       : number of alleles            |
 *   [                                              |
 *     uint32_t, str : allele id                    |
 *   ], ...                                         |
 * ], ...                                           /
 *
 * Version 04.
 */
#ifndef BGEN_METAFILE_04_H_PRIVATE
#define BGEN_METAFILE_04_H_PRIVATE

#include <inttypes.h>
#include <stdio.h>

#define BGEN_METAFILE_04_SIGNATURE "bgen index 04"
#define BGEN_METAFILE_04_HEADER_SIZE (13 + 4 + 4)

struct bgen_metafile_04
{
    char*     filepath;
    FILE*     stream;
    uint32_t  nvariants;
    uint32_t  npartitions;
    uint64_t* partition_offset; /**< Array of partition offsets */
};

uint32_t bgen_metafile_04_partition_size(uint32_t nvariants, uint32_t npartitions);

#endif
