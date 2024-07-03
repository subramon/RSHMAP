#include <stdint.h>
#include "get_time_usec.h"
#include "rdtsc.h"

//START_FUNC_DECL
uint64_t
RDTSC(
    void
    )
//STOP_FUNC_DECL
{
  return get_time_usec();
}
