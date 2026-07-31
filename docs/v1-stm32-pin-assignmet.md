# Robot V1 - STM32 Pin Assignment

This document defines the STM32 peripheral allocation for Robot V1 and the corresponding physical pin locations on the NUCLEO-F446RE development board.

---

## Motor PWM (TIM3)

| Function | Peripheral | STM32 Pin | NUCLEO-F446RE Board |
|----------|------------|-----------|---------------------|
| Left Front Motor PWM | TIM3_CH1 | PA6 | Arduino **D12 (PA6)** |
| Right Front Motor PWM | TIM3_CH2 | PA7 | Arduino **D11 (PA7)** |
| Left Rear Motor PWM | TIM3_CH3 | PB0 | Arduino **A3 (PB0)** |
| Right Rear Motor PWM | TIM3_CH4 | PB1 | Morpho **CN10 Pin 24 (PB1)** |

---

## Motor Direction GPIO

| Function | STM32 Pin | NUCLEO-F446RE Board |
|----------|-----------|---------------------|
| Left Front Motor DIR | PC0 | Morpho **CN7 Pin 38 (PC0)** |
| Right Front Motor DIR | PC1 | Morpho **CN7 Pin 36 (PC1)** |
| Left Rear Motor DIR | PC2 | Morpho **CN7 Pin 35 (PC2)** |
| Right Rear Motor DIR | PC3 | Morpho **CN7 Pin 37 (PC3)** |

---

## Encoders

| Encoder | Peripheral | STM32 Pin | NUCLEO-F446RE Board |
|----------|------------|-----------|---------------------|
| Left Front Encoder CHA | TIM1_CH1 | PA8 | Arduino **D7 (PA8)** |
| Left Front Encoder CHB | TIM1_CH2 | PA9 | Arduino **D8 (PA9)** |
| Right Front Encoder CHA | TIM2_CH1 | PA15 | Morpho **CN7 Pin 17 (PA15)** |
| Right Front Encoder CHB | TIM2_CH2 | PB9 | Arduino **D14 (PB9)** |
| Left Rear Encoder CHA | TIM4_CH1 | PB6 | Arduino **D10 (PB6)** |
| Left Rear Encoder CHB | TIM4_CH2 | PB7 | Morpho **CN7 Pin 21 (PB7)** |
| Right Rear Encoder CHA | TIM5_CH1 | PA0 | Arduino **A0 (PA0)** |
| Right Rear Encoder CHB | TIM5_CH2 | PA1 | Arduino **A1 (PA1)** |

---

## UART

| Function | Peripheral | STM32 Pin | NUCLEO-F446RE Board |
|----------|------------|-----------|---------------------|
| ESP32 TX | USART2_TX | PA2 | Arduino **D1 / TX (PA2)** |
| ESP32 RX | USART2_RX | PA3 | Arduino **D0 / RX (PA3)** |

---

## Power

| Signal | NUCLEO-F446RE Board |
|--------|----------------------|
| 3.3 V | 3V3 Pin |
| 5 V | 5V Pin |
| Ground | GND Pin |

---

## Notes

- **STM32 Pin** is the MCU pin name used in STM32CubeMX, STM32 HAL and firmware development.
- **NUCLEO-F446RE Board** indicates the physical connector used when wiring the robot.
- **Arduino D/A** refers to the Arduino UNO R3 compatible headers.
- **Morpho CN7/CN10** refers to the ST Morpho expansion headers on the NUCLEO-F446RE.
- The **CN7/CN10 pin numbers** follow the official STMicroelectronics NUCLEO-F446RE User Manual (UM1724).


## Pin Summary

| STM32 Pin | Board Pin | Purpose |
|-----------|-----------|----------|
| PA6 | D12 | LF Motor PWM |
| PA7 | D11 | RF Motor PWM |
| PB0 | A3 | LR Motor PWM |
| PB1 | CN10-24 | RR Motor PWM |
| PC0 | CN7-38 | LF Motor DIR |
| PC1 | CN7-36 | RF Motor DIR |
| PC2 | CN7-35 | LR Motor DIR |
| PC3 | CN7-37 | RR Motor DIR |
| PA8 | D7 | LF Encoder CHA |
| PA9 | D8 | LF Encoder CHB |
| PA15 | CN7-17 | RF Encoder CHA |
| PB9 | D14 | RF Encoder CHB |
| PB6 | D10 | LR Encoder CHA |
| PB7 | CN7-21 | LR Encoder CHB |
| PA0 | A0 | RR Encoder CHA |
| PA1 | A1 | RR Encoder CHB |
| PA2 | D1 | ESP32 TX |
| PA3 | D0 | ESP32 RX |