#include <stdio.h>
#include <stdint.h>
#include "macros.h"
#include "hw1_rs_hmap_struct.h"
#include "hw1_rs_hmap_pr_val.h"

//START_FUNC_DECL
int 
hw1_rs_hmap_pr_val(
    hw1_rs_hmap_val_t *ptr_val,
    FILE *fp
    )
//STOP_FUNC_DECL
{
  int status = 0;
  if ( ptr_val == NULL ) { go_BYE(-1); } 
  fprintf(fp, "%u", *ptr_val);
BYE:
  return status;
}
