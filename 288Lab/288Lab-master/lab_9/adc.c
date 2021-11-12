#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"

void adc_init(void)
{
    SYSCTL_RCGCADC_R  |= 0x01; // ADC0 clock

    SYSCTL_RCGCGPIO_R |= 0x02; // Port B system clock

    GPIO_PORTB_AFSEL_R |= 0x10;
    GPIO_PORTB_DIR_R &= ~0x10;
    GPIO_PORTB_DEN_R &= ~0x10;
    GPIO_PORTB_AMSEL_R |= 0x10;
    GPIO_PORTB_ADCCTL_R = 0x00;


    ADC0_ACTSS_R = 0x02;
    ADC0_EMUX_R &= ~0xF0;

    ADC0_SSMUX1_R &= ~0x0F;
    ADC0_SSMUX1_R |= 0x0A; // ain10
    ADC0_SSCTL1_R |= 0x06; // end after first sample
    ADC0_SAC_R |= 0x02;

}

int adc_read(void)
{
    // initiate sampling on SS1
    ADC0_PSSI_R |= 0x02;

    while(~ADC0_RIS_R & 0x02); // wait for complete conversion on SS1

    int quantizedValue = ADC0_SSFIFO1_R & 0x0FFF;


    // clear interrupt
    ADC0_ISC_R |= 0x02;

    return quantizedValue;
}
