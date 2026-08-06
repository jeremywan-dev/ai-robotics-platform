# Firmware API Design

## Communication

Responsibility: continuously receive and parse movement commands from the ESP32.

```c
void Communication_Init(void);
void Communication_Update(void);
```

When a valid movement command is received, `Communication_Update()` calls `Robot_SetMotion(direction, speed)`.

## Robot

Responsibility: convert robot-level movement commands into four target wheel speeds.

```c
void Robot_Init(void);

void Robot_SetMotion(
    Direction direction,
    uint8_t speed
);
```

`Robot_SetMotion()` is event-driven. It stores the requested direction and speed, converts the requested motion into four target wheel speeds, and calls `Control_SetTargetWheelSpeeds()`. Robot currently has no periodic task, so it does not require `Robot_Update()`.

## Control

Responsibility: use encoder feedback and PID control to make each wheel reach its target speed.

```c
void Control_Init(void);

void Control_SetTargetWheelSpeeds(
    int16_t front_left,
    int16_t front_right,
    int16_t rear_left,
    int16_t rear_right
);

void Control_Update(void);
```

`Control_SetTargetWheelSpeeds()` stores the four target wheel speeds. `Control_Update()` runs periodically: it reads the latest measured wheel speeds from Sensor, compares them with the targets, runs four PID controllers, calculates four signed motor outputs, and calls `Motor_SetWheelOutputs()`.

## Sensor

Responsibility: continuously update encoder measurements and provide the latest measured wheel speeds.

The getter API is provisional because it depends on the final encoder implementation and speed-calculation method.

```c
void Sensor_Init(void);
void Sensor_Update(void);

/* Provisional */
void Sensor_GetWheelSpeeds(...);
```

## Motor

Responsibility: convert four signed control outputs into PWM and direction signals for the DRV8833 motor drivers.

```c
void Motor_Init(void);

void Motor_SetWheelOutputs(
    int16_t front_left,
    int16_t front_right,
    int16_t rear_left,
    int16_t rear_right
);
```

The parameters are signed motor control outputs, not measured wheel speeds or target wheel speeds: positive is forward output, negative is reverse output, and zero is no drive output. The final numeric range will be defined during implementation.

## Runtime Behaviour

Periodic execution:

```c
while (1)
{
    Communication_Update();
    Sensor_Update();
    Control_Update();
}
```

Event-driven call chain when a valid command arrives:

```text
Communication_Update()
    -> Robot_SetMotion()
    -> Control_SetTargetWheelSpeeds()
```

Continuous closed-loop control:

```text
Sensor_Update()
    -> Sensor stores the latest encoder measurements

Control_Update()
    -> reads measured wheel speeds from Sensor
    -> runs PID
    -> calls Motor_SetWheelOutputs()
```
