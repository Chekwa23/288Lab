/*
 * lcd.h
 *
 *  Created on: 11/02/21
 *      Author: drodriguez & lchekwa
 */

void ping_timer3b_init(void);
int ping_read(void);
void send_pulse();
void TIMER3B_handler(void);
