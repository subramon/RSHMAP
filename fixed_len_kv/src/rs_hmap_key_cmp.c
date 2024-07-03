// Default implementation. User is expected to over-ride
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "macros.h"
#include "__TMPL___rs_hmap_struct.h"
#include "__TMPL___rs_hmap_key_cmp.h"

//START_FUNC_DECL
bool
__TMPL___rs_hmap_key_cmp(
    const __TMPL___rs_hmap_key_t * const ptr_key1,
    const __TMPL___rs_hmap_key_t * const ptr_key2
    )
//STOP_FUNC_DECL
{
  if ( ( ptr_key1 == NULL ) && ( ptr_key2 == NULL ) ) { return true; } 
  if ( ptr_key1 == NULL ) { return false; }
  if ( ptr_key2 == NULL ) { return false; }
  if ( memcmp(ptr_key1, ptr_key2, sizeof(__TMPL___rs_hmap_key_t)) == 0 ) {
    return true;
  }
  else {
    return false;
  }
}
