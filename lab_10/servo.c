/*
 * servo.c
 *
 *  Created on: Oct 22, 2020
 *      Author: bruceb1
 */

#include "servo.h"

#define ZERO_DEG 311480
#define ONE_EIGHTY_DEG 282440
#define DEG_TO_MATCH_FACTOR ((ZERO_DEG - ONE_EIGHTY_DEG) / 180)

unsigned int pulsePeriod = 320000; //20 milliseconds
int pulseLength = 20500;
float degreesPosition = 90;



//Initialize time and setup PWM
void servo_init()   {

       SYSCTL_RCGCGPIO_R |= 0b000010;      //Enable PORTB clock
       GPIO_PORTB_DEN_R |= 0b00100000;  //Digital Enable for PB5 (T1CCP1)
       GPIO_PORTB_DIR_R |= 0b00100000;  //Setting PB5 as output
       GPIO_PORTB_AFSEL_R |= 0b00100000;    //Turning on Alternate Function for PB5
       GPIO_PORTB_PCTL_R |= 0x700000;   //Selecting function Timer 0 Capture/Compare/PWM 0 for PB6

       SYSCTL_RCGCTIMER_R |= 0b000010;  //Turn on the clock for timer1
       TIMER1_CTL_R &= 0b011111111; //disable timer to config
       TIMER1_TBMR_R |= 0b1010; //periodic and PWM enable and edge count
       TIMER1_CTL_R &= ~0x4000; //Configure the output state of the PWM signal *non-inverted
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

       TIMER1_CTL_R |= 0b100000000;     //Re-enable the timer
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

