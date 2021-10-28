/*
*
*   uart.h
*
*   Used to set up the UART
*   uses UART1 at 115200
*
*
*   @author Dane Larson
*   @date 07/18/2016
*   Phillip Jones updated 9/2019, removed WiFi.h
*/

#ifndef UART_H_
#define UART_H_

#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include "driverlib/interrupt.h"
#include <stdint.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>

extern volatile  char uart_data;
extern volatile  char flag;

void uart_init(int baud);

void uart_sendChar(char data);

char uart_receive(void);

void uart_sendStr(const char *data);

void interrupt_init(void);

void UART1_Handler(void);


#endif /* UART_H_ */
