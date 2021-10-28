
#ifndef MISSION_HELPER_H_
#define MISSION_HELPER_H_

#include <stdint.h>
#include <inc/tm4c123gh6pm.h>
#include "open_interface.h"
#include "timer.h"
#include "lcd.h"
#include "movement.h"
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include <math.h>
#include <limits.h>
#include "uart.h"


void printResponse(char direction);

void print_data(char *strPtr);

int calculateWidth(int angleWidth, int a, int b);

void pointToObject(int angle, cyBOT_Scan_t* cyBotScan);

#endif /* BUTTON_H_ */
