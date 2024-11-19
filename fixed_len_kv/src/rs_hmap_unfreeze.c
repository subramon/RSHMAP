#include "rs_mmap.h"
#include "mk_dir_file_name.h"
#include "rs_hmap_common.h"
#include "__TMPL___rs_hmap_struct.h"
#include "__TMPL___rs_hmap_unfreeze.h"
//START_FUNC_DECL
int 
__TMPL___rs_hmap_unfreeze(
    __TMPL___rs_hmap_t *H,
    const char * const dir,
    const char * const meta_file_name,
    const char * const bkts_file_name,
    const char * const full_file_name
    )
//STOP_FUNC_DECL
{
  int status = 0;
  FILE *fp = NULL; char *fname = NULL;
  int nr = 0; char *X = NULL; size_t nX = 0;

  //------------------------------------------------
  if ( meta_file_name == NULL ) { go_BYE(-1); } 
  fname = mk_dir_file_name(dir, meta_file_name);
  if ( fname == NULL ) { go_BYE(-1); } 
  fp = fopen(fname, "r");
  return_if_fopen_failed(fp, fname, "r");
  //------------------------------------------------

  nr = fscanf(fp, "size,%" PRIu32 "\n", &(H->size));
  if ( nr != 1 ) { go_BYE(-1); }

  nr = fscanf(fp, "nitems,%" PRIu32 "\n", &(H->nitems));
  if ( nr != 1 ) { go_BYE(-1); }

  nr = fscanf(fp, "divinfo,%" PRIu64 "\n", &(H->divinfo));
  if ( nr != 1 ) { go_BYE(-1); }

  nr = fscanf(fp, "hashkey,%" PRIu64 "\n", &(H->hashkey));
  if ( nr != 1 ) { go_BYE(-1); }

  //-- configs 
  nr = fscanf(fp, "min_size,%" PRIu32 "\n", &(H->config.min_size));
  if ( nr != 1 ) { go_BYE(-1);  }

  nr = fscanf(fp, "max_size,%" PRIu32 "\n", &(H->config.max_size));
  if ( nr != 1 ) { go_BYE(-1);  }

  nr = fscanf(fp, "low_water_mark,%f\n", &(H->config.low_water_mark));
  if ( nr != 1 ) { go_BYE(-1);  }

  nr = fscanf(fp, "high_water_mark,%f\n", &(H->config.high_water_mark));
  if ( nr != 1 ) { go_BYE(-1);  }

  H->start_check_val = 123456789; // to check integrity of struct
  H->stop_check_val  = 987654321; // to check integrity of struct

  free_if_non_null(fname);
  fclose_if_non_null(fp);
  //--------------------------------------------------
  if ( bkts_file_name == NULL ) { go_BYE(-1); } 
  fname = mk_dir_file_name(dir, bkts_file_name);
  if ( fname == NULL ) { go_BYE(-1); } 

  status = rs_mmap(fname, &X, &nX, 0); cBYE(status);
  status = posix_memalign((void **)&(H->bkts), 16, nX); cBYE(status);
  memcpy(H->bkts, X, nX);
  munmap(X, nX); X = NULL; nX = 0;

  free_if_non_null(fname);
  //--------------------------------------------------
  if ( full_file_name == NULL ) { go_BYE(-1); } 
  fname = mk_dir_file_name(dir, full_file_name);
  if ( fname == NULL ) { go_BYE(-1); } 

  status = rs_mmap(fname, &X, &nX, 0); cBYE(status);
  status = posix_memalign((void **)&(H->bkt_full), 16, nX); cBYE(status);
  memcpy(H->bkt_full, X, nX);
  munmap(X, nX); X = NULL; nX = 0;

  free_if_non_null(fname);
  //--------------------------------------------------
BYE:
  free_if_non_null(fname);
  fclose_if_non_null(fp);
  return status;
}
