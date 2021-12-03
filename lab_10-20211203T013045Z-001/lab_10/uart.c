/*
*
*   uart_extra_help.c
* Description: This is file is meant for those that would like a little
*              extra help with formatting their code, and followig the Datasheet.
*/
#include "lcd.h"
#include "uart.h"
#include "timer.h"
#include "uart.h"
#define REPLACE_ME 0x00


void uart_init(int baud)
{
    SYSCTL_RCGCGPIO_R |= 0b00000010;      // enable clock GPIOB (page 340)
    SYSCTL_RCGCUART_R |= 0b00000010;      // enable clock UART1 (page 344)
    GPIO_PORTB_AFSEL_R |= 0b00000011;      // sets PB0 and PB1 as peripherals (page 671)
    GPIO_PORTB_PCTL_R  &= 0xFFFFFF00;       // pmc0 and pmc1       (page 688)  also refer to page 650
    GPIO_PORTB_PCTL_R  |= 0x00000011;       // pmc0 and pmc1       (page 688)  also refer to page 650
    GPIO_PORTB_DEN_R   |= 0b00000011;        // enables pb0 and pb1
    GPIO_PORTB_DIR_R   |= 0b00000001;        // sets pb0 as output, pb1 as input
    GPIO_PORTB_DIR_R   &= 0b11111101;

    //compute baud values [UART clock= 16 MHz] 
    double fbrd;
    int    ibrd;

    //fbrd = REPLACE_ME; // page 903
    ibrd = 8;
    fbrd = 44;

    UART1_CTL_R &= 0b1111111111111110;      // disable UART1 (page 918)
    UART1_IBRD_R = 8;        // write integer portion of BRD to IBRD
    UART1_FBRD_R = 44;   // write fractional portion of BRD to FBRD
    UART1_LCRH_R |= 0b01100000;
    UART1_LCRH_R &= 0b111111101; // write serial communication parameters (page 916) * 8bit and no parity
    UART1_CC_R  &= 0x0;          // use system clock as clock source (page 939)
    UART1_CTL_R |= 0b0000000000000001;        // enable UART1

}

void uart_sendChar(char data)
{
   while(UART1_FR_R & 0b00100000) {

   }

   UART1_DR_R = data;
   
}

char uart_receive(void)
{
    char data = 0;

    while(UART1_FR_R & 0b00010000) {

    }
 
    data = (char) (UART1_DR_R & 0xFF);

    return data;
}


void uart_sendStr(const char *data)
{
    int i = 0;

    while(UART1_FR_R & 0b00100000) {

    }

    UART1_DR_R = '\n';
    UART1_DR_R = '\r';


    /*while (data[i] != '\0')
    {
        UART1_DR_R = data[i];
        i++;
    }*/
    //uart_sendChar(data);
}

// _PART3


void uart_interrupt_init()
{
    // Enable interrupts for receiving bytes through UART1
    UART1_IM_R |= 0b0000000010000; //enable interrupt on receive - page 924

    // Find the NVIC enable register and bit responsible for UART1 in table 2-9
    // Note: NVIC register descriptions are found in chapter 3.4
    NVIC_EN0_R |= 0x6; //enable uart1 interrupts - page 104

    // Find the vector number of UART1 in table 2-9 ! UART1 is 22 from vector number page 104
    IntRegister(22, uart_interrupt_handler); //give the microcontroller the address of our interrupt handler - page 104 22 is the vector number

}

void uart_interrupt_handler()
{
// STEP1: Check the Masked Interrupt Status
    if(UART1_MIS_R & 0b0000000010000) {


//STEP2:  Copy the data 

        char string[21] = "";
        char clear[21] = "                    ";
        int i = 0;

        char curr;

            for(i = 0; i < 20; i++) {
                curr = uart_receive();
                uart_sendChar(curr);

                if(curr == '\r') {
                    break;
            }

            string[i] = curr;
            }

            lcd_printf("%s", clear);
            lcd_printf("%s", string);

            uart_sendStr(string);

            sprintf(string, "                    ");

//STEP3:  Clear the interrupt
          UART1_ICR_R = 0b0000000010000;

    }
}
