#include "rs_hmap_common.h"
#include "mk_hmap_key.h"
#include "__TMPL___rs_hmap_struct.h"
#include "__TMPL___rs_hmap_insert.h"
#include "__TMPL___rs_hmap_resize.h"
//START_FUNC_DECL
int
__TMPL___rs_hmap_resize(
    __TMPL___rs_hmap_t *ptr_hmap, 
    size_t newsize
    )
//STOP_FUNC_DECL
{
  int status = 0;
  if ( ptr_hmap == NULL ) { go_BYE(-1); }
  const size_t oldsize = ptr_hmap->size;
  const size_t nitems  = ptr_hmap->nitems;
  register __TMPL___rs_hmap_bkt_t *bkts = ptr_hmap->bkts;
  register bool *bkt_full = ptr_hmap->bkt_full;

  // some obvious logical checks
  if ( ( newsize <= 0 ) || ( newsize >= UINT_MAX ) )  { go_BYE(-1); }
  if ( newsize < (uint32_t)(HIGH_WATER_MARK * (double)nitems) ) { 
    go_BYE(-1); 
  }
  status = posix_memalign((void **)&(ptr_hmap->bkts), 16, 
      sizeof(__TMPL___rs_hmap_bkt_t) * newsize);
  cBYE(status);
  memset(ptr_hmap->bkts, 0, sizeof(__TMPL___rs_hmap_bkt_t) * newsize);

  status = posix_memalign((void **)&(ptr_hmap->bkt_full), 16,
      sizeof(bool) * newsize);
  cBYE(status);
  memset((ptr_hmap->bkt_full), 0, sizeof(bool) * newsize);

  ptr_hmap->size   = newsize;
  uint32_t chk_nitems = ptr_hmap->nitems;
  ptr_hmap->nitems = 0;

   // generate a new hash key/seed every time we resize the hash table.
  ptr_hmap->divinfo = fast_div32_init(newsize);
  ptr_hmap->hashkey = mk_hmap_key();

  for ( uint32_t i = 0; i < oldsize; i++) {
    if ( bkt_full[i] == false ) { continue; } // skip empty slots
    // printf("Re-inserting %s \n", (char *)bkts[i].key);
    __TMPL___rs_hmap_key_t *ptr_key  = &(bkts[i].key);
    __TMPL___rs_hmap_val_t *ptr_val  = &(bkts[i].val);
    status = __TMPL___rs_hmap_insert(ptr_hmap, ptr_key, ptr_val); 
    cBYE(status);
  }
  if ( ptr_hmap->nitems != chk_nitems ) { go_BYE(-1); }
  free_if_non_null(bkts);
  free_if_non_null(bkt_full);
BYE:
  return status;
}
