/*
 * os.h
 */

//
// some useful types
//
typedef void (* pfv_t)();
typedef int (* pfi_t)();
typedef unsigned int (* pfu_t)();



typedef union allnum {
	char	name[4];
	short	half[2];
	int		num;
} allnum_t;

#define NULL 0

//
// some system parameters
//
#define NUM_CORES	4
#define NUM_THREADS	16
#define MAX_SLEEP_INTERVAL	ONE_MSEC

//
// TIME values - caveats:
// a. this assumes you are using the 900MHz-driven clock-timer as "now"
// b. it is ridiculously inaccurate (only approximately == 1 usec, 1 msec, 1 sec)
// c. but, hey, it works for now - one can always trim it up to be more accurate later
//    (e.g., set these values to *precisely* the number of clock-timer cycles that
//    bring you to the desired time ... I just didn't have the *time* (haha get it?) 
//    to do all that work)



extern void create_timeoutq_event(int start_time, int repeat_interval, pfv_t gofunction, unsigned int data);
// gofunction:	void function( unsigned int data );



//
// errno/debug routines
//

extern void blink_led( unsigned int );
extern void flash_cpuid( );
extern void flash_lonum( unsigned int );
extern void die( unsigned int );
extern void log( unsigned int );
#define GRN 0x1
#define RED 0x2
extern void flash_led ( unsigned int, unsigned int, unsigned int );

extern void	monitor ( unsigned int *dataval, char *dataname );


//
// utilities/etc (assembly-code routines)
//
extern void PUT32 ( unsigned int, unsigned int );
extern void PUT16 ( unsigned int, unsigned int );
extern void PUT8 ( unsigned int, unsigned int );
extern unsigned int GET32 ( unsigned int );
extern unsigned int GETPC ( void );
extern void dummy ( unsigned int );
extern unsigned int BRANCHTO ( unsigned int );
extern unsigned int cpu_id ( void );
extern void idle ( void );



