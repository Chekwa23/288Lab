#include "servo.h"

#define ZERO_DEG 311480
#define ONE_EIGHTY_DEG 282440
#define DEG_TO_MATCH_FACTOR ((ZERO_DEG - ONE_EIGHTY_DEG) / 180)

unsigned int pulsePeriod = 320000; //20 milliseconds
int pulseLength = 20500;
float degreesPosition = 90;


unsigned int PB5 = 0x20;


void servo_init()   
{
    /* GPIO config: PB5 as digital output */

    SYSCTL_RCGCGPIO_R |= 0x2;  
    GPIO_PORTB_DIR_R |= PB5; 
    GPIO_PORTB_AFSEL_R |= PB5; 
    GPIO_PORTB_DEN_R |= PB5;
    GPIO_PORTB_PCTL_R |= 0x00070000;  

    /* Timer 1B config: PWM & periodic mode, 8 bit prescalar, 16 bit countdown timer, falling edge */

    SYSCTL_RCGCTIMER_R |= 0b000010;  //Turn on the clock for timer1
    TIMER1_CTL_R &= ~0b0100; //disable timerB for config
    TIMER1_TBMR_R |= 0b1010; //periodic and PWM enable 
    TIMER1_CTL_R &= ~0x4000; // ensure pwm output is not inverted
    TIMER1_CFG_R |= 0b00000100; //set size of timer to 16

    TIMER1_TBPR_R =  (pulsePeriod >> 16) & 0xFF;   //write the top 8 bits to the pre-scaler
    TIMER1_TBILR_R = pulsePeriod & 0xFFFF;    //write the lower 16 bits to Internal Load register

    /* //move servo to the middle
    int mid = pulsePeriod - pulseLength;
    TIMER1_TBPMR_R =  (mid >> 16) & 0xFF;        //set top 8-bit of pre-scaler
    TIMER1_TBMATCHR_R = mid & 0xFFFF;        //set lower 16-bit*/

    //move servo to "0" degree
    TIMER1_TBPMR_R = 0x0;   //set the match register pre-scaler top 8-bits
    TIMER1_TBMATCHR_R = 0x3E80;   //set the remaining 16 bits in the match register
    //TIMER1_TBMATCHR_R = 0x5DC0;

    //turn on interrupts
    TIMER1_ICR_R |= 0x900;
    TIMER1_IMR_R |= 0x900;
    NVIC_EN0_R |= 0x40000;

    TIMER1_CTL_R |= 0x0100;    //Re-enable the timer
}


int servo_move(float degrees)  {

   /* if (degrees > 180 || degreesPosition > 180)   {
        degrees = 180;
        degreesPosition = 180;
    }
    float pulsePercent =*/

    // Map given degrees to the correct range of match values
    unsigned int new_match = ZERO_DEG - DEG_TO_MATCH_FACTOR * degrees;
    TIMER1_TBPMR_R = (new_match >> 16) & 0xFF; // Bits 17:24 of match value
    TIMER1_TBMATCHR_R = new_match & 0xFFFF; // Lower 16 bits of the timer start value

    return new_match & 0xFFFFFF;
}

