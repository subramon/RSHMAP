// EXTERNAL EXPOSURE
/*
 * rhashmap_put: insert a value given the key.
 *
 * => If the key is already present, return its associated value.
 * => Otherwise, on successful insert, return the given value.
 */
#include "calc_new_size.h"
#include "rs_hmap_common.h"
#include "__TMPL___rs_hmap_struct.h"
#include "__TMPL___rs_hmap_resize.h"
#include "__TMPL___rs_hmap_insert.h"
#include "__TMPL___rs_hmap_put.h"
//START_FUNC_DECL
int
__TMPL___rs_hmap_put(
    __TMPL___rs_hmap_t *ptr_hmap, 
    const __TMPL___rs_hmap_key_t  * const ptr_key, 
    const __TMPL___rs_hmap_val_t * const ptr_val
    )
//STOP_FUNC_DECL
{
  int status = 0;
  uint32_t newsize; bool resize = false;
  uint64_t threshold = (uint64_t)(HIGH_WATER_MARK * (double)ptr_hmap->size);

  if ( ptr_hmap->nitems > threshold ) { 
    status = calc_new_size(ptr_hmap->nitems, ptr_hmap->config.max_size, 
        ptr_hmap->size, &newsize, &resize);
    cBYE(status);
  }
  if ( resize ) { 
    status = __TMPL___rs_hmap_resize(ptr_hmap, newsize); cBYE(status);
  }
  status = __TMPL___rs_hmap_insert(ptr_hmap, ptr_key, ptr_val); cBYE(status);
BYE:
  return status;
}
