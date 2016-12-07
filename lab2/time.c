#include "os.h"
#include "math.h"

#define CLO 0x7E003004
#define CHI 0x7E003008
#define FOS 900000000

void get_time ( unsigned int *sec, unsigned int *usec)
{
    
}

unsigned int now_usec( )
{
      uint8_t l;
      uint8_t h;
      uint8_t now;
      l = GET32(CLO);
      h = GET32(CHI);
      now = h<<31 | l;
      now = (now * pow(10, 6)) / FOS;
      return now;
}

unsigned int now_hrs( void )
{
}

unsigned int usec_diff(unsigned int now, unsigned int then)
{
      unsigned int diff = 0;
      return diff;
}

void wait (unsigned int delay)
{
      uint8_t now = 0;
      do
      {
            now = now_usec();
            now =  now / delay;             
      } while(now == 0);
}
