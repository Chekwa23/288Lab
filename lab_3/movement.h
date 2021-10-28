//#ifndef MOVEMENT_H_
//#define MOVEMENT_H_

#include "open_interface.h"


int move_foward(oi_t *sensor, int centimeters);
void turn_clockwise(oi_t *sensor, int degrees);
void backup(oi_t *sensor, int centimeters);
void turn_counterClockwise(oi_t *sensor, int degrees);
void handle_bump(oi_t *sensor, int distance_left);
void handle_both_bump(oi_t *sensor);
void handle_left_bump(oi_t *sensor);
void handle_right_bump(oi_t *sensor);
