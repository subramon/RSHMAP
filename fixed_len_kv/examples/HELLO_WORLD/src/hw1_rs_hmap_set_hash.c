#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "fasthash.h"
#include "rs_hmap_common.h"
#include "hw1_rs_hmap_struct.h"
#include "hw1_rs_hmap_set_hash.h"

//START_FUNC_DECL
uint32_t
hw1_rs_hmap_set_hash(
    const hw1_rs_hmap_key_t * const ptr_key,
    const hw1_rs_hmap_t     * const ptr_hmap
    )
//STOP_FUNC_DECL
{
  uint32_t hash;
    // hash = murmurhash3(key, len, ptr_hmap->hashkey);
  hash = fasthash32(ptr_key, sizeof(hw1_rs_hmap_key_t), ptr_hmap->hashkey);
  return hash;
}
