// EXTERNAL EXPOSURE
// #include <dlfcn.h>
#include "rs_hmap_common.h"
#include "__TMPL___rs_hmap_struct.h"
#include "__TMPL___rs_hmap_destroy.h"
//START_FUNC_DECL
void
__TMPL___rs_hmap_destroy(
    __TMPL___rs_hmap_t *ptr_hmap
    )
//STOP_FUNC_DECL
{
  if ( ptr_hmap == NULL ) { return; }
  free_if_non_null(ptr_hmap->bkts);
  free_if_non_null(ptr_hmap->bkt_full);
  /* Not needed any more 
  free_if_non_null(ptr_hmap->config.so_file);
  if ( ptr_hmap->config.so_handle != NULL ) { 
    char *cptr = dlerror();
    if ( cptr != NULL ) { 
      fprintf(stderr, "Error on dlclose = %s \n", cptr);
    }
    // TODO P0 Why does dlclose() cause error sometimes?
    // int status = dlclose(ptr_hmap->config.so_handle);
    // if ( status != 0 ) { WHEREAMI; }
  }
  */
  memset(ptr_hmap, '\0', sizeof(__TMPL___rs_hmap_t));
}
