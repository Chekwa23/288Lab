#include "open_interface.h"
#include "timer.h"
#include "lcd.h"
#include "movement.h"
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include <math.h>
#include <limits.h>

#define MIN_DIST 75
#define MIN_IR_VAL 850
#define MIN_IR_DELTA_UPPER 140
#define MIN_IR_DELTA_LOWER 120
#define MIN_WIDTH 5
#define MAX_WIDTH 27

typedef struct{
    int x1;
    int x2;

    int dist1;
    int dist2;
}objSize;

typedef struct{
    int angle;
    int width;
    int distance;
    int scan_id;
}object;


void printResponse(char direction)
{
      char sendBack[] = "Got an ";
      char* sendBackPtr = sendBack;
      while(*sendBackPtr != '\0')
      {
          cyBot_sendByte(*sendBackPtr);
          sendBackPtr++;
      }
      cyBot_sendByte(direction);
      cyBot_sendByte('\n');
      cyBot_sendByte('\r');

}

void print_data(char *strPtr){
    while(*strPtr != '\0')
    {
        cyBot_sendByte(*strPtr);
        strPtr++;
    }
    cyBot_sendByte('\n');
    cyBot_sendByte('\r');
}

int calculateWidth(int angleWidth, int a, int b){

    double rad = (angleWidth * (M_PI))/180;
    double cosC = cos(rad);
    double c_sq = b*b + a*a - 2*a*b*cosC;
    double c = sqrt(c_sq);
    int retVal = (int)ceil(c);

    return retVal;
}


object* scan_for_objects(cyBOT_Scan_t* cyBotScan, int* objectCount, int scan_id)
{
    object* smallestObject; // smallest object found data (return value)
    int smallest; // smallest width of objects found
    int curr_IR, prev_IR, curr_dist, prev_dist; // most recent and last scan values
    int foundObject = 0;
    int x1, x2, d1, d2, x1_backup, d1_backup; // start and end distance and angle of most recent object found
    int i; // loop variable
    char text[100]; // print statement (for debugging)

    /* init variables */
    smallestObject = malloc(sizeof(object));
    smallestObject->width = INT_MAX;
    smallestObject->angle = 360;
    smallestObject->distance = 0;
    smallestObject->scan_id = scan_id;

    smallest = INT_MAX;

    curr_IR = INT_MAX;
    prev_IR = INT_MAX;
    curr_dist = INT_MAX;
    prev_dist = INT_MAX;

    d1 = INT_MAX;
    d2 = INT_MAX;
    x1 = 0;
    x2 = 0;

    for(i = 0; i <= 180; i+= 2)
    {
        x1_backup = x1;
        d1_backup = d1;

        /* scan for new sensor values */
        cyBOT_Scan(i, cyBotScan);
        curr_IR = cyBotScan->IR_raw_val;
        curr_dist = (int)cyBotScan->sound_dist;


        if(!foundObject && (curr_dist < MIN_DIST || d2 < MIN_DIST) && (curr_IR - prev_IR > MIN_IR_DELTA_UPPER) && (curr_IR > MIN_IR_VAL))
        {
            foundObject = 1;
            lcd_printf("%d", i);
            x1 = i;
            d1 = curr_dist;
        }
        else if(foundObject && ((prev_IR - curr_IR > MIN_IR_DELTA_UPPER) || (prev_IR - curr_IR > MIN_IR_DELTA_LOWER && curr_IR < MIN_IR_VAL && prev_IR > MIN_IR_VAL)) )
        {

            int width = calculateWidth(x2 - x1, d1, d2);
            if(width < MIN_WIDTH) // false end
            {
                x1 = x1_backup;
                d1 = d1_backup;
            }
            else
            {
                if(width < MAX_WIDTH) // found reasonable end object width
                {
                    foundObject = 0;
                    (*objectCount)++;
                    sprintf(text, "%d \t\t %d \t\t %d \t\t %d", (*objectCount), x2, d2, width);
                    print_data(text);
                    if(smallest > width){
                         smallest = width;
                         smallestObject->width = width;
                         smallestObject->angle = x1 + ((x2 - x1)/2);
                         smallestObject->distance = d2;
                    }
                }
                x1 = i;
                d1 = d2;
            }

        }

       // sprintf(text, "angle: %d\t\t distance: %d\t\t ir_val: %d\t\t",i, curr_dist, curr_IR);
      // print_data(text);

        /* updated running values */
        x2 = i;
        d2 = curr_dist;
        prev_IR = curr_IR;
    }

//    free(smallestObject);

    return smallestObject;
}


void pointToObject(int angle, cyBOT_Scan_t* cyBotScan){
 //   cyBOT_init_Scan();
    cyBOT_Scan(angle, cyBotScan);
}

void main()
{
    timer_init();
    lcd_init();
//    uart_init(115200);


    cyBOT_Scan_t cyBotScan;
    oi_t *sensor_data = oi_alloc();
    int* objectCount = 0;
    char msg[100]; // print statement (for debugging)


    lcd_init();
    oi_init(sensor_data);
    cyBot_uart_init();
    cyBOT_init_Scan();

     while(1)
     {
         int byte = cyBot_getByte();
         lcd_printf("%c", byte);
         char character = (char) byte;

         switch(character)
         {
              case 'w' :
                  printResponse(character);
                  move_foward(sensor_data, 100);
                  break;
              case 's' :
                 printResponse(character);
                 backup(sensor_data, 100);
                  break;
              case 'a' :
                  printResponse(character);
                  turn_counterClockwise(sensor_data, 90);
                  move_foward(sensor_data, 100);
                  break;
              case 'd' :
                  printResponse(character);
                  turn_clockwise(sensor_data, 90);
                  move_foward(sensor_data, 100);
                  break;
              case 'm' :
                  print_data("Object# \t Angle \t Distance (cm) \t Width");
                  object* goToObj1 = scan_for_objects(&cyBotScan, &objectCount, 1);
                  turn_counterClockwise(sensor_data, 180);
                  object* goToObj2 = scan_for_objects(&cyBotScan, &objectCount, 2);

                  if(objectCount != 0)
                  {
                      int width = (goToObj1->width >= goToObj2->width) ? goToObj2->width : goToObj1->width;
                    int distance = (goToObj1->width >= goToObj2->width) ? goToObj2->distance : goToObj1->distance;
                    int angle = (goToObj1->width >= goToObj2->width) ? goToObj2->angle : goToObj1->angle;
                    if(angle == 360) break;
                    int scan_id = (goToObj1->width >= goToObj2->width) ? 2 : 1;
                    if(scan_id == 1) turn_counterClockwise(sensor_data, 180);

                    sprintf(msg,"Smallest object: scan_id=%d\t width=%d\t angle=%d\t", scan_id, width, angle);
                    print_data(msg);
                    pointToObject(angle, &cyBotScan);

                    if(angle > 90)
                    {
                        turn_clockwise(sensor_data, angle - 90);
                    }
                    else
                    {
                        turn_counterClockwise(sensor_data, 90-angle);
                    }

                    int bumpDir = move_foward(sensor_data, distance - 15);
                    if(bumpDir != 0){
                        if(bumpDir == 1){
                            turn_counterClockwise(sensor_data, 90);
                            move_foward(sensor_data, 25);
                            turn_clockwise(sensor_data, 90);
                        }
                        else if(bumpDir == 2){
                            turn_clockwise(sensor_data, 90);
                            move_foward(sensor_data, 25);
                            turn_counterClockwise(sensor_data, 90);
                        }
                    }
                  }


        //          cyBot_sendByte();
                  free(goToObj1);
                  free(goToObj2);


                  break;

         }
     }


     oi_free(sensor_data);
}
