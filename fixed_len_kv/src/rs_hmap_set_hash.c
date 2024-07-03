// Default implementation. User is allowed to over-ride
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "fasthash.h"
#include "rs_hmap_common.h"
#include "__TMPL___rs_hmap_struct.h"
#include "__TMPL___rs_hmap_set_hash.h"

//START_FUNC_DECL
uint32_t
__TMPL___rs_hmap_set_hash(
    const void * const in_ptr_key,
    const void * const in_ptr_hmap
    )
//STOP_FUNC_DECL
{
  uint32_t hash;
  const __TMPL___rs_hmap_key_t * const ptr_key = 
    (const __TMPL___rs_hmap_key_t * const) in_ptr_key;
  const __TMPL___rs_hmap_t * const ptr_hmap = 
    (const __TMPL___rs_hmap_t * const) in_ptr_hmap;
    // hash = murmurhash3(key, len, ptr_hmap->hashkey);
  hash = fasthash32(ptr_key, sizeof(__TMPL___rs_hmap_key_t), ptr_hmap->hashkey);
  return hash;
}
