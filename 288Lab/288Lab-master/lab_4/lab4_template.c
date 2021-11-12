/**
 * lab4_template.c
 * 
 * Template file for CprE 288 lab 4
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 */

#include "button.h"
#include "Timer.h"
#include "lcd.h"
#include "cyBot_uart.h"  // Functions for communiticate between CyBot and Putty (via UART)
                         // PuTTy: Buad=115200, 8 data bits, No Flow Control, No Party,  COM1

//#warning "Possible unimplemented functions"
#define REPLACEME 0

void print_data(char *strPtr){
    while(*strPtr != '\0')
    {
        cyBot_sendByte(*strPtr);
        strPtr++;
    }
    cyBot_sendByte('\n');
    cyBot_sendByte('\r');
}

int main(void) {
	button_init();
	lcd_init();
	cyBot_uart_init();
	// Don't forget to initialze the cyBot UART before trying to use it

	// YOUR CODE HERE
	while(1)
	{

      // YOUR CODE HERE
	    lcd_printf("%d", button_getButton());
	    char arr[10];
        sprintf(arr, "%d", button_getButton());
        print_data(arr);
	}

}
