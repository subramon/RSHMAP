#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "macros.h"
#include "hw2_rs_hmap_struct.h"
#include "hw2_rs_hmap_pr_key.h"

//START_FUNC_DECL
int
hw2_rs_hmap_pr_key(
    hw2_rs_hmap_key_t *ptr_key,
    FILE *fp
    )
//STOP_FUNC_DECL
{
  int status = 0;
  if ( ptr_key == NULL ) { go_BYE(-1); } 
  fprintf(fp, "(%lf,%u,%f,%d)", 
      ptr_key->f8,
      ptr_key->ui2,
      ptr_key->f4,
      ptr_key->i4
      );
BYE:
  return status;
}
