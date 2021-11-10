/*
 * cyBot_adc.c
 *
 *  Created on: Oct 8, 2020
 *      Author: bruceb1
 */

#include "cyBot_adc.h"

void cyBot_ADC_init()  {

    //turn on the clock
    SYSCTL_RCGCADC_R |= 0b01;

    //Enable the clock for ports B
    SYSCTL_RCGCGPIO_R |= 0b0000010;

    //Set the AFSEL register for ADC input pins
    GPIO_PORTB_AFSEL_R |= 0b00010000;

    //Set the digital enalble for AIN10
    GPIO_PORTB_DEN_R &= 0b11101111;

    //Disable the analog isolation circuit for all ADC input pins that are to be used
   //GPIO_PORTB_AMSEL_R &= 0b11101111;
    GPIO_PORTB_AMSEL_R |= 0b00010000;


    //initalize ADC port trigger
    GPIO_PORTB_ADCCTL_R = 0x00;

    //Disable the Sample Sequencer (SS0)
    ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;

    //Set the trigger to processor for each EM0
    //ADCEMUX_R &= 0b0000000000000000;
    ADC0_EMUX_R = ADC_EMUX_EM0_PROCESSOR;

    //set 1st sample to use the AIN10 ADC pin
    ADC0_SSMUX0_R &= 0xFFFFFFF0; //Can be forced to 0's as well
    ADC0_SSMUX0_R |= 0x000A;

    //enable the end bit for the first sample sequencer
    ADC0_SSCTL0_R &= 0b0000;
    ADC0_SSCTL0_R |= 0b0110;

    //enable oversampling to average
   // ADC0_SAC_R |= ADC_SAC_AVG_64X;

    //re-enable ADC0 SS0
    ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;
}


int cyBot_ADC_read()  {

    int value = 0;

    //disable ADC0SS0 sample sequencer to configure it
    //ADC0_ACTSS_R &= ~ADC_ACTSS_ASEN0;

    //set 1st sample to use the channel ADC pin
    //ADC0_SSMUX0_R |= 0x000A;

    //re-enable ADC0 SS0
    //ADC0_ACTSS_R |= ADC_ACTSS_ASEN0;

    //initiate SS0 conversion
    ADC0_PSSI_R = ADC_PSSI_SS0;

    //wait for ADC conversion to be complete
    while((ADC0_RIS_R & ADC_RIS_INR0) == 0){}

    ADC0_ISC_R |= 0b0001;


    value = ADC0_SSFIFO0_R;

    return value;
}



