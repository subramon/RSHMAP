// Default implementation. User is expected to over-ride
#include <stdio.h>
#include "macros.h"
#include "__TMPL___rs_hmap_struct.h"
#include "__TMPL___rs_hmap_pr_key.h"

//START_FUNC_DECL
int
__TMPL___rs_hmap_pr_key(
    const __TMPL___rs_hmap_key_t * const ptr_key,
    FILE *fp
    )
//STOP_FUNC_DECL
{
  int status = 0;
  if ( ptr_key == NULL ) { go_BYE(-1); }
  fprintf(fp, "key");
BYE:
  return status;
}
