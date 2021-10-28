///**
// * lab6_template_extra_help.c
// *
// * Description: This is file is meant for those that would like a little
// *              extra help with formatting their code.
// *
// */
//
//#define _RESET 0
//#define _PART1 0
//#define _PART2 0
//#define _PART3 1
//
//
//#include "timer.h"
//#include "lcd.h"
//#include "uart.h"
//
//#if _RESET
//#include "Simulation_User Files_resetSimulation.h"
//#endif
//
//// Adding global volatile varibles for communcating between
//// your Interupt Service Routine, and your non-interupt code.
//
//extern volatile  char uart_data;
//extern volatile  char flag;
//
//int counter;
//char bufferStr[21];
//
////void send(void){
////
////    char rxStr = uart_data;
////    if((int) rxStr == 13){
////        uart_sendChar('\n');
////        uart_sendChar(rxStr);
////    }
////    else{
////        uart_sendChar(rxStr);
////        lcd_printf("%c", rxStr);
////        timer_waitMillis(500);
////        lcd_printf("%d", ++counter);
////    }
////
////}
//
//void receive(void){
//
//    if(counter == 20){
//        lcd_printf("%s", bufferStr);
//    }
//    else
//    {
//        char rxStr = uart_data;
//        if((int) rxStr == 13 || counter == 20){ //makes no sense but shii
//            lcd_printf("%s", bufferStr);
//            memset(bufferStr, ' ', 20);
//            bufferStr[20] = '\0';
//            counter = 0;
//        }
//        else
//        {
//            bufferStr[counter] = rxStr;
//            lcd_printf("%c", rxStr);
//            timer_waitMillis(500);
//            lcd_printf("%d", ++counter);
//        }
//
//    }
//
//
//}
//
//void main()
//{
//#if _RESET
//    resetSimulationBoard();
//#else
//
//    timer_init();
//    lcd_init();
//    uart_init(115200);
//
//    counter = 0;
//    bufferStr[20] = '\0';
//
//    #if _PART1      // Receive and display text
//        // TODO
//    receive(void);
//
//
//    #endif
//
//    #if _PART2      // Echo Received Character
//        // TODO
//        send(void);
//
//    #endif
//
//    #if _PART3 // Receive and send characters using interrupts.
//     // TODO
//        interrupt_init();
//        while(1)
//        {
//
//            if(flag == 'r')
//            {
//                flag = 0;
//                if(counter == 20){
//                     lcd_printf("%s", bufferStr);
//                 }
//                 else
//                 {
//                     char rxStr = uart_data;
//                     if((int) rxStr == 13 || counter == 20){ //makes no sense but shii
//                         lcd_printf("%s", bufferStr);
//                         memset(bufferStr, ' ', 20);
//                         bufferStr[20] = '\0';
//                         counter = 0;
//                     }
//                     else
//                     {
//                         bufferStr[counter] = rxStr;
//                         lcd_printf("%c", rxStr);
//                         timer_waitMillis(500);
//                         lcd_printf("%d", ++counter);
//                     }
//
//                 }
//
//
//            }
//
//
//        }
//
//
//    #endif
//
//
//#endif
//}
//
