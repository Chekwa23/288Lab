/*
 * movement.h
 *
 *  Created on: Sep 9, 2021
 *      Author: mdreeves
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_
#include "open_interface.h"

void straight(oi_t *sensor_data, double dist);
void back(oi_t *sensor_data, double dist);
void moveWithObstacle(oi_t *sensor_data, double totalDist);
void turn_right(oi_t *sensor_data, double deg);
void turn_left(oi_t *sensor_data, double deg);



#endif /* MOVEMENT_H_ */
