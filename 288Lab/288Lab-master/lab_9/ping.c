#include "timer.h"
#include "open_interface.h"
#include "ping.h"
#include "driverlib/interrupt.h"

unsigned int PB3 = 0x8;
volatile enum {LOW, HIGH, DONE} state; // set by ISR
volatile unsigned int rising_time; //Pulse start time: Set by ISR
volatile unsigned int falling_time; //Pulse end time: Set by ISR




void ping_timer3b_init(void)
{
   /* GPIO config: PB3 as digital output (initially low)  */

   SYSCTL_RCGCGPIO_R |= 0x2;
   GPIO_PORTB_DIR_R |= PB3;
   GPIO_PORTB_AFSEL_R |= ~PB3;
   GPIO_PORTB_DEN_R |= PB3;
   GPIO_PORTB_DATA_R  &= ~PB3;

   /* Timer 3B config: input capture, count-down, 16 bit timer */

   SYSCTL_RCGCTIMER_R |= 0x8;
   TIMER3_CTL_R &= ~0x0100; //disable timerB for config
   TIMER3_CFG_R = 0x4;
   TIMER3_TBMR_R = 0b0111;
   TIMER3_CTL_R |= 0x0C00; // capture both edges
   TIMER3_IMR_R |= 0x0400; // enable interrupts & clear status
   TIMER3_ICR_R |= 0x0400;
   TIMER3_TBILR_R = 0xFFFF;
   TIMER3_TBPR_R =  0xFF;

   IntRegister(INT_TIMER3B, TIMER3B_handler); // Bind the ISR
   IntMasterEnable();
//
//   TIMER3_ICR_R |= 0x0400; // clear interrupt status
//
//   TIMER1_TAPR_R = 0x0F;               // 15 gives a period of 1us



}


/* Pulse output signal from PB3 low-high-low to trigger sonar burst */
int ping_read(void)
{

    int ping_distance = 0;
    send_pulse();

//    while(1)
//    {
//        // Wait for ISR to capture rising edge & falling edge time
//        switch(state) {
//            case HIGH : // pulse start
//                break;
//            case LOW : // pulse end
//                break;
//            case DONE :
//                break;
//            default :
//                break;
//
//        }
//    }


    // Calculate the width of the pulse; convert to centimeters
    return ping_distance;

}

void send_pulse()
{
    TIMER3_IMR_R &= ~0x0400; // mask timer IR
    GPIO_PORTB_AFSEL_R &= ~PB3; // GPIO
    GPIO_PORTB_DIR_R |= PB3; // output
    GPIO_PORTB_DATA_R  |= PB3; // high

    timer_waitMicros(5); // wait 5 microseconds

    GPIO_PORTB_DATA_R  &= ~PB3; // low
    GPIO_PORTB_DIR_R &= ~PB3; // input
    GPIO_PORTB_AFSEL_R |= PB3;
    GPIO_PORTB_PCTL_R |= 0x7000;

    TIMER3_ICR_R |= 0x0400; // unmask timer IR & clear status
    TIMER3_IMR_R |= 0x0400;
}

void TIMER3B_handler(void)
{
    return;
}


