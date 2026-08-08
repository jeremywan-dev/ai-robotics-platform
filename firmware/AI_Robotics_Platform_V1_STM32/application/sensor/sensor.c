#include "sensor.h"

#include "main.h"

typedef struct
{
    int16_t front_left;
    int16_t front_right;
    int16_t rear_left;
    int16_t rear_right;
} WheelSpeeds;

typedef struct
{
    uint32_t front_left;
    uint32_t front_right;
    uint32_t rear_left;
    uint32_t rear_right;
} EncoderCounts;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;

static WheelSpeeds sensor_wheel_speeds;
static EncoderCounts sensor_raw_counts;
static uint8_t sensor_measurements_valid;

void Sensor_Init(void)
{
    sensor_wheel_speeds = (WheelSpeeds){0};
    sensor_raw_counts = (EncoderCounts){0};
    sensor_measurements_valid = 0U;

    if (HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL) != HAL_OK)
    {
        Error_Handler();
    }
}

void Sensor_Update(void)
{
    sensor_raw_counts.front_left = __HAL_TIM_GET_COUNTER(&htim1);
    sensor_raw_counts.front_right = __HAL_TIM_GET_COUNTER(&htim2);
    sensor_raw_counts.rear_left = __HAL_TIM_GET_COUNTER(&htim4);
    sensor_raw_counts.rear_right = __HAL_TIM_GET_COUNTER(&htim5);

    /* Encoder scaling and speed calculation await the final encoder hardware. */
    sensor_measurements_valid = 0U;
}

uint8_t Sensor_GetWheelSpeeds(
    int16_t *front_left,
    int16_t *front_right,
    int16_t *rear_left,
    int16_t *rear_right)
{
    if ((front_left == NULL) || (front_right == NULL) ||
        (rear_left == NULL) || (rear_right == NULL) ||
        (sensor_measurements_valid == 0U))
    {
        return 0U;
    }

    *front_left = sensor_wheel_speeds.front_left;
    *front_right = sensor_wheel_speeds.front_right;
    *rear_left = sensor_wheel_speeds.rear_left;
    *rear_right = sensor_wheel_speeds.rear_right;

    return 1U;
}
