#ifndef __Gimbal_H
#define __Gimbal_H



#include <stdio.h>
#include <stdint.h>



typedef uint16_t (*gimbal_get_value_t)(void);

typedef struct gimbal_driver_s{
    gimbal_get_value_t      _getX;
    gimbal_get_value_t      _getY;
}gimbal_driver_t;



#endif /* __Gimbal_H */
