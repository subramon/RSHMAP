// EXTERNAL EXPOSURE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "macros.h"
#include "hw1_rs_hmap_struct.h"
#include "hw1_rs_hmap_pr_key.h"
#include "hw1_rs_hmap_pr_val.h"
#include "hw1_rs_hmap_pr.h"
//START_FUNC_DECL
int
hw1_rs_hmap_pr(
    hw1_rs_hmap_t *ptr_hmap,
    FILE *fp
    )
//STOP_FUNC_DECL
{
  int status = 0;
  hw1_rs_hmap_bkt_t *bkts = ptr_hmap->bkts;
  bool *bkt_full = ptr_hmap->bkt_full;

  for ( uint32_t i = 0; i < ptr_hmap->size; i++ ) { 
    if ( !bkt_full[i] ) { continue; }
    fprintf(fp, "%u,", i); // print index just for fun
    status = hw1_rs_hmap_pr_key(&(bkts[i].key), fp);  cBYE(status);
    fprintf(fp, ",");
    status = hw1_rs_hmap_pr_val(&(bkts[i].val), fp);  cBYE(status);
    fprintf(fp, "\n");
  }
BYE:
  return status;
}
