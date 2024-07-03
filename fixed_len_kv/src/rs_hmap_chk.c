// EXTERNAL EXPOSURE
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "macros.h"
#include "rdtsc.h"
#include "spooky_struct.h"
#include "spooky_hash.h"
#include "set_probe_loc.h"
#include "__TMPL___rs_hmap_struct.h"
#include "__TMPL___rs_hmap_set_hash.h"
#include "__TMPL___rs_hmap_key_cmp.h"
#include "__TMPL___rs_hmap_get.h"
#include "__TMPL___rs_hmap_chk.h"

typedef struct _chk_t { 
  uint32_t idx;
  uint64_t hash;
} chk_t; 

static int
sortcompare_UI64(
    const void *in1,
    const void *in2
    )
{
  const chk_t  *u1 = (const chk_t *)in1;
  const chk_t  *u2 = (const chk_t *)in2;
  uint64_t h1 = u1->hash;
  uint64_t h2 = u2->hash;
  if ( h1 < h2 ) {
    return -1;
  }
  else {
    return 1;
  }
}

//-----------------------------------------------------
//START_FUNC_DECL
int
__TMPL___rs_hmap_chk(
    __TMPL___rs_hmap_t *ptr_hmap
    )
//STOP_FUNC_DECL
{
  int status = 0;
  chk_t *hashes = NULL;
  // status = hmap_pr(ptr_hmap); cBYE(status);
  // check that number of items is correct
  uint32_t chk_nitems = 0;
  __TMPL___rs_hmap_bkt_t *bkts = ptr_hmap->bkts;
  bool *bkt_full = ptr_hmap->bkt_full;
  for ( uint32_t i = 0; i < ptr_hmap->size; i++ ) { 
    if ( bkt_full[i] ) {
      chk_nitems++;
    }
  }
  if ( ptr_hmap->nitems != chk_nitems ) { go_BYE(-1); }
  // check that (the hash of) each key is unique 
  hashes = malloc(chk_nitems * sizeof(chk_t));
  return_if_malloc_failed(hashes);
  memset(hashes, 0, chk_nitems * sizeof(chk_t));
  uint32_t hash_cnt = 0;
  uint64_t seed = RDTSC() ^ random();
  for ( uint32_t i = 0; i < ptr_hmap->size; i++ ) { 
    if ( bkt_full[i] ) {
     if ( hash_cnt >= chk_nitems ) { go_BYE(-1); }
      hashes[hash_cnt].hash = spooky_hash64(
          &(bkts[i].key), sizeof(__TMPL___rs_hmap_key_t), seed);
      hashes[hash_cnt].idx = i;
      hash_cnt++;
    }
  }
  if ( hash_cnt != chk_nitems ) { go_BYE(-1); }
  if ( chk_nitems < 2048 ) {  // do a dumb O(n^2) comparison of keys
    for ( uint32_t i = 0; i < chk_nitems; i++ ) { 
    if ( !bkt_full[i] ) { continue; }
      for ( uint32_t j = i+1; j < chk_nitems; j++ ) { 
        if ( __TMPL___rs_hmap_key_cmp(&(bkts[i].key), &(bkts[j].key)) ) {
          fprintf(stderr, "Positions %u and %u have same key \n", i, j);
          go_BYE(-1);
        }
      }
    }
  }
  else { // do a faster O(n log n) comparison of the hashes
    qsort(hashes, hash_cnt, sizeof(chk_t), sortcompare_UI64);
    for ( uint32_t i = 1; i < chk_nitems; i++ ) { 
      if ( hashes[i].hash == hashes[i-1].hash ) { go_BYE(-1); }
    }
  }
  //-----------------------
  //-- make sure no holes between initial probe_loc and current position
  for ( uint32_t i = 0; i < ptr_hmap->size; i++ ) { 
    if ( !bkt_full[i] ) { continue; }
    __TMPL___rs_hmap_val_t val; bool is_found; uint32_t where_found; 
    void *ptr_key    = &(bkts[i].key);
    status = __TMPL___rs_hmap_get(ptr_hmap, ptr_key, (void *)&val, &is_found, 
        &where_found);
    cBYE(status);
    if ( !is_found ) { go_BYE(-1); }
    uint32_t hash = __TMPL___rs_hmap_set_hash(ptr_key, ptr_hmap);
    uint32_t probe_loc = 
      set_probe_loc(hash, ptr_hmap->size, ptr_hmap->divinfo);
    if ( probe_loc == i ) { 
      // this key was placed with no searching 
      continue;
    }
    uint32_t start_from = i;
    for ( uint32_t num_searches = 0 ; ; num_searches++ ) { 
      if ( num_searches == ptr_hmap->size ) { go_BYE(-1); }
      if ( !bkt_full[start_from] ) { go_BYE(-1); }
      if ( start_from == 0 ) { 
        start_from = ptr_hmap->size - 1;
      }
      else {
        start_from--;
      }
      if ( start_from == probe_loc ) { break; }
    }
  }
BYE:
  free_if_non_null(hashes);
  return status;
}
