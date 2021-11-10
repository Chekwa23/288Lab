#include "open_interface.h"
#include "timer.h"
#include "lcd.h"
#include "movement.h"


void main()
{
    int byte;

    lcd_init();
    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);




//    move_foward(sensor_data, 200);

    oi_free(sensor_data);

}
