#ifndef __SERVO_H__
#define __SERVO_H__

#include "main.h"

#define PWM_MIN_VALUE_ANGLE_0 2400   //�����ת0�ȶ�Ӧ��pwm�Ƚ�ֵ
#define PWM_MAX_VALUE_ANGLE_90 1500  //90�ȶ�Ӧ��pwm�Ƚ�ֵ
#define DISTANCE_FROM_INITIAL_POSITION_TO_QR_CODE 1000   //��㵽��ά��������룬��������ʱ

void ServoPWM_Start(void);
void servoControl(int16_t angle);
void rotate_servo(int8_t angle, uint16_t speed);
 
#endif 
