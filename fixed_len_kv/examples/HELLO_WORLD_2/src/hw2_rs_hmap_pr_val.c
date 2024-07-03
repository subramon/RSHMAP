#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "macros.h"
#include "hw2_rs_hmap_struct.h"
#include "hw2_rs_hmap_pr_val.h"

//START_FUNC_DECL
int
hw2_rs_hmap_pr_val(
    hw2_rs_hmap_val_t *ptr_val,
    FILE *fp
    )
//STOP_FUNC_DECL
{
  int status = 0;
  if ( ptr_val == NULL ) { go_BYE(-1); } 
  fprintf(fp, "(%ld,%s,%d)",
      ptr_val->i8,
      ptr_val->str,
      ptr_val->i1
      );
BYE:
  return status;
}
