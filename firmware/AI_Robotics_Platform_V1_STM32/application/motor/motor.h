#ifndef APPLICATION_MOTOR_MOTOR_H
#define APPLICATION_MOTOR_MOTOR_H

#include <stdint.h>

void Motor_Init(void);
void Motor_SetWheelOutputs(
    int16_t front_left,
    int16_t front_right,
    int16_t rear_left,
    int16_t rear_right);

#endif /* APPLICATION_MOTOR_MOTOR_H */
