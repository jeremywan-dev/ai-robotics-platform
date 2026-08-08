#include "communication.h"

#include "main.h"
#include "robot/robot.h"

#define COMMUNICATION_RX_BUFFER_SIZE       (16U)
#define COMMUNICATION_MAX_SPEED_PERCENT    (100U)

extern UART_HandleTypeDef huart2;

static uint8_t communication_rx_byte;
static char communication_rx_buffer[COMMUNICATION_RX_BUFFER_SIZE];
static volatile uint8_t communication_rx_length;
static volatile uint8_t communication_command_ready;
static volatile uint8_t communication_discard_until_newline;

static uint8_t Communication_ParseCommand(Direction *direction, uint8_t *speed);
static void Communication_StartReceive(void);

void Communication_Init(void)
{
    communication_rx_length = 0U;
    communication_command_ready = 0U;
    communication_discard_until_newline = 0U;

    Communication_StartReceive();
}

void Communication_Update(void)
{
    Direction direction;
    uint8_t speed;

    if (communication_command_ready == 0U)
    {
        return;
    }

    if (Communication_ParseCommand(&direction, &speed) != 0U)
    {
        Robot_SetMotion(direction, speed);
    }

    communication_rx_length = 0U;
    communication_command_ready = 0U;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance != USART2)
    {
        return;
    }

    if (communication_command_ready == 0U)
    {
        if (communication_rx_byte == '\n')
        {
            if ((communication_rx_length > 0U) &&
                (communication_discard_until_newline == 0U))
            {
                communication_rx_buffer[communication_rx_length] = '\0';
                communication_command_ready = 1U;
            }

            communication_rx_length = 0U;
            communication_discard_until_newline = 0U;
        }
        else if (communication_rx_byte != '\r')
        {
            if (communication_discard_until_newline == 0U)
            {
                if (communication_rx_length < (COMMUNICATION_RX_BUFFER_SIZE - 1U))
                {
                    communication_rx_buffer[communication_rx_length] =
                        (char)communication_rx_byte;
                    communication_rx_length++;
                }
                else
                {
                    communication_rx_length = 0U;
                    communication_discard_until_newline = 1U;
                }
            }
        }
    }

    Communication_StartReceive();
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        communication_rx_length = 0U;
        communication_command_ready = 0U;
        communication_discard_until_newline = 0U;

        if (HAL_UART_GetState(&huart2) == HAL_UART_STATE_READY)
        {
            Communication_StartReceive();
        }
    }
}

static uint8_t Communication_ParseCommand(Direction *direction, uint8_t *speed)
{
    uint8_t index = 2U;
    uint8_t parsed_speed = 0U;
    uint8_t digit_count = 0U;

    if ((communication_rx_buffer[1] != ',') ||
        (communication_rx_buffer[0] == '\0'))
    {
        return 0U;
    }

    switch (communication_rx_buffer[0])
    {
        case 'F':
            *direction = DIRECTION_FORWARD;
            break;

        case 'B':
            *direction = DIRECTION_BACKWARD;
            break;

        case 'L':
            *direction = DIRECTION_LEFT;
            break;

        case 'R':
            *direction = DIRECTION_RIGHT;
            break;

        case 'S':
            *direction = DIRECTION_STOP;
            break;

        default:
            return 0U;
    }

    while (communication_rx_buffer[index] != '\0')
    {
        if ((communication_rx_buffer[index] < '0') ||
            (communication_rx_buffer[index] > '9'))
        {
            return 0U;
        }

        if (parsed_speed > ((COMMUNICATION_MAX_SPEED_PERCENT -
                             (uint8_t)(communication_rx_buffer[index] - '0')) / 10U))
        {
            return 0U;
        }

        parsed_speed = (uint8_t)((parsed_speed * 10U) +
                                 (uint8_t)(communication_rx_buffer[index] - '0'));
        digit_count++;
        index++;
    }

    if ((digit_count == 0U) || (parsed_speed > COMMUNICATION_MAX_SPEED_PERCENT))
    {
        return 0U;
    }

    if ((*direction == DIRECTION_STOP) && (parsed_speed != 0U))
    {
        return 0U;
    }

    *speed = parsed_speed;
    return 1U;
}

static void Communication_StartReceive(void)
{
    if (HAL_UART_Receive_IT(&huart2, &communication_rx_byte, 1U) != HAL_OK)
    {
        Error_Handler();
    }
}
