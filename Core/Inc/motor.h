#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "main.h"

void MotorPWM_Start(void);
void MOTOR_A_SetSpeed(int16_t speed);
void MOTOR_B_SetSpeed(int16_t speed);
void MOTOR_C_SetSpeed(int16_t speed);
void MOTOR_D_SetSpeed(int16_t speed);

void moving_forward(int8_t speed, int16_t distance);
void moving_backwards(int8_t speed, int16_t distance);
void moving_left(int8_t speed, int16_t distance);
void moving_right(int8_t speed, int16_t distance);
 
void turnRight(void);
void turnLeft(void);
void moveForward(void);
void stop(void);
void RotateOnce(int16_t distanc);
#endif /* __TIM_H__ */
