#include <stdlib.h>
#include <stdint.h>
#include "rdtsc.h"
#include "mk_hmap_key.h"
//START_FUNC_DECL
uint32_t
mk_hmap_key(
    void
    )
//STOP_FUNC_DECL
{
  uint64_t r1 = random() ^ RDTSC();
  uint64_t r2 = random() ^ RDTSC();
  return (uint32_t)( r1 | ( r2 << 32 )  );
}
