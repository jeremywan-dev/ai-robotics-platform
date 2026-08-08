#ifndef APPLICATION_CONTROL_CONTROL_H
#define APPLICATION_CONTROL_CONTROL_H

#include <stdint.h>

void Control_Init(void);
void Control_SetTargetWheelSpeeds(
    int16_t front_left,
    int16_t front_right,
    int16_t rear_left,
    int16_t rear_right);
void Control_Update(void);

#endif /* APPLICATION_CONTROL_CONTROL_H */
