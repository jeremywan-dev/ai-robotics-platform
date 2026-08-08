#include "motor.h"

#include "main.h"

extern TIM_HandleTypeDef htim3;

#define MOTOR_OUTPUT_MIN_PERCENT        (-100)
#define MOTOR_OUTPUT_MAX_PERCENT        (100)

/* Change an individual polarity after physical motor-direction testing. */
#define MOTOR_FRONT_LEFT_FORWARD_DIR    GPIO_PIN_SET
#define MOTOR_FRONT_RIGHT_FORWARD_DIR   GPIO_PIN_SET
#define MOTOR_REAR_LEFT_FORWARD_DIR     GPIO_PIN_SET
#define MOTOR_REAR_RIGHT_FORWARD_DIR    GPIO_PIN_SET

void Motor_Init(void)
{
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0U);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 0U);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 0U);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0U);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);

    if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3) != HAL_OK)
    {
        Error_Handler();
    }

    if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4) != HAL_OK)
    {
        Error_Handler();
    }
}

void Motor_SetWheelOutputs(
    int16_t front_left,
    int16_t front_right,
    int16_t rear_left,
    int16_t rear_right)
{
    uint32_t timer_arr = __HAL_TIM_GET_AUTORELOAD(&htim3);
    uint32_t front_left_magnitude;
    uint32_t front_right_magnitude;
    uint32_t rear_left_magnitude;
    uint32_t rear_right_magnitude;

    if (front_left > MOTOR_OUTPUT_MAX_PERCENT)
    {
        front_left = MOTOR_OUTPUT_MAX_PERCENT;
    }
    else if (front_left < MOTOR_OUTPUT_MIN_PERCENT)
    {
        front_left = MOTOR_OUTPUT_MIN_PERCENT;
    }

    if (front_right > MOTOR_OUTPUT_MAX_PERCENT)
    {
        front_right = MOTOR_OUTPUT_MAX_PERCENT;
    }
    else if (front_right < MOTOR_OUTPUT_MIN_PERCENT)
    {
        front_right = MOTOR_OUTPUT_MIN_PERCENT;
    }

    if (rear_left > MOTOR_OUTPUT_MAX_PERCENT)
    {
        rear_left = MOTOR_OUTPUT_MAX_PERCENT;
    }
    else if (rear_left < MOTOR_OUTPUT_MIN_PERCENT)
    {
        rear_left = MOTOR_OUTPUT_MIN_PERCENT;
    }

    if (rear_right > MOTOR_OUTPUT_MAX_PERCENT)
    {
        rear_right = MOTOR_OUTPUT_MAX_PERCENT;
    }
    else if (rear_right < MOTOR_OUTPUT_MIN_PERCENT)
    {
        rear_right = MOTOR_OUTPUT_MIN_PERCENT;
    }

    HAL_GPIO_WritePin(
        GPIOC,
        GPIO_PIN_0,
        (front_left < 0) ?
            (MOTOR_FRONT_LEFT_FORWARD_DIR == GPIO_PIN_SET ? GPIO_PIN_RESET : GPIO_PIN_SET) :
            MOTOR_FRONT_LEFT_FORWARD_DIR);
    HAL_GPIO_WritePin(
        GPIOC,
        GPIO_PIN_1,
        (front_right < 0) ?
            (MOTOR_FRONT_RIGHT_FORWARD_DIR == GPIO_PIN_SET ? GPIO_PIN_RESET : GPIO_PIN_SET) :
            MOTOR_FRONT_RIGHT_FORWARD_DIR);
    HAL_GPIO_WritePin(
        GPIOC,
        GPIO_PIN_2,
        (rear_left < 0) ?
            (MOTOR_REAR_LEFT_FORWARD_DIR == GPIO_PIN_SET ? GPIO_PIN_RESET : GPIO_PIN_SET) :
            MOTOR_REAR_LEFT_FORWARD_DIR);
    HAL_GPIO_WritePin(
        GPIOC,
        GPIO_PIN_3,
        (rear_right < 0) ?
            (MOTOR_REAR_RIGHT_FORWARD_DIR == GPIO_PIN_SET ? GPIO_PIN_RESET : GPIO_PIN_SET) :
            MOTOR_REAR_RIGHT_FORWARD_DIR);

    front_left_magnitude = (front_left < 0) ? (uint32_t)(-front_left) : (uint32_t)front_left;
    front_right_magnitude = (front_right < 0) ? (uint32_t)(-front_right) : (uint32_t)front_right;
    rear_left_magnitude = (rear_left < 0) ? (uint32_t)(-rear_left) : (uint32_t)rear_left;
    rear_right_magnitude = (rear_right < 0) ? (uint32_t)(-rear_right) : (uint32_t)rear_right;

    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, (front_left_magnitude * timer_arr) / 100U);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, (front_right_magnitude * timer_arr) / 100U);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, (rear_left_magnitude * timer_arr) / 100U);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, (rear_right_magnitude * timer_arr) / 100U);
}
