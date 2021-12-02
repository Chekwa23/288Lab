#define _PART1 0
#define _PART2 0


#define MAX_DEG 180.00
#define MIN_DEG 0.00



#include <math.h>
#include <stdio.h>
#include "servo.h"
#include "resetSimulation.h"




void main()   {
// #if _RESET
//     resetSimulationBoard();
// #else
//     timer_init();
//     lcd_init();

#if _PART1
    servo_init();
    lcd_printf("Done!");
#endif

#if _PART2
    volatile int button_event = 0;   // Track if button has been pressed
    volatile int button_pressed = 0; // Highest butotn pressed
    int direction = 1; // Move clockwise (-1) or counterclockwise (1)
    float degrees = MAX_DEG / 2.00; // Start at 90 degrees
    int register_val = 0;       // Value in the timer match register (24 bits)
    char str_buff[100];         // Buffer to hold the LCD output
    char *rotation_dir_str = "CCW"; // String for direction indication on LCD

    init_button_interrupts(&button_event, &button_pressed);
    //button_init();
    servo_init();

    while (1) {
        rotation_dir_str = (direction > 0 ? "CCW" : "CW");
        register_val = servo_move(degrees); // Update the servo

        sprintf(str_buff,"Direction: %s\nMatch Value:%d\nDegrees: %.2f\nButton: %d", rotation_dir_str, register_val, degrees, button_pressed);
        lcd_printf(str_buff); // Update the LCD

        if (button_event) {
            switch (button_pressed) {
            case 1:
                degrees += 1.0 * direction;
                break;
            case 2:
                degrees += 5.0 * direction;
                break;
            case 3:
                direction *= -1;
                break;
            default:
                break;
            }
            button_event = 0;
        }


        // Set max and min ranges
        if (degrees > 180) {
            degrees = 180;
        }
        else if (degrees < 0) {
            degrees = 0;
        }
    }
/*    servo_init();
    button_init();
    int positive = 1;
    float degrees = MAX_DEG / 2.00; // Start at 90 degrees
    int register_val = 0;       // Value in the timer match register (24 bits)
    char str_buff[100];         // Buffer to hold the LCD output
    char *rotation_dir_str = "CCW"; // String for direction indication on LCD


    char highVlow = '+';
    int num;
    int newMatchVal;
    while (1)  {

        num = button_getButton();

        if (num == 1)   {
            degrees+=1;
            servo_move(degrees);
        }
        else if (num == 2)   {
            servo_move(degrees+=5);
        }


        else if (num == 3)   {
            if (positive == 1)   {
                positive = -1;
                highVlow = '-';
            }
            else   {
                positive = 1;
                highVlow = '+';
            }
        }
        else if (num == 4)   {

        }
    }
*/
#endif

#endif
}


/*
int main(void) {
    volatile int button_event = 0;   // Track if button has been pressed
    volatile int button_pressed = 0; // Highest butotn pressed
    int direction = 1; // Move clockwise (-1) or counterclockwise (1)
    float degrees = MAX_DEG / 2.00; // Start at 90 degrees
    int register_val = 0;       // Value in the timer match register (24 bits)
    char str_buff[100];         // Buffer to hold the LCD output
    char *rotation_dir_str = "CCW"; // String for direction indication on LCD

    init_button_interrupts(&button_event, &button_pressed);
    servo_init();
    lcd_init();
    timer_init();

    while (1) {
        rotation_dir_str = (direction > 0 ? "CCW" : "CW");
        register_val = servo_move(degrees); // Update the servo

        sprintf(str_buff,
                "Direction: %s\nMatch Value:%d\nDegrees: %.2f\nButton: %d",
                rotation_dir_str, register_val, degrees, button_pressed);
        lcd_printf(str_buff); // Update the LCD

        if (button_event) {
            switch (button_pressed) {
            case 1: // Button 1
                degrees += 1.0 * direction;
                break;
            case 2: // Button 2
                degrees += 5.0 * direction;
                break;
            case 3: // Button 3
                direction *= -1;
                break;
            default: // Button 0
                break;
            }
            button_event = 0;
        }

        // Set max and min ranges
        if (degrees > 180) {
            degrees = 180;
        }
        else if (degrees < 0) {
            degrees = 0;
        }
    }
}*/

