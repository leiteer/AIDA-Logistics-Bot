#include "tim.h"
#include "servo.h"

void ServoPWM_Start(void){
		HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);
	}

void servoControl(int16_t angle){
	 // ���ƶ���ĺ�������������ĽǶȼ���PWMֵ�����ö�ʱ���ıȽ�ֵ
	 uint16_t pwm_value = 0;
	 if (angle >= 0 && angle <= 90)
	 {
		 pwm_value = PWM_MIN_VALUE_ANGLE_0 - (- PWM_MAX_VALUE_ANGLE_90 + PWM_MIN_VALUE_ANGLE_0) * angle / 90;
	 }
	 else if (angle < 0)
	 {
		 pwm_value = PWM_MIN_VALUE_ANGLE_0;
	 }
	 else if (angle > 90)
	 {
		 pwm_value = PWM_MAX_VALUE_ANGLE_90;
	 }
	 __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_4, pwm_value);
	}
 
void rotate_servo(int8_t angle, uint16_t speed) {
		 // ��ת����ĺ�������������ĽǶȺ��ٶ��𲽵�������ĽǶ�
		 uint8_t current_angle = 0;

		 if (angle >= 0 && angle <= 90) {
				 int8_t step = (angle > current_angle) ? 1 : -1;
				 while (current_angle != angle) {
						 current_angle += step;
						 servoControl(current_angle);
						 HAL_Delay(1000/speed);
				 }
		 }
	}	
