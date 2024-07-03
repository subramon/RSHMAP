#ifndef ___TMPL___RS_HMAP_STRUCT_H
#define ___TMPL___RS_HMAP_STRUCT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>
#include "__TMPL___rs_hmap_types.h"
#include "rs_hmap_config.h"

typedef struct __TMPL___rs_hmap_kv_t { 
  __TMPL___rs_hmap_key_t key;
  __TMPL___rs_hmap_val_t val;
} __TMPL___rs_hmap_kv_t;

typedef struct __TMPL___rs_hmap_bkt_t { 
  __TMPL___rs_hmap_key_t key; 
  uint16_t psl; // probe sequence length 
  __TMPL___rs_hmap_val_t val;    // value that is aggregated, NOT input value
} __TMPL___rs_hmap_bkt_t;

typedef struct __TMPL___rs_hmap_t {
  double start_check_val; // for debugging 
  uint32_t size;
  uint32_t nitems;
  uint64_t divinfo;
  __TMPL___rs_hmap_bkt_t  *bkts;  
  bool *bkt_full; 
  uint64_t hashkey;
  rs_hmap_config_t config; // external config 
  double stop_check_val; // for debugging 
} __TMPL___rs_hmap_t;

#endif // ___TMPL___RS_HMAP_STRUCT_H
