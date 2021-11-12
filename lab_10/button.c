/*
 * button.c
 *
 *  Created on: Jul 18, 2016
 *      Author: Eric Middleton, Zhao Zhang, Chad Nelson, & Zachary Glanz.
 *
 *  @edit: Lindsey Sleeth and Sam Stifter on 02/04/2019
 *  @edit: Phillip Jone 05/30/2019: Mearged Spring 2019 version with Fall 2018
 */
 


//The buttons are on PORTE 3:0
// GPIO_PORTE_DATA_R -- Name of the memory mapped register for GPIO Port E, 
// which is connected to the push buttons
#include "button.h"


#define BUTTON_PORT GPIO_PORTE_DATA_R;

// Global varibles
volatile int *button_event;
volatile int *button_num;

/**
 * Initialize PORTE and configure bits 0-3 to be used as inputs for the buttons.
 */
void button_init() {
	static uint8_t initialized = 0;

	//Check if already initialized
	if(initialized){
		return;
	}

	// delete warning after implementing 
	#warning "Unimplemented function: void button_init()"
	
	// Reading: To initialize and configure GPIO PORTE, visit pg. 656 in the 
	// Tiva datasheet.
	
	// Follow steps in 10.3 for initialization and configuration. Some steps 
	// have been outlined below.
	
	// Ignore all other steps in initialization and configuration that are not 
	// listed below. You will learn more about additional steps in a later lab.

	// 1) Turn on PORTE system clock, do not modify other clock enables
	SYSCTL_RCGCGPIO_R |= 0b10000;

	// 2) Set the buttons as inputs, do not modify other PORTE wires
	GPIO_PORTE_DIR_R &= 0b110000;
	
	// 3) Enable digital functionality for button inputs, 
	//    do not modify other PORTE enables
	GPIO_PORTE_DEN_R |= 0b00001111;

	
	initialized = 1;
}



/**
 * Initialize and configure PORTE interupts
 */
void init_button_interrupts(int *button_event_addr, int *button_num_addr) {
    // Store the pointer to the given button_event boolean
    button_event = button_event_addr;
    // Store the pointer to the given button_num int
    button_num = button_num_addr;

    // Set up the GPIO pins
    button_init();

    // Disable interrupts on PB0-PB5 during setup
    GPIO_PORTE_IM_R &= ~0x3F;

    // Set pins 0-5 to use edge sensing
    GPIO_PORTE_IS_R &= 0b11110000;

    // Set pins 0-5 to use both edges. We want to update the LCD
    // when a button is pressed, and when the button is released.
    GPIO_PORTE_IBE_R |= 0x3F;

    // Clear the interrupts
    GPIO_PORTE_ICR_R |= 0x3F;

    // Unmask the bits for pins 0-5
    GPIO_PORTE_IM_R |= 0b00001111;

    // Enable GPIO port E interrupt
    NVIC_EN0_R |= 0b00010000;

    // Bind the interrupt to the handler.
    IntRegister(INT_GPIOE, gpioe_handler);
}

/**
 * Handles a hardware interrupt that occurs from a button being pressed
 */
void gpioe_handler() {

    // Clear interrupt status register
    GPIO_PORTE_ICR_R = 0x3F;

    // Set the button_event flag
    *button_event = 1;
    // Store the value of the highest button pressed at the given button_num address
    *button_num = button_getButton();
}

/**
 * returns a 6-bit bit field, representing the push buttons. A 1 means the corresponding button is pressed.
 */
uint8_t button_checkButtons()
{
    return (~GPIO_PORTE_DATA_R) & (0b01000000 - 1); //Return the button status
}

/**
 * Returns the position of the leftmost button being pushed.
 * @return the position of the leftmost button being pushed. A 6 is the leftmost button, 1 is the rightmost button. Return 0 if no button is being pressed.
 */
uint8_t button_getButton() {
    int i;
    for (i = 3; i >= 0 ; i--) {
        // Check each bit from bit 5 to bit 0
        if (~GPIO_PORTE_DATA_R & (1 << i)) {
            // Return the first bit that is set to 0
            return i + 1;
        }
    }
    // No bits 0 (no buttons pressed), return 0
    return 0;
}






