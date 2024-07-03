#ifndef __RS_CONFIG_H
#define __RS_CONFIG_H

// Configs set externally
typedef struct _rs_hmap_config_t { 
  uint32_t min_size;
  uint32_t max_size;
  float low_water_mark;
  float high_water_mark;
} rs_hmap_config_t; 

#endif // __RS_CONFIG_H
