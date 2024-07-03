#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "macros.h"
#include "hw1_rs_hmap_struct.h"
#include "hw1_rs_hmap_pr_key.h"

//START_FUNC_DECL
int
hw1_rs_hmap_pr_key(
    hw1_rs_hmap_key_t *ptr_key,
    FILE *fp
    )
//STOP_FUNC_DECL
{
  int status = 0;
  if ( ptr_key == NULL ) { go_BYE(-1); } 
  fprintf(fp, "%" PRIu64, *ptr_key);
BYE:
  return status;
}
