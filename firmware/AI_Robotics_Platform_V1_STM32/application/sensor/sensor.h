#ifndef APPLICATION_SENSOR_SENSOR_H
#define APPLICATION_SENSOR_SENSOR_H

#include <stdint.h>

void Sensor_Init(void);
void Sensor_Update(void);

uint8_t Sensor_GetWheelSpeeds(
    int16_t *front_left,
    int16_t *front_right,
    int16_t *rear_left,
    int16_t *rear_right);

#endif /* APPLICATION_SENSOR_SENSOR_H */
