#include "robot.h"

#include "control/control.h"

void Robot_SetMotion(Direction direction, uint8_t speed)
{
    int16_t front_left = 0;
    int16_t front_right = 0;
    int16_t rear_left = 0;
    int16_t rear_right = 0;
    int16_t target_speed = (int16_t)speed;

    switch (direction)
    {
        case DIRECTION_FORWARD:
            front_left = target_speed;
            front_right = target_speed;
            rear_left = target_speed;
            rear_right = target_speed;
            break;

        case DIRECTION_BACKWARD:
            front_left = -target_speed;
            front_right = -target_speed;
            rear_left = -target_speed;
            rear_right = -target_speed;
            break;

        case DIRECTION_LEFT:
            front_left = -target_speed;
            front_right = target_speed;
            rear_left = target_speed;
            rear_right = -target_speed;
            break;

        case DIRECTION_RIGHT:
            front_left = target_speed;
            front_right = -target_speed;
            rear_left = -target_speed;
            rear_right = target_speed;
            break;

        case DIRECTION_STOP:
        default:
            break;
    }

    Control_SetTargetWheelSpeeds(front_left, front_right, rear_left, rear_right);
}
