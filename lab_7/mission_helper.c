#include "open_interface.h"
#include "timer.h"
#include "lcd.h"
#include "movement.h"
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include <math.h>
#include <limits.h>
#include "uart.h"

void printResponse(char direction)
{
      char sendBack[] = "Got an ";
      char* sendBackPtr = sendBack;

      uart_sendStr(sendBackPtr);
      uart_sendChar(direction);
      uart_sendChar('\n');
      uart_sendChar('\r');
}

void print_data(char *strPtr){
    uart_sendStr(strPtr);
    uart_sendChar('\n');
    uart_sendChar('\r');
}

int calculateWidth(int angleWidth, int a, int b){

    double rad = (angleWidth * (M_PI))/180;
    double cosC = cos(rad);
    double c_sq = b*b + a*a - 2*a*b*cosC;
    double c = sqrt(c_sq);
    int retVal = (int)ceil(c);

    return retVal;
}


void pointToObject(int angle, cyBOT_Scan_t* cyBotScan){
    cyBOT_Scan(angle, cyBotScan);
}

//void printResponse(char direction)
//{
//      char sendBack[] = "Got an ";
//      char* sendBackPtr = sendBack;
//      while(*sendBackPtr != '\0')
//      {
//
//          cyBot_sendByte(*sendBackPtr);
//          sendBackPtr++;
//      }
//      cyBot_sendByte(direction);
//      cyBot_sendByte('\n');
//      cyBot_sendByte('\r');
//}
//
//void print_data(char *strPtr){
//    while(*strPtr != '\0')
//    {
//        cyBot_sendByte(*strPtr);
//        strPtr++;
//    }
//    cyBot_sendByte('\n');
//    cyBot_sendByte('\r');
//}
//
//int calculateWidth(int angleWidth, int a, int b){
//
//    double rad = (angleWidth * (M_PI))/180;
//    double cosC = cos(rad);
//    double c_sq = b*b + a*a - 2*a*b*cosC;
//    double c = sqrt(c_sq);
//    int retVal = (int)ceil(c);
//
//    return retVal;
//}
//
//
//void pointToObject(int angle, cyBOT_Scan_t* cyBotScan){
//    cyBOT_Scan(angle, cyBotScan);
//}
