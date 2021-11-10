/*
*
*   uart.c
*
*
*
*
*
*   @author
*   @date
*/

#include "uart.h"
#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "lcd.h"
#include <inc/tm4c123gh6pm.h>
#include "driverlib/interrupt.h"



volatile  char uart_data;
volatile  char flag;
volatile  int autoFag;
volatile  char mode_flag;



void uart_init(int baud){
//    SYSCTL_RCGCGPIO_R |= 0b000010;      // enable clock GPIOB (page 340)
//    SYSCTL_RCGCUART_R |= 0b00000010;      // enable clock UART1 (page 344)
//    GPIO_PORTB_AFSEL_R |= 0b00000011;      // sets PB0 and PB1 as peripherals (page 671)

//    GPIO_PORTB_PCTL_R  &= 0xFFFFFFF0;       // pmc0 and pmc1       (page 688)  also refer to page 650
//    GPIO_PORTB_PCTL_R  |= 0x000000FF;

//    GPIO_PORTB_DEN_R   |= 0b00000011;        // enables pb0 and pb1

//    GPIO_PORTB_DIR_R   |= 0b00000001;          // sets pb0 as output, pb1 as input
//    GPIO_PORTB_DIR_R   &= 0b11111101;

    SYSCTL_RCGCGPIO_R |= 0b000010;      // enable clock GPIOB (page 340)
    SYSCTL_RCGCUART_R |= 0b00000010;      // enable clock UART1 (page 344)
    GPIO_PORTB_AFSEL_R = 0b00000011;      // sets PB0 and PB1 as peripherals (page 671)
    GPIO_PORTB_PCTL_R  = 0x00000011;
    GPIO_PORTB_DEN_R   = 0b00000011;        // enables pb0 and pb1
    GPIO_PORTB_DIR_R   = 0b00000001;

    //compute baud values [UART clock= 16 MHz]
    double fbrd;
    int ibrd;
    double brd;


//    fbrd = (49/72) * 64 + 5; // page 903
    brd = 16000000.0/(16.0*baud);
    ibrd = (int)brd;
    fbrd = brd - ibrd; // page 903

    UART1_CTL_R &= 0xFFFE;      // disable UART1 (page 918)
    UART1_IBRD_R = ibrd;        // write integer portion of BRD to IBRD
    UART1_FBRD_R = (int)(fbrd * 64 + 0.5);   // write fractional portion of BRD to FBRD
    UART1_LCRH_R = 0b01100000;        // write serial communication parameters (page 916) * 8bit and no parity
    UART1_CC_R   = 0b00000000;          // use system clock as clock source (page 939)
    UART1_CTL_R |= 0x0001;        // enable UART1
}

void uart_sendChar(char data){
    while((UART1_FR_R & 0b00100000) != 0);
    UART1_DR_R = data;
}

//char uart_receive(void){
//
//
//    return (char)(UART1_DR_R & 0xFF);
//}

void uart_sendStr(const char *data){
	//TODO for reference see lcd_puts from lcd.c file
    while(*data != '\0')
    {
        uart_sendChar(*data);
        data++;
    }
}

void interrupt_init(void)
{
//    turn off uart1 while we set it up
    UART1_CTL_R &= 0xFFFE;

//    clear interrupt flag
    UART1_ICR_R |= 0x17F2;

//    enable send and receive raw interrupts
    UART1_IM_R |= 0x0030;

//    set priority of usart1 interrupt **
    NVIC_PRI1_R |= 0xFF1FFFFF;

//    enable interrupt for IRQ 6 **
    NVIC_EN0_R |= 0x0040;

    IntRegister(INT_UART1, UART1_Handler);

    IntMasterEnable();

//    re-enable RX, TX and uart1
    UART1_CTL_R |= 0x0301;

    uart_data = 0;
    flag = 0;
    mode_flag = 'm';

}

//void UART1_Handler(void){ (lab 6 part 1)
////    check if a receive byte IRQ has occurred
//    if(UART1_MIS_R & 0x0010){
//        //do something
//        uart_data = (char)(UART1_DR_R & 0xFF);
//        flag = 'r';
//        if((int)uart_data == 13)
//        {
//            uart_sendChar('\n');
//            uart_sendChar('\r');
//        }
//        else
//       {
//            uart_sendChar(uart_data);
//       }
//
////        clear the receive byte interrupt
//        UART1_ICR_R |= 0x00010;
//    }
//    else if(UART1_MIS_R & 0x0020){
//
//        UART1_ICR_R |= 0x00020;
//    }
//
//
//}



void UART1_Handler(void){
//    check if a receive byte IRQ has occurred
    if(UART1_MIS_R & 0x0010){
        //do something
        uart_data = (char)(UART1_DR_R & 0xFF);
        if(uart_data == 't')
        {
            switch (mode_flag){
            case 'm':
                mode_flag = 'a';
                break;
            case 'a':
                mode_flag = 'm';
                break;
            }
        }
        else
       {
            uart_sendChar(uart_data);
       }

//        clear the receive byte interrupt
        UART1_ICR_R |= 0x00010;
    }
    else if(UART1_MIS_R & 0x0020){

        UART1_ICR_R |= 0x00020;
    }


}

