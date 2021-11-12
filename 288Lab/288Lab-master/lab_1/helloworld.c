/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Describtion: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"
#include <stdio.h>
#include <string.h>

#define CYCLE 20
#define EMPTY ' '
#define END_STRING '\0'

int main (void) {
    int i;

    /* string that rotates on the screen + pointer to it */
//    char rotatingString[] = "Microcontrollers are lots of fun!";
    char rotatingString[] = "Microcontrollers are lots of fun!";
    char empty[] = "                   ";
    strcat(rotatingString, empty);
    char* rotatingStringPtr = rotatingString;
    int temp = 1;

//    /* initialize print string to all empty spaces */
//    char printString[21];
//    for(i = 0; i < CYCLE; i++)
//        printString[i] = EMPTY;
//
//    /* set null byte */
//    printString[CYCLE] = END_STRING;
//
//
//	timer_init(); // Initialize Timer, needed before any LCD screen fucntions can be called
//	              // and enables time functions (e.g. timer_waitMillis)
//	lcd_init();   // Initialize the the LCD screen.  This also clears the screen.

	while(1)
	{
	    /* initialize print string to all empty spaces */
	        char printString[21];
	        for(i = 0; i < CYCLE; i++)
	            printString[i] = EMPTY;

	        /* set null byte */
	        printString[CYCLE] = END_STRING;


	      timer_init(); // Initialize Timer, needed before any LCD screen fucntions can be called
	                    // and enables time functions (e.g. timer_waitMillis)
	      lcd_init();   // Initialize the the LCD screen.  This also clears the screen.
	      temp = 1;

	      while(temp){
	    /*.3 second sleep */
            timer_waitMillis(300);

            /* copy values at index 1 - 19 to index 0 - 18 */
            for(i = 0; i < CYCLE - 1; i++)
                printString[i] = printString[i+1];

            /* add new character to last index  */
            printString[CYCLE - 1] = (*rotatingStringPtr != END_STRING) ? *rotatingStringPtr : EMPTY;

            /* increment pointer */
            rotatingStringPtr = (*rotatingStringPtr != END_STRING) ? rotatingStringPtr + 1 : rotatingString;

            lcd_printf("%s", printString);

            if(*rotatingStringPtr == END_STRING ){
                temp = 0;
                timer_waitMillis(300);
            }
	    }
	}


	// Clear the LCD screen and print "Hello, world" on the LCD
//	lcd_printf("Hello, world");
//	lcd_puts("Microcontrollers are lots of fun!");


	// lcd_puts("Hello, world");// Replace lcd_printf with lcd_puts
                                 // step through in debug mode
                                 // and explain to TA how it
                                 // works


    
	// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
    // NOTE: For time fuctions see Timer.h

	return 0;
}
