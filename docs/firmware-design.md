# Firmware Design

## 2026-08-05

### Motor API

Current API:

```c
void Motor_Init(void);
void Motor_SetSpeed(MotorId id, int8_t speed);
```
