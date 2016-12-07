#include "math.h"

uint8_t pow(uint8_t n, uint8_t m)
{
      uint16_t i = 0;
      uint8_t result = 1;
      if( n == 0  || n == 1)
            return 1;
      for(i = 1; i<= m; i++)
      {
            result *= n;
      }
      return result;
}