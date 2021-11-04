#include "Timer.h"
#include "open_interface.h"

#define t_out 5

void ping_init(void)
{
   /* initialize port B pin 3 */
   SYSCTL_RCGCGPIO_R |= 0x2; // Port B system clock
   GPIO_PORTB_DIR_R |= 0x4; // PB3 as output
   GPIO_PORTB_AFSEL_R &= ~0x4; // disable alt fun'n
   GPIO_PORTB_DEN_R |= 0x4; // enable
   GPIO_PORTB_DATA_R  &= ~0x4; // set to low

   // set pin low-high-low

   // initalize timer
   SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R1; // Turn on clock to TIMER1
   TIMER1_CTL_R &= ~TIMER_CTL_TAEN;           // Disable TIMER5 for setup
   TIMER1_CFG_R = TIMER_CFG_16_BIT;           // Set as 16-bit timer
   TIMER1_TAMR_R |= 0x17   // set TACMR to 1, TAMR to 3, and TACDIR to 1
   TIMER1_CTL_R |= TIMER_CTL_TAEVENT_BOTH; // capture both positive and negative edge
   TIMER1_TAILR_R = TIMER_TAILR_S; // start count at 0




   TIMER1_ICR_R |= TIMER_ICR_TATOCINT; // clear interrupt status




   TIMER1_ICR_R |= TIMER_ICR_TATOCINT; // Clear timeout interrupt status
   TIMER1_TAPR_R = 0x0F;               // 15 gives a period of 1us
   TIMER1_IMR_R |= TIMER_IMR_TATOIM;   // Allow TIMER5 timeout interrupts
   NVIC_PRI23_R |= NVIC_PRI23_INTA_M;  // Priority 7 (lowest)
   NVIC_EN2_R |= (1 << 28);             // Enable TIMER5 interrupts

   IntRegister(INT_TIMER5A, timer_clockTickHandler); // Bind the ISR
   TIMER1_CTL_R |= TIMER_CTL_TAEN; // Start TIMER5 counting

 //  _running = 1;

 //  GPIO_PORTB_DEN_R &= ~0x10;
}

int ping_read(void)
{
    // trigger pulse by setting PB3 low-high-low

    GPIO_PORTB_DATA_R  &= ~0x4; // set to low
    waitMicros(t_out);
    GPIO_PORTB_DATA_R  |= 0x4; // set to high
    waitMicros(t_out);
    GPIO_PORTB_DATA_R  &= ~0x4; // set to low

    // start timer
    GPIO_PORTB_DATA_R  &= ~0x4; // set to low

}
