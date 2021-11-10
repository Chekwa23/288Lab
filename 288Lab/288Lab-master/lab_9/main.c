#include "open_interface.h"
#include "timer.h"
#include "lcd.h"
#include "movement.h"
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include "uart.h"
#include "mission_helper.h"
#include "adc.h"
#include "ping.h"



void main()
{
    int ping_distance = 0;
    ping_timer3b_init();

    while(1)
    {
        timer_waitMillis(1000);
        ping_distance = ping_read();
    }
}


