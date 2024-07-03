#include "hw2_rs_hmap_struct.h"
#include "hw2_rs_hmap_key_cmp.h"
//START_FUNC_DECL
bool
hw2_rs_hmap_key_cmp(
    const hw2_rs_hmap_key_t *const ptr_k1,
    const hw2_rs_hmap_key_t *const ptr_k2
    )
//STOP_FUNC_DECL
{
  if ( ptr_k1->f8 != ptr_k2->f8 ) { return false; }
  if ( ptr_k1->ui2 != ptr_k2->ui2 ) { return false; }
  if ( ptr_k1->f4 != ptr_k2->f4 ) { return false; }
  if ( ptr_k1->i4 != ptr_k2->i4 ) { return false; }
  return true; 
}
