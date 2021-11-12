/*
 * servo.h
 *
 *  Created on: Oct 22, 2020
 *      Author: bruceb1
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "Timer.h"
#include "lcd.h"


#ifndef SERVO_H_
#define SERVO_H_

void servo_init(void);

int servo_move(float degrees);



#endif /* SERVO_H_ */
