#include "movement.h"

#define SPEED 300

/* This method moves the bot forward a distance, distance and bot sensor are given in parameters. */
//void move_foward(oi_t *sensor, int centimeters)
//{
//    /* keep track of distance traveled */
//    double sum = 0;
//    int distance = centimeters * 10;
//
//    /* put both wheels in forward motion  */
//    oi_setWheels(SPEED, SPEED);
//
//    /* check the progress of the bot, */
//    while (sum < distance)
//    {
//        oi_update(sensor);
//        sum += sensor->distance;
//        if (sensor->bumpLeft || sensor->bumpRight)
//        {
//            oi_setWheels(0, 0);
//            handle_bump(sensor, (distance - sum) / 10);
//            break;
//        }
//    }
//
//    oi_setWheels(0, 0);
//    oi_update(sensor);
//}

int move_foward(oi_t *sensor, int centimeters)
{
    /* keep track of distance traveled */
    double sum = 0;
    int distance = centimeters * 10;

    int bumpDir = 0;

    /* put both wheels in forward motion  */
    oi_setWheels(SPEED, SPEED);

    /* check the progress of the bot, */
    while (sum < distance)
    {www
        oi_update(sensor);
        sum += sensor->distance;
        if (sensor->bumpLeft || sensor->bumpRight)
        {
            if(sensor->bumpLeft) bumpDir = 1;
            else if(sensor->bumpRight) bumpDir = 2;

            oi_setWheels(0, 0);
            handle_bump(sensor, (distance - sum) / 10);
            break;
        }
    }

    oi_setWheels(0, 0);
    oi_update(sensor);

    return bumpDir;
}

void turn_clockwise(oi_t *sensor, int degrees)
{
    double curr_angle = 0.0;
    if (degrees > 0)
    {
        oi_setWheels(-100, 100);
        while (curr_angle < degrees)
        {
            oi_update(sensor);
            curr_angle += (sensor->angle * -1);
        }
    }
    else
    {
        oi_setWheels(100, -100); // move forward; full speed
        while (curr_angle > degrees)
        {
            oi_update(sensor);
            curr_angle -= sensor->angle;
        }
    }

    oi_setWheels(0, 0);
    oi_update(sensor);

}

void turn_counterClockwise(oi_t *sensor, int degrees)
{
    turn_clockwise(sensor, -degrees);
}

void backup(oi_t *sensor, int centimeters)
{
    double sum = 0;
    int distance = centimeters * 10;
    oi_setWheels(-SPEED, -SPEED);
    while (sum < distance)
    {
        oi_update(sensor);
        sum += (sensor->distance) * (-1);
    }

    oi_setWheels(0, 0);
    oi_update(sensor);
}

void handle_bump(oi_t *sensor, int distance_left)
{
    if (sensor->bumpLeft && sensor->bumpRight)
    {
        handle_both_bump(sensor);
    }
    else if (sensor->bumpLeft)
    {
        handle_right_bump(sensor);
    }
    else if (sensor->bumpRight)
    {
        handle_left_bump(sensor);
    }
    move_foward(sensor, distance_left + 15);
}

void handle_right_bump(oi_t *sensor)
{
    backup(sensor, 15);
    turn_clockwise(sensor, 90);
    move_foward(sensor, 25);
    turn_counterClockwise(sensor, 90);
}

void handle_left_bump(oi_t *sensor)
{
    backup(sensor, 15);
    turn_counterClockwise(sensor, 90);
    move_foward(sensor, 25);
    turn_clockwise(sensor, 90);
}

void handle_both_bump(oi_t *sensor)
{
    handle_left_bump(sensor);
}

void travel_to_object(oi_t *sensor, int distance)
{
       /* keep track of distance traveled */
       int y = 15;
       double sum = 0;
       double remaining_dist = distance * 10;
       int horizontal_dist = 0; // x < 0 object is left, x > 0 object is right

       /* put both wheels in forward motion  */
       oi_setWheels(SPEED, SPEED);

       /* check the progress of the bot, */
       while (remaining_dist > 0)
       {
           oi_update(sensor);
           remaining_dist -= sensor->distance;

        //   sum += sensor->distance;
           if (sensor->bumpLeft)
           {
               oi_setWheels(0, 0);
               backup(sensor, y);
               turn_clockwise(sensor, 90);

               travel_to_object(sensor, remaining_dist);
           }
           else if(sensor->bumpRight)
           {
               oi_setWheels(0, 0);
              backup(sensor, y);
              turn_counterClockwise(sensor, 90);
              travel_to_object(sensor, remaining_dist);
           }
       }

       oi_setWheels(0, 0);
       oi_update(sensor);
}





