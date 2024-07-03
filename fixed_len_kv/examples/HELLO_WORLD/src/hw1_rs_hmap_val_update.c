#include "macros.h"
#include "hw1_rs_hmap_struct.h"
#include "hw1_rs_hmap_val_update.h"
//START_FUNC_DECL
int 
hw1_rs_hmap_val_update(
    hw1_rs_hmap_val_t *ptr_v1,
    const hw1_rs_hmap_val_t *const ptr_v2
    )
//STOP_FUNC_DECL
{
  int status = 0;
  if ( ptr_v1 == NULL )  { go_BYE(-1); }
  if ( ptr_v2 == NULL )  { go_BYE(-1); }
  hw1_rs_hmap_val_t v1 = *ptr_v1;
  hw1_rs_hmap_val_t v2 = *ptr_v2;
  *ptr_v1 = v1 + v2;
BYE:
  return status;
}
