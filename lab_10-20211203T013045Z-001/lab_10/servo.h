
#ifndef SERVO_H_
#define SERVO_H_

#include <inc/tm4c123gh6pm.h>

void servo_init(void);

int servo_move(float degrees);


#endif /* SERVO_H_ */
