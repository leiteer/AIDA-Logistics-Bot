#ifndef __SERVO_H__
#define __SERVO_H__

#include "main.h"

#define PWM_MIN_VALUE_ANGLE_0 2400   //舵机旋转0度对应的pwm比较值
#define PWM_MAX_VALUE_ANGLE_90 1500  //90度对应的pwm比较值
#define DISTANCE_FROM_INITIAL_POSITION_TO_QR_CODE 1000   //起点到二维码区域距离，本质是延时

void ServoPWM_Start(void);
void servoControl(int16_t angle);
void rotate_servo(int8_t angle, uint16_t speed);
 
#endif 
