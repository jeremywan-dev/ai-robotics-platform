# Hardware Design (V1)

## Design Principles

All hardware selections shall follow the project requirements:

- Reliable
- Modular and easy to extend
- Cost-effective

The selected hardware should not only satisfy the requirements of V1, but also provide a solid foundation for future versions of the robot, including Raspberry Pi integration, computer vision, and AI capabilities.

---

# Hardware Selection

## 1. Main Controller

### Selected Hardware

- STM32 NUCLEO-F446RE

### Reason

- Official ST development board
- Rich peripherals
- Excellent documentation
- Easy to debug
- Highly expandable

Status: ✅ Confirmed

---

## 2. Communication Module

### Selected Hardware

- ESP32 DevKit V1

### Reason

- Bluetooth
- Wi-Fi
- UART communication with STM32
- Future Raspberry Pi integration
- Supports wireless communication expansion

Status: ✅ Confirmed

---

## 3. Chassis

### Selected Hardware

- 4WD Aluminium Robot Chassis

### Reason

- Strong structure
- Standard mounting holes
- Easy to expand
- Suitable for future AI hardware

Status: ✅ Confirmed

---

## 4. Motors

### Selected Hardware

- TT Gear Motor
- 6V
- 1:48 Gear Ratio
- Quadrature Hall Encoder

### Reason

- Good balance between speed and torque
- Encoder supports closed-loop control
- Suitable for PID, odometry and navigation
- Standard TT mounting size
- Easy to replace or upgrade

Status: ✅ Confirmed

---

## 5. Motor Driver

### Selected Hardware

- 2 × TB6612FNG

### Reason

- High efficiency MOSFET driver
- Low heat generation
- Independent left/right motor control
- Better expandability than a single driver solution

Status: ✅ Confirmed

---

## 6. IMU

### Selected Hardware

- ICM-20948

### Reason

- 9-axis IMU
- I2C interface
- Supports future sensor fusion
- Suitable for autonomous navigation
- Long-term platform component

Status: ✅ Confirmed

---

## 7. Battery

### Selected Hardware

- 2 × 18650 Li-ion Batteries

### Reason

- Rechargeable
- High energy density
- Easy replacement
- Widely available

Status: ✅ Confirmed

---

## 8. Charging System

### Selected Hardware

- USB-C Charging Module with Integrated BMS

### Reason

- USB-C charging
- Rechargeable without removing batteries
- Battery protection
- Simple wiring
- Easy maintenance

Status: ✅ Confirmed

---

## 9. DC-DC Power Module

### Selected Hardware

- LM2596 Buck Converter

### Reason

- Efficient voltage conversion
- Stable 5V power supply
- Supports future hardware expansion

Status: ✅ Confirmed

---

## 10. Power Switch

### Selected Hardware

- Panel Mount Power Switch

### Reason

- Convenient system power control
- Simple installation
- Reliable operation

Status: ✅ Confirmed

---

## 11. Battery Indicator

### Selected Hardware

- LED Battery Level Indicator

### Reason

- Displays remaining battery level
- Easy charging management
- Improves user experience

Status: ✅ Confirmed

---

# Current Hardware BOM

| Component | Selected Hardware | Status |
|-----------|-------------------|--------|
| Main Controller | STM32 NUCLEO-F446RE | ✅ |
| Communication | ESP32 DevKit V1 | ✅ |
| Chassis | 4WD Aluminium Chassis | ✅ |
| Motors | TT Gear Motor (6V, 1:48, Quadrature Encoder) | ✅ |
| Motor Driver | 2 × TB6612FNG | ✅ |
| IMU | ICM-20948 | ✅ |
| Battery | 2 × 18650 Li-ion | ✅ |
| Charging | USB-C Charging Module with BMS | ✅ |
| DC-DC | LM2596 Buck Converter | ✅ |
| Power Switch | Panel Mount Switch | ✅ |
| Battery Indicator | LED Battery Indicator | ✅ |