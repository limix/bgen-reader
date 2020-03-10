#ifndef BGEN_PARTITION_H_PRIVATE
#define BGEN_PARTITION_H_PRIVATE

#include "bgen/partition.h"

struct bgen_partition* bgen_partition_create(uint32_t npartition);
void                   bgen_partition_set(struct bgen_partition* partition, uint32_t index,
                                          struct bgen_vm const* variant_metadata);

#endif
