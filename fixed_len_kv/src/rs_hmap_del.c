// EXTERNAL EXPOSURE
/*
 * hmap_del: remove the given key and return its value.
 * => If key was present, return its associated value
 */
#include <stdio.h>
#include <stdint.h>
#include "macros.h"
#include "set_probe_loc.h"
#include "rs_hmap_common.h"
#include "__TMPL___rs_hmap_struct.h"
#include "__TMPL___rs_hmap_set_hash.h"
#include "__TMPL___rs_hmap_key_cmp.h"
#include "__TMPL___rs_hmap_resize.h"
#include "__TMPL___rs_hmap_del.h"
//START_FUNC_DECL
int
__TMPL___rs_hmap_del(
    __TMPL___rs_hmap_t *ptr_hmap, 
    const __TMPL___rs_hmap_key_t * const ptr_key, 
          __TMPL___rs_hmap_val_t *       ptr_val, 
    // set to  NULL => we do not care for value
    bool *ptr_is_found
    )
//STOP_FUNC_DECL
{
  int status = 0;

  if ( ptr_hmap == NULL ) { go_BYE(-1); } 
  if ( ptr_key == NULL ) { go_BYE(-1); } 

  register uint32_t hash = __TMPL___rs_hmap_set_hash(ptr_key, ptr_hmap);
  register uint32_t probe_loc = 
    set_probe_loc(hash, ptr_hmap->size, ptr_hmap->divinfo);
  register __TMPL___rs_hmap_bkt_t *bkts = ptr_hmap->bkts;
  register bool *bkt_full = ptr_hmap->bkt_full;
  register uint32_t my_psl = 0;
  register uint32_t num_probes = 0;

  // Start by assuming that key is not found. 
  *ptr_is_found = false;
  if ( ptr_val != NULL ) { 
    memset(ptr_val, 0, sizeof(__TMPL___rs_hmap_val_t));
  }

  for ( ; ; ) {
    if ( num_probes >= ptr_hmap->size ) { go_BYE(-1); }
    // same probing logic as in lookup function.
    uint16_t this_psl = bkts[probe_loc].psl; 
    if ( bkt_full[probe_loc] == false ) { // bucket is empty
      goto BYE;
    }
    if ( my_psl > this_psl) { // key does not exist 
      goto BYE;
    }
    // check if key matches incoming one 
    if ( __TMPL___rs_hmap_key_cmp(&(bkts[probe_loc].key), ptr_key) ) { 
      *ptr_is_found = true;
      if ( ptr_val != NULL ) {  // return value of deleted key
        *ptr_val = bkts[probe_loc].val; 
      }
      break;
    }
    my_psl++;
    /* Continue to the next bucket. */
    probe_loc++;
    if ( probe_loc == ptr_hmap->size ) { probe_loc = 0; }
    num_probes++;
  }

  // if key does not exist, we should have returned by now 
  if ( *ptr_is_found == false ) { go_BYE(-1); }

  ptr_hmap->nitems--;
  // We found the key at probe_loc

  /*
   * The probe sequence must be preserved in the deletion case.
   * Use the backwards-shifting method to maintain low variance.
   */
  __TMPL___rs_hmap_bkt_t *this_bkt  = &(bkts[probe_loc]);
  uint32_t prev_probe_loc = probe_loc; 
  for ( ; ; ) {
    // mark this bucket as empty
    memset(&(bkts[probe_loc]), 0, sizeof(__TMPL___rs_hmap_bkt_t));
    bkt_full[probe_loc] = false; 

    probe_loc++;
    if ( probe_loc == ptr_hmap->size ) { probe_loc = 0; }
    __TMPL___rs_hmap_bkt_t *next_bkt = bkts + probe_loc;
    /*
     * Stop if we reach an empty bucket or hit a key which
     * is in its base (original) location.
     */
    if ( ( bkt_full[probe_loc] == false ) || ( next_bkt->psl == 0 ) ) { 
      break;
    }
    next_bkt->psl--;
    *this_bkt = *next_bkt;
    this_bkt = next_bkt;
    bkt_full[prev_probe_loc] = bkt_full[probe_loc];
    prev_probe_loc = probe_loc; 
  }

  /*
   * If the load factor is less than threshold, then shrink by
   * halving the size, but not more than the minimum size.
   */
  size_t threshold = LOW_WATER_MARK * (double)ptr_hmap->size;
  if ( ( ptr_hmap->nitems > ptr_hmap->config.min_size ) && 
       ( ptr_hmap->nitems < threshold ) ) {
    size_t new_size = (double)ptr_hmap->nitems / IDEAL_WATER_MARK;
    if ( new_size < ptr_hmap->config.min_size ) { 
      new_size = ptr_hmap->config.min_size;
    }
    status = __TMPL___rs_hmap_resize(ptr_hmap, new_size); cBYE(status); 
  }
BYE:
  return status;
}
