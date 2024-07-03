#include "hw1_rs_hmap_struct.h"
#include "hw1_rs_hmap_key_cmp.h"
//START_FUNC_DECL
bool
hw1_rs_hmap_key_cmp(
    const hw1_rs_hmap_key_t *const ptr_k1,
    const hw1_rs_hmap_key_t *const ptr_k2
    )
//STOP_FUNC_DECL
{
  if ( *ptr_k1 == *ptr_k2 ) { return true; } else { return false; }
}
