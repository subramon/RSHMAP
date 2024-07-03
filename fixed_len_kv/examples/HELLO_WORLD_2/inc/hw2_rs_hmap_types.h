#ifndef __HW2_RS_HMAP_TYPES_H
#define __HW2_RS_HMAP_TYPES_H
#include <stdint.h>
typedef struct _hw2_rs_hmap_key_t { 
  double  f8;
  uint16_t ui2;
  float f4;
  int i4;
} hw2_rs_hmap_key_t;
typedef struct _rhw2_s_hmap_val_t {
  int64_t i8;
  char str[16];
  int8_t i1;
} hw2_rs_hmap_val_t;
#endif //  __HW2_RS_HMAP_TYPES_H
