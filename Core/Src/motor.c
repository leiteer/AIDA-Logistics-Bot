#include "tim.h"
#include "MOTOR.h"

void MotorPWM_Start(void)
{
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
  //HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);
}

void inline MOTOR_A_SetSpeed(int16_t speed)
{
//	int16_t temp;
//	
//	temp = speed;
	
	if(speed>100)
		speed = 100;
	if(speed<-100)
		speed = -100;
	
	if(speed > 0)
	{
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 100);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, (100 - speed));

	}
	else
	{
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, 100);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, (100 + speed));

	}
}

void inline MOTOR_B_SetSpeed(int16_t speed)
{
//	int16_t temp;
//	
//	temp = speed;
	
	if(speed>100)
		speed = 100;
	if(speed<-100)
		speed = -100;
	
	if(speed > 0)
	{
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 100);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, (100 - speed));

	}
	else
	{
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_4, 100);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, (100 + speed));

	}
}

void inline MOTOR_C_SetSpeed(int16_t speed)
{
	// int16_t temp;
	
	// temp = speed;
	
	if(speed>100)
		speed = 100;
	if(speed<-100)
		speed = -100;
	
	if(speed > 0)
	{
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, 100);
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, (100 - speed));

	}
	else
	{
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, 100);
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, (100 + speed));

	}
}

void inline MOTOR_D_SetSpeed(int16_t speed)
{
	// int16_t temp;
	
	// temp = speed;
	
	if(speed>100)
		speed = 100;
	if(speed<-100)
		speed = -100;
	
	if(speed > 0)
	{
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, 100);
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, (100 - speed));

	}
	else
	{
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, 100);
    __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, (100 + speed));

	}
}

void moving_forward(int8_t speed, int16_t distance)
{
	MOTOR_A_SetSpeed(-speed);//后右
	MOTOR_B_SetSpeed(-(speed+1));//后左
	MOTOR_C_SetSpeed(speed+1);//前左
	MOTOR_D_SetSpeed(speed);//前右

	HAL_Delay(distance);

	MOTOR_A_SetSpeed(0);
	MOTOR_B_SetSpeed(0);
	MOTOR_C_SetSpeed(0);
	MOTOR_D_SetSpeed(0);
}

void moving_backwards(int8_t speed, int16_t distance)
{
	MOTOR_A_SetSpeed(speed);
	MOTOR_B_SetSpeed(speed+1);
	MOTOR_C_SetSpeed(-(speed+1));
	MOTOR_D_SetSpeed(-speed);

	HAL_Delay(distance);

	MOTOR_A_SetSpeed(0);
	MOTOR_B_SetSpeed(0);  
	MOTOR_C_SetSpeed(0);
	MOTOR_D_SetSpeed(0);
}

void moving_left(int8_t speed, int16_t distance)
{
	MOTOR_A_SetSpeed(speed);
	MOTOR_B_SetSpeed(-speed);
	MOTOR_C_SetSpeed(-speed);
	MOTOR_D_SetSpeed(speed);

	HAL_Delay(distance);

	MOTOR_A_SetSpeed(0);
	MOTOR_B_SetSpeed(0);  
	MOTOR_C_SetSpeed(0);
	MOTOR_D_SetSpeed(0);
}

void moving_right(int8_t speed, int16_t distance)
{
	MOTOR_A_SetSpeed(-(speed+1));
	MOTOR_B_SetSpeed(speed);
	MOTOR_C_SetSpeed(speed);
	MOTOR_D_SetSpeed(-(speed));

	HAL_Delay(distance);

	MOTOR_A_SetSpeed(0);
	MOTOR_B_SetSpeed(0);  
	MOTOR_C_SetSpeed(0);
	MOTOR_D_SetSpeed(0);
}

void turnRight(void)
{
	// 控制电机向右转
	int8_t speed = 20;
	MOTOR_A_SetSpeed(0);//后右
	MOTOR_B_SetSpeed(-speed);//后左
	MOTOR_C_SetSpeed(speed);//前左
	MOTOR_D_SetSpeed(0);//前右
}

void turnLeft(void)
{
	// 控制电机向左转
	int8_t speed = 20;
	MOTOR_A_SetSpeed(-speed);
	MOTOR_B_SetSpeed(0);
	MOTOR_C_SetSpeed(0);
	MOTOR_D_SetSpeed(speed);
}
 
void moveForward(void)
{
	// 控制电机向前移动
	int8_t speed = 15;
	MOTOR_A_SetSpeed(-speed);
	MOTOR_B_SetSpeed(-(speed+1));
	MOTOR_C_SetSpeed(speed+1);
	MOTOR_D_SetSpeed(speed);
}

void stop(void)
{
	// 停止所有电机
	MOTOR_A_SetSpeed(0);
	MOTOR_B_SetSpeed(0);
	MOTOR_C_SetSpeed(0);
	MOTOR_D_SetSpeed(0);

}

void RotateOnce(int16_t distance)//原地旋转
{
  int8_t speed = 20;
  MOTOR_A_SetSpeed(-speed);
  MOTOR_B_SetSpeed(speed);
  MOTOR_C_SetSpeed(-(speed+1));
  MOTOR_D_SetSpeed(speed);

  HAL_Delay(distance);

  MOTOR_A_SetSpeed(0);
	MOTOR_B_SetSpeed(0);  
	MOTOR_C_SetSpeed(0);
	MOTOR_D_SetSpeed(0);
}
