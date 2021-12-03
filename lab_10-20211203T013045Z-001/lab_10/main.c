#include "Timer.h"
#include "lcd.h"
#include "math.h"
#include "servo.h"

int main (void) {

    timer_init();
    servo_init();

    while(1) {
    servo_move(0);
    }
}
