/**
 * lab5_template.c
 *
 * Template file for CprE 288 lab 5
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 */

#include "button.h"
#include "timer.h"
#include "lcd.h"
#include <math.h>
#include "open_interface.h"

#include "cyBot_uart.h"  // Functions for communiticate between CyBot and Putty (via UART)
                         // PuTTy: Buad=115200, 8 data bits, No Flow Control, No Party,  COM1

#include "cyBot_Scan.h"  // For scan sensors



#define REPLACEME 0


// Defined in button.c : Used to communicate information between the
// the interupt handeler and main.
extern volatile int button_event;
extern volatile int button_num;

void print_data(char *strPtr){
    while(*strPtr != '\0')
    {
        cyBot_sendByte(*strPtr);
        strPtr++;
    }
    cyBot_sendByte('\n');
    cyBot_sendByte('\r');
}



double estimateDistance(float IR_Value){
    return (1*pow(10,-5)*pow(IR_Value,2))-(0.0626*IR_Value)+102.49;
}

//void print_values(cyBOT_Scan_t* cyBotScan)
//{
//    cyBot_uart_init();
//    char text[50];
//    int i;
//    for(i = 90; i <= 180; i+= 2)
//    {
//        /* scan for new sensor values */
//        cyBOT_Scan(i, cyBotScan);
//        int tempIR = cyBotScan->IR_raw_val;
//        float tempScan = cyBotScan->sound_dist;
//        sprintf(text, "%d\t\t%f\t\t%f", tempIR, estimateDistance(tempIR), tempScan );
////        sprintf(text, "%f\t\t%f", estimateDistance(tempIR), tempScan );
//        print_data(text);
//
//    }
//
//}

void print_values(cyBOT_Scan_t* cyBotScan)
{
    cyBot_uart_init();
    double sum;
    char text[50];
    int i;
    for(i = 0; i < 30; i++)
    {
        /* scan for new sensor values */
        cyBOT_Scan(115, cyBotScan);
        int tempIR = cyBotScan->IR_raw_val;
        sum += tempIR;
        float tempScan = cyBotScan->sound_dist;
        sprintf(text, "%d\t\t%f", tempIR, tempScan );
        print_data(text);

    }

    sprintf(text, "%f", sum/30);
    print_data(text);
}

double average(int angle, cyBOT_Scan_t* cyBotScan){
    int averageArr[10];
    double retVal;
    int i;
    for(i = 0; i < 10; i++ ){
        cyBOT_Scan(angle, cyBotScan);
        int tempIR = cyBotScan->IR_raw_val;
        retVal += estimateDistance(tempIR);
    }

    return retVal/10;
}

int main(void)
{
    cyBOT_Scan_t cyBotScan;
	button_init();
	init_button_interrupts();
	lcd_init();
	cyBOT_init_Scan();
	cyBot_uart_init();

//
//	cyBot_uart_init_clean();
//
//	SYSCTL_RCGCGPIO_R |= 0b0000010; // enable system clock for port B
//    timer_waitMillis(1);            // Small delay before accessing device after turning on clock
//    GPIO_PORTB_AFSEL_R |= 0b00000011;  // enable U1Rx and U1Tx for pin 0 and 1 of port B
//
//    GPIO_PORTB_PCTL_R &= 0x0011;
//    GPIO_PORTB_PCTL_R |= 0x0011;
//    GPIO_PORTB_DEN_R |= 0b00000011;
//    GPIO_PORTB_DIR_R &= 0b00000010;      // Force 0's in the disired locations
//    GPIO_PORTB_DIR_R |= 0b00000010;      // Force 1's in the disired locataions
//
//    cyBot_uart_init_last_half();

	while(1)
	{
//	    if(button_event)
//	    {
//	        lcd_printf("%d", button_num);
//            char arr[10];
//            sprintf(arr, "%d", button_num);
//            print_data(arr);
//            button_event = 0;
//	    }

	    int byte = cyBot_getByte();
        char character = (char) byte;
        if(character == 'r'){
//            print_values(&cyBotScan);

            char text[50];
            double temp = average(115, &cyBotScan);
            sprintf(text, "%f", temp );
            print_data(text);
        }

	}

}
