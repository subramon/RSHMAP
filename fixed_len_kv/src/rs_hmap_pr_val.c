// Default implementation. User is expected to over-ride
#include <stdio.h>
#include "macros.h"
#include "__TMPL___rs_hmap_struct.h"
#include "__TMPL___rs_hmap_pr_val.h"

//START_FUNC_DECL
int
__TMPL___rs_hmap_pr_val(
    const __TMPL___rs_hmap_val_t * const ptr_val,
    FILE *fp
    )
//STOP_FUNC_DECL
{
  int status = 0;
  if ( ptr_val == NULL )  { go_BYE(-1); }
  fprintf(fp, "val");
BYE:
  return status;
}
