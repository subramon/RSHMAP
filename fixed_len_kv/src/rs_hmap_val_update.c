#include <string.h>
#include "macros.h"
#include "__TMPL___rs_hmap_struct.h"
#include "__TMPL___rs_hmap_val_update.h"
//START_FUNC_DECL
int 
__TMPL___rs_hmap_val_update(
    __TMPL___rs_hmap_val_t *ptr_v1,
    const __TMPL___rs_hmap_val_t *const ptr_v2
    )
//STOP_FUNC_DECL
{
  int status = 0;
  if ( ptr_v1 == NULL )  { go_BYE(-1); }
  if ( ptr_v2 == NULL )  { go_BYE(-1); }
  memcpy(ptr_v1, ptr_v2, sizeof(__TMPL___rs_hmap_val_t));
BYE:
  return status;
}
