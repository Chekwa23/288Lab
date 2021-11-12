//#include "open_interface.h"
//#include "timer.h"
//#include "lcd.h"
//#include "movement.h"
//#include "cyBot_uart.h"
//#include "cyBot_Scan.h"
//#include <math.h>
//#include <limits.h>
//#include "uart.h"
//#include "mission_helper.h"
//#include "adc.h"
//
//#define coeff_A -0.000617049
//#define coeff_B 0.026951788
//
//
////cyBOT_Scan_t cyBotScan;
//oi_t *sensor_data;
//extern volatile  char uart_data;
//extern volatile int measurement_flag;
//extern volatile  char mode_flag;
//
//
//void main()
//{
//    char msg[50];
//    lcd_init();
//    timer_init();
//    adc_init();
//    uart_init(115200);
//    interrupt_init();
//
//    while(1)
//    {
//        if(measurement_flag)
//        {
//
//            int value = adc_read();
////            double calibratedValue = (coeff_A*pow(value, 3))+(coeff_B*pow(value,2)) - (0.106*value) + 110.37;
//            double calibratedValue = 495898*(pow(value,-1.375));
//            sprintf(msg, "q: %d\t\t d:%f\n\r", value, calibratedValue);
//            lcd_printf(msg);
//            uart_sendStr(msg);
//            measurement_flag = 0;
//        }
//
//    }
//}


