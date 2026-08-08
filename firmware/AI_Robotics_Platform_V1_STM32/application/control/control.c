#include "control.h"

#include "motor/motor.h"
#include "sensor/sensor.h"

#define CONTROL_KP                         (0.0F)
#define CONTROL_KI                         (0.0F)
#define CONTROL_KD                         (0.0F)
#define CONTROL_LOOP_PERIOD_SECONDS        (0.0F)
#define CONTROL_MOTOR_OUTPUT_LIMIT         (100.0F)

typedef struct
{
    int16_t front_left;
    int16_t front_right;
    int16_t rear_left;
    int16_t rear_right;
} WheelSpeeds;

typedef struct
{
    float integral;
    float previous_error;
} PIDState;

static WheelSpeeds control_target_speeds;
static PIDState control_front_left_pid;
static PIDState control_front_right_pid;
static PIDState control_rear_left_pid;
static PIDState control_rear_right_pid;

static uint8_t Control_ReadMeasuredWheelSpeeds(WheelSpeeds *measured_speeds)
{
    return Sensor_GetWheelSpeeds(
        &measured_speeds->front_left,
        &measured_speeds->front_right,
        &measured_speeds->rear_left,
        &measured_speeds->rear_right);
}

static float Control_CalculatePid(float target, float measured, PIDState *state)
{
    float error = target - measured;
    float derivative = 0.0F;

    if (CONTROL_LOOP_PERIOD_SECONDS > 0.0F)
    {
        state->integral += error * CONTROL_LOOP_PERIOD_SECONDS;
        derivative = (error - state->previous_error) / CONTROL_LOOP_PERIOD_SECONDS;
    }

    state->previous_error = error;

    return (CONTROL_KP * error) + (CONTROL_KI * state->integral) + (CONTROL_KD * derivative);
}

static int16_t Control_ClampMotorOutput(float output)
{
    if (output > CONTROL_MOTOR_OUTPUT_LIMIT)
    {
        return 100;
    }

    if (output < -CONTROL_MOTOR_OUTPUT_LIMIT)
    {
        return -100;
    }

    return (int16_t)output;
}

void Control_Init(void)
{
    control_target_speeds = (WheelSpeeds){0};
    control_front_left_pid = (PIDState){0};
    control_front_right_pid = (PIDState){0};
    control_rear_left_pid = (PIDState){0};
    control_rear_right_pid = (PIDState){0};
}

void Control_SetTargetWheelSpeeds(
    int16_t front_left,
    int16_t front_right,
    int16_t rear_left,
    int16_t rear_right)
{
    control_target_speeds.front_left = front_left;
    control_target_speeds.front_right = front_right;
    control_target_speeds.rear_left = rear_left;
    control_target_speeds.rear_right = rear_right;
}

void Control_Update(void)
{
    WheelSpeeds measured_speeds;
    int16_t front_left_output;
    int16_t front_right_output;
    int16_t rear_left_output;
    int16_t rear_right_output;

    if (Control_ReadMeasuredWheelSpeeds(&measured_speeds) == 0U)
    {
        Motor_SetWheelOutputs(0, 0, 0, 0);
        return;
    }

    front_left_output = Control_ClampMotorOutput(
        Control_CalculatePid(
            (float)control_target_speeds.front_left,
            (float)measured_speeds.front_left,
            &control_front_left_pid));
    front_right_output = Control_ClampMotorOutput(
        Control_CalculatePid(
            (float)control_target_speeds.front_right,
            (float)measured_speeds.front_right,
            &control_front_right_pid));
    rear_left_output = Control_ClampMotorOutput(
        Control_CalculatePid(
            (float)control_target_speeds.rear_left,
            (float)measured_speeds.rear_left,
            &control_rear_left_pid));
    rear_right_output = Control_ClampMotorOutput(
        Control_CalculatePid(
            (float)control_target_speeds.rear_right,
            (float)measured_speeds.rear_right,
            &control_rear_right_pid));

    Motor_SetWheelOutputs(
        front_left_output,
        front_right_output,
        rear_left_output,
        rear_right_output);
}
