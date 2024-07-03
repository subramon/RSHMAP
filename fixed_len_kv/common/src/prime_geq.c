#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include "prime_geq.h"
//START_FUNC_DECL
uint32_t 
prime_geq(
    uint32_t n
    )
//STOP_FUNC_DECL
{
  if ( n <= 1 ) { return 1; }
  // start with odd number >= n
  uint32_t m;
  if ( n % 0x1 == 1 ) { m = n; } else { m = n + 1 ; }
  for ( ; ; m = m + 2 ) { 
    bool is_prime = true;
    for ( uint32_t k = 3;  k <= sqrt(m); k = k + 2 ) { 
      if ( ( m % k ) == 0 ) { 
        is_prime = false; 
        break;
      }
    }
    if ( is_prime ) { 
      return m;
    }
  }
}
