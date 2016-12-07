//
#define ONE_USEC        0x1
#define ONE_MSEC        (0x1 << 10)
#define ONE_SEC         (0x1 << 20)

#define MICROSECONDS(u) (u * ONE_USEC)
#define MILLISEC(m)             (m * ONE_MSEC)
#define SECONDS(s)              (s * ONE_SEC)           // note we can only go up to 2000 seconds



//
// time/timeoutq routines
//

unsigned int usec_diff( unsigned int now, unsigned int then );   // only good for short deltas: assumes only one wrap-around is possible
unsigned int now_usec( void );
unsigned int now_hrs( void );
void get_time ( unsigned int *sec, unsigned int *usec);
void wait ( unsigned int );
void oldwait ( unsigned int );
