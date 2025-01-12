#include <stdio.h>
#include <string.h>
#include <stdint.h> 
#include "tim.h"
#include "usart.h"
#include "contral.h"
#include "grayscale_sensor.h"
#include "motor.h"
#include "servo.h"
#include "led.h"

#define ZONE_1 1 //区域1
#define ZONE_2 2
#define ZONE_3 3

extern const uint8_t VOICE_5[22],VOICE_2[22],VOICE_9[16],VOICE_3[22],VOICE_4[22];
extern uint8_t digital_position;
extern uint8_t arriving_the_starting_point_sign,count_state;
extern uint8_t flag2;


void returnToStartingPoint(void)//返回起点
{
	static uint8_t out_state = 0;
	printf("page 8\xff\xff\xff");//屏幕输出
	HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_5,sizeof(VOICE_5), 1000);//语音提示“正在前往载货区域”
	while (out_state == 0)
	{
		followTrail();//循迹
		if (arriving_the_starting_point_sign == 1)//检查到已经到达起点，四个传感器都检测到黑线
		{
			out_state = 1;
			followTrail_distance(500);//向前走一小段距离
		}
	}
	out_state = 0;
}

void HandsomeReturnToPlace(void)//不循迹，抄近道返回起点
{
  static uint8_t out_state2 = 0;
  moving_right(25, 2520);//向右横着走到对面黑线
  while (out_state2 == 0)
  {
    followTrail();//循迹
    if (arriving_the_starting_point_sign == 1)//检查到已经到达起点，四个传感器都检测到黑线
    {
			stop();
			HAL_Delay(1000);
      out_state2 = 1;
      RotateOnce(1420);//向右转180度，调头
    }
  }
	out_state2 = 0;
}

void FollowTrailToDesignatedArea(uint8_t zone)//前往指定区域
{
  static uint8_t out_state3 = 0;
  while (out_state3 == 0)
  {
    followTrail();//循迹
    if (digital_position == zone)//检查到已经抵达指定区域
    {
      stop();
      out_state3 = 1;
      
    }
  }
  out_state3 = 0;
}

void ThrowingPackages(void)
{
		HAL_Delay(300);
		moving_left(10, 300);//向左走一点，靠近区域
		rotate_servo(50, 40);//旋转舵机，将物块倾倒在一号区域
		LED3_Turn();
		servoControl(0);//舵机回到初始位置
		moving_right(10, 300);//向右走一点，回到轨迹
		HAL_Delay(300);
}

void task1(uint8_t mode2_flag,uint8_t mode2_count)//将物块放置在一号区域并返回起点
{
	arriving_the_starting_point_sign = 0;
	count_state = 0;
	printf("page 5\xff\xff\xff");//屏幕显示page 5页面，
	HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_2,sizeof(VOICE_2), 1000);//语音提示“正在前往一号区域”
	//moving_forward(15, 3000-initialPosition);
	//followTrail_distance(DISTANCE_FROM_STARTING_POINT_TO_ZONE_1 - initialPosition);
	FollowTrailToDesignatedArea(ZONE_1);//前往一号区域
	
	ThrowingPackages();

	//moving_backwards(15, 3000);
	//followTrail_distance(FULL_DISTANCE - DISTANCE_FROM_STARTING_POINT_TO_ZONE_1);
	returnToStartingPoint();
//	HandsomeReturnToPlace();//不循迹，抄近道返回起点
	if (flag2 == 0)
	{
		HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_9,sizeof(VOICE_9), 1000);//语音提示“请放置包裹”
	}
	if (mode2_flag == 1 && mode2_count < 2)//如果是模式2，且模式2执行次数小于2
	{
		printf("page 2\xff\xff\xff");//返回模式2页面
	}
	HAL_Delay(3000);
}

void task2(uint8_t mode2_flag,uint8_t mode2_count)
{
	arriving_the_starting_point_sign = 0;
	count_state = 0;
	printf("page 6\xff\xff\xff");//屏幕显示page 6页面
	HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_3,sizeof(VOICE_3), 1000);//语音提示“正在前往二号区域”
	//moving_forward(15, 3000-initialPosition);
	//followTrail_distance(DISTANCE_FROM_STARTING_POINT_TO_ZONE_2 - initialPosition);
	FollowTrailToDesignatedArea(ZONE_2);//前往二号区域
	
	ThrowingPackages();

	//moving_backwards(15, 3000);
	//followTrail_distance(FULL_DISTANCE - DISTANCE_FROM_STARTING_POINT_TO_ZONE_2);
	returnToStartingPoint();
	//HandsomeReturnToPlace();//不循迹，抄近道返回起点
	if (flag2 == 0)
	{
		HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_9,sizeof(VOICE_9), 1000);//语音提示“请放置包裹”
	}
	if (mode2_flag == 1 && mode2_count < 2)//如果是模式2，且模式2执行次数小于2
	{
		printf("page 2\xff\xff\xff");//返回模式2页面
	}
	HAL_Delay(3000);

}

void task3(/*int16_t initialPosition*/ uint8_t mode2_flag,uint8_t mode2_count)
{
	arriving_the_starting_point_sign = 0;
	count_state = 0;
	printf("page 7\xff\xff\xff");//屏幕显示page 7页面
	HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_4,sizeof(VOICE_4), 1000);//语音提示“正在前往三号区域”
	//moving_forward(15, 3000-initialPosition);
	//followTrail_distance(DISTANCE_FROM_STARTING_POINT_TO_ZONE_3 - initialPosition);
	FollowTrailToDesignatedArea(ZONE_3);//前往三号区域
	
	ThrowingPackages();

	//moving_backwards(15, 3000);
	//followTrail_distance(FULL_DISTANCE - DISTANCE_FROM_STARTING_POINT_TO_ZONE_3);
	returnToStartingPoint();//不循迹，抄近道返回起点
	if (flag2 == 0)
	{
		HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_9,sizeof(VOICE_9), 1000);//语音提示“请放置包裹”
	}
	if (mode2_flag == 1 && mode2_count < 2)
	{
		printf("page 2\xff\xff\xff");//返回模式2页面
	}
	HAL_Delay(3000);
}

