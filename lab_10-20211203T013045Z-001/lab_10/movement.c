/*
 * movement.c
 *
 *  Created on: Sep 9, 2021
 *      Author: mdreeves
 */
#include "Timer.h"
#include "lcd.h"
#include "string.h"
#include "open_interface.h"
#include "movement.h"



    void straight(oi_t *sensor_data, double dist) {
        double sum = 0;
        oi_setWheels(400, 400); // move forward; full speed
        while (sum < dist) {
            oi_update(sensor_data);
            sum += sensor_data->distance;
        }
        oi_setWheels(0, 0); // stop
    }

    void back(oi_t *sensor_data, double dist) {
            double sum = 0;
            oi_setWheels(-400, -400); // move back; full speed
            while (sum > -dist) {
                oi_update(sensor_data);
                sum += sensor_data->distance;
            }
            oi_setWheels(0, 0); // stop
        }

    void moveWithObstacle(oi_t *sensor_data, double totalDist) {

        double distMoved = 0;
        double distToMove = totalDist;

        while(distMoved < distToMove) {

            oi_update(sensor_data);

            if (sensor_data->bumpLeft == 1) {
                distMoved -= 150;

                oi_update(sensor_data);

                back(sensor_data, 150);
                turn_right(sensor_data, 81.5);
                straight(sensor_data, 300);
                turn_left(sensor_data, 81.5);


            }
            else if (sensor_data->bumpRight == 1) {
                distMoved -= 150;

                oi_update(sensor_data);

                back(sensor_data, 150);
                turn_left(sensor_data, 81.5);
                straight(sensor_data, 300);
                turn_right(sensor_data, 81.5);

            }

            oi_setWheels(400, 400);
            distMoved += sensor_data->distance;
         }
    }

    void turn_right(oi_t *sensor_data, double deg) {
        double turn_angle = 0;
        while (turn_angle > -deg) {

            oi_setWheels(-100, 100);
            oi_update(sensor_data);
            turn_angle += sensor_data->angle;
            lcd_printf("%f", turn_angle);

        }

        oi_setWheels(0, 0); // stop

    }

    void turn_left(oi_t *sensor_data, double deg) {
            double turn_angle = 0;
            while (turn_angle < deg) {

                oi_setWheels(100, -100);
                oi_update(sensor_data);
                turn_angle += sensor_data->angle;
                lcd_printf("%f", turn_angle);

            }

            oi_setWheels(0, 0); // stop

        }



