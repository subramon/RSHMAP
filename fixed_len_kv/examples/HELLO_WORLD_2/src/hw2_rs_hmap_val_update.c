#include <string.h>
#include "macros.h"
#include "hw2_rs_hmap_struct.h"
#include "hw2_rs_hmap_val_update.h"
//START_FUNC_DECL
int 
hw2_rs_hmap_val_update(
    hw2_rs_hmap_val_t *ptr_v1,
    const hw2_rs_hmap_val_t *const ptr_v2
    )
//STOP_FUNC_DECL
{
  int status = 0;
  if ( ptr_v1 == NULL )  { go_BYE(-1); }
  if ( ptr_v2 == NULL )  { go_BYE(-1); }
  ptr_v1->i8 += ptr_v2->i8;
  ptr_v1->str[16-1] = '\0'; // null terminate 
  strncpy(ptr_v1->str, ptr_v2->str, 16-1); 
  ptr_v1->i1 = ptr_v2->i1;
BYE:
  return status;
}
