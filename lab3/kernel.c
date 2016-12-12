#include "os.h"


#define INT_IRQ	0x0F
#define INT_FIQ	0xF0
#define INT_NONE 0

/* set bits - write-only */
#define INT_SET_BASE			0x40000080
/* clear bits - read/write */
#define INT_CLR_BASE			0x400000C0

// und_handler: .word Undefine_Handler
// swi_handler: .word SVI_Handler
// pre_handler: .word Prefetch_Handler
// dat_handler: .word Data_Abort_Handler
// hyp_handler: .word HyperMode_Handler
// irq_handler: .word IRQ_Handler
// fiq_handler: .word FIQ_Handler

void SVI_Handler(void) __attribute__((interrupt("SWI")));
void IRQ_Handler(void) __attribute__((interrupt("IRQ")));
void FIQ_Handler(void) __attribute__((interrupt("FIQ")));

void
interrupt_core( unsigned int core )
{
	PUT32(INT_SET_BASE + ((core & 0xf) << 4), 0x1);// raise interrupt in mailbox
}

void
clear_interrupt( unsigned int core )
{
	PUT32(INT_CLR_BASE + ((core & 0xf) << 4), 0xFFFFFFFF); // clear interrupt in mailbox
}

extern void _init_time();

void
kernel()
{
	unsigned int then, now, delta;
	PUT32(0x40000054, INT_IRQ);		// mboxes 1..3 *do* interrupt, via IRQ
	PUT32(0x40000058, INT_IRQ);
	PUT32(0x4000005C, INT_IRQ);

	flash_lonum(3);

	then = now_usec();
	while (1) {
		now = now_usec();
		delta = usec_diff( now, then );
		if (delta > ONE_MSEC) {
//		if (delta > ((7 * ONE_SEC) + (500 * ONE_MSEC))) {
			then = now;
//			flash_lonum(3);
//			oldwait(20);
			interrupt_core(1);
//			while (1) continue;
		}
	}
}
void SVI_Handler(void)
{
      blink_led(GRN);
      clear_interrupt(1);   
}

void IRQ_Handler(void)
{
      blink_led(RED);
      clear_interrupt(1);
}
void FIQ_Handler(void)
{
      blink_led(GRN | RED);
      clear_interrupt(1);
}
