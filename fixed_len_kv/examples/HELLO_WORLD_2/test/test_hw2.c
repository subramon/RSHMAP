#include "rs_hmap_common.h"
#include "hw2_rs_hmap_struct.h"
#include "hw2_rs_hmap_instantiate.h"
#include "hw2_rs_hmap_chk.h"
#include "hw2_rs_hmap_get.h"
#include "hw2_rs_hmap_put.h"
#include "hw2_rs_hmap_pr.h"
#include "hw2_rs_hmap_del.h"
#include "hw2_rs_hmap_destroy.h"

int
main(
    int argc,
    char **argv
    )
{
  int status = 0;
  FILE *fp = NULL;
  int num_iterations = 8; 
  hw2_rs_hmap_t H;
  //---------------------------
  rs_hmap_config_t HC; memset(&HC, 0, sizeof(rs_hmap_config_t));
  if ( argc != 1 ) { go_BYE(-1); }
  HC.min_size = 32;
  HC.max_size = 0;
  status = hw2_rs_hmap_instantiate(&H, &HC); cBYE(status);
  //-----------------------------------------------------------
  hw2_rs_hmap_val_t chk_val; 
  memset(&chk_val, 0, sizeof(hw2_rs_hmap_val_t));
  chk_val.i8 = 0;

  uint32_t nitems = 1048576;
  // The keys we create are 
  // (1*1, 0, 100*1, 10*1)
  // (1*2, 0, 100*2, 10*2)
  // We use the same value for all keys.
  // In iteration 0, val is ((i+1, key_1, 0))
  // In iteration 1, val is ((i+1, key_2, 0))

  for ( int iter = 0; iter < num_iterations; iter++ ) {
    printf("Put Iter = %d \n", iter);
    // set the val
    hw2_rs_hmap_val_t val;
    memset(&val, 0, sizeof(hw2_rs_hmap_val_t));
    val.i8 = iter+1;
    val.i1 = 0;
    sprintf(val.str, "[str_val_%" PRIu64 "]", val.i8);

    // set the value we will check against
    chk_val.i8 += val.i8;
    chk_val.i1 += 0;
    sprintf(chk_val.str, "[str_val_%" PRIu64 "]", val.i8);
    bool is_found; uint32_t where_found;
    for ( uint32_t i = 0; i < nitems; i++ ) {
      // set the key 
      hw2_rs_hmap_key_t key;
      memset(&key, 0, sizeof(hw2_rs_hmap_key_t));
      key.f8 = (i+1)*1; 
      key.ui2 = 0;
      key.f4 = (i+1)*100; 
      key.i4 = (i+1)*10; 
      //--------------------------------------
      status = hw2_rs_hmap_put(&H, &key, &val); cBYE(status);
      if ( iter == 0 ) { 
        if ( H.nitems != (i+1) ) { go_BYE(-1); } 
      }
      else { 
        if ( H.nitems != nitems ) { go_BYE(-1); }
      }
      hw2_rs_hmap_val_t curr_val;
      memset(&curr_val, 0, sizeof(hw2_rs_hmap_val_t));
      status = hw2_rs_hmap_get(&H, &key, &curr_val, &is_found, &where_found);
      cBYE(status);
      if ( !is_found ) { go_BYE(-1); }
      // because of the way val_update() is defined, we assert
      if ( chk_val.i8 != curr_val.i8 ) { go_BYE(-1); }
      if ( chk_val.i1 != curr_val.i1 ) { go_BYE(-1); }
      if ( strcmp(chk_val.str,  curr_val.str) != 0 ) { go_BYE(-1); }
      //------------------------------
    }
    status = hw2_rs_hmap_chk(&H); cBYE(status); 
  }
  //--------------------------------------------------
  // The following works only for this particular Key/Val updates
  uint32_t chk_n1 = 0, chk_n2 = 0;
  for ( uint32_t i = 0; i < H.size; i++ ) { 
    hw2_rs_hmap_bkt_t *bkts = H.bkts;
    bool *bkt_full = H.bkt_full;
    if ( bkts[i].key.f4 != 0 ) { chk_n1++; }
    if ( bkts[i].val.i8 != 0 ) { chk_n2++; }
    if ( bkt_full[i] ) { 
      if ( bkts[i].key.f4 == 0 ) { 
        go_BYE(-1); }
      if ( bkts[i].val.i8 == 0 ) { go_BYE(-1); }
    }
    else {
      if ( bkts[i].key.f4 != 0 ) { go_BYE(-1); }
      if ( bkts[i].val.i8 != 0 ) { go_BYE(-1); }
    }
  }
  if ( chk_n1 != H.nitems ) { go_BYE(-1); }
  if ( chk_n2 != H.nitems ) { go_BYE(-1); }
  //--------------------------------------------------
  // Print hashmap to a  file 
  fp = fopen("_hashmap.csv", "w");
  return_if_fopen_failed(fp, "_hashmap.csv", "w");
  status = hw2_rs_hmap_pr(&H, fp); cBYE(status);
  // Now delete the items one by one 
  // All items have the same value: let us determine what it is 
  int8_t  chk_val_i1 = 0;
  int64_t chk_val_i8 = 0;
  for ( int iter = 0; iter < num_iterations; iter++ ) { 
    chk_val_i8 += iter+1;
  }
  uint32_t chk_nitems = nitems; 
  printf("Del Iter 1 \n");
  for ( uint32_t i = 0; i < nitems; i++ ) {
    bool is_found;
    // set the key 
    hw2_rs_hmap_key_t key;
    memset(&key, 0, sizeof(hw2_rs_hmap_key_t));
    key.f8 = (i+1)*1; 
    key.ui2 = 0;
    key.f4 = (i+1)*100; 
    key.i4 = (i+1)*10; 

    hw2_rs_hmap_val_t chk_val; 
    memset(&chk_val, 0, sizeof(hw2_rs_hmap_val_t));
    status = hw2_rs_hmap_del(&H, &key, &chk_val, &is_found); cBYE(status);
    if ( !is_found ) { go_BYE(-1); }
    if ( chk_val.i8 != chk_val_i8 ) { go_BYE(-1); }
    if ( chk_val.i1 != chk_val_i1 ) { go_BYE(-1); }
    chk_nitems--; 
    if ( H.nitems != chk_nitems ) { go_BYE(-1); } 
    // delete again just for kicks 
    memset(&chk_val, 0, sizeof(hw2_rs_hmap_val_t)); 
    status = hw2_rs_hmap_del(&H, &key, &chk_val, &is_found); cBYE(status);
    if ( is_found ) { go_BYE(-1); }
    if ( chk_val.i8 != 0 ) { go_BYE(-1); }
  }
  if ( H.nitems != 0 ) { go_BYE(-1); } 
  status = hw2_rs_hmap_chk(&H); cBYE(status); 
  // Now delete items again. Should have no impact 
  printf("Del Iter 2 \n");
  for ( uint32_t i = 0; i < nitems; i++ ) {
    bool is_found;
    hw2_rs_hmap_key_t key;
    memset(&key, 0, sizeof(hw2_rs_hmap_key_t));
    key.f4 = (i+1)*10; 
    hw2_rs_hmap_val_t chk_val; 
    memset(&chk_val, 0, sizeof(hw2_rs_hmap_val_t)); 
    status = hw2_rs_hmap_del(&H, &key, &chk_val, &is_found); cBYE(status);
    if ( is_found ) { go_BYE(-1); }
    if ( chk_val.i8 != 0 ) { go_BYE(-1); }
    if ( H.nitems != 0 ) { go_BYE(-1); } 
  }
  //--------------------------------------------------

  printf("hmap occupancy = %d \n", H.nitems);
  printf("hmap size      = %d \n", H.size);
  hw2_rs_hmap_destroy(&H); 
  fprintf(stderr, "Unit test succeeded\n");
BYE:
  fclose_if_non_null(fp);
  if ( status == 0 ) { printf("Success on %s \n", argv[0]); }
  return status;
}
