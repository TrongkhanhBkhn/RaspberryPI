//
// timeout queue
//

#include "os.h"
#include "llist.h"


struct event {
	LL_PTRS;
	int timeout;
	int repeat_interval;
	pfv_t go;
	unsigned int data;
};

#define MAX_EVENTS	8
struct event queue[ MAX_EVENTS ];

// list anchors -- important, but ignore them; they are never used directly
llobject_t TQ;
llobject_t FL;

struct event *timeoutq;
struct event *freelist;

unsigned int then_usec;

//
// sets up concept of local time
// initializes the timeoutq and freelist
// fills the freelist with entries
// timeoutq is empty
//
void
init_timeoutq()
{
	int i;
	then_usec = now_usec();
	timeoutq = (struct event *)&TQ;
	LL_INIT(timeoutq);
	freelist = (struct event *)&FL;
	LL_INIT(freelist);

	for (i=0; i<MAX_EVENTS; i++) {
		struct event *ep = &queue[i];
		LL_PUSH(freelist, ep);
	}

	return;
}


//
// account for however much time has elapsed since last update
// return timeout or MAX
//
int
bring_timeoutq_current()
{
	
}


//
// get a new event structure from the freelist,
// initialize it, and insert it into the timeoutq
// 
void
create_timeoutq_event(int timeout, int repeat, pfv_t function, unsigned int data)
{
    struct event *ep = LL_POP(freelist);
    
    ep->timeout = timeout;
    ep->repeat_interval = repeat;
    ep->data = data;
    ep->go = function;
    LL_PUSH(timeout, ep);
    return ;
}
//
// bring the time current
// check the list to see if anything expired
// if so, do it - and either return it to the freelist 
// or put it back into the timeoutq
//
// return whether or not you handled anything
//
int
handle_timeoutq_event( )
{
    struct event* ep = timeoutq;
    unsigned int now;
    int event_num = 0;
    do{
        now = now_usec();
        if(now % ep->timeout == 0)
        {
            (ep->go)(ep->data);
             event_num ++;
             ep->repeat_interval --;
             if(ep->repeat_interval <=0){
                 LL_DETACH(timeoutq, ep);
                 ep = LL_NULL;
                 LL_PUSH(freelist, ep);
             }
        }    
    }while((ep = timeoutq->next) != LL_NULL);
    
   return  event_num;
}
