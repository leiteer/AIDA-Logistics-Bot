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

#define ZONE_1 1 //����1
#define ZONE_2 2
#define ZONE_3 3

extern const uint8_t VOICE_5[22],VOICE_2[22],VOICE_9[16],VOICE_3[22],VOICE_4[22];
extern uint8_t digital_position;
extern uint8_t arriving_the_starting_point_sign,count_state;
extern uint8_t flag2;


void returnToStartingPoint(void)//�������
{
	static uint8_t out_state = 0;
	printf("page 8\xff\xff\xff");//��Ļ���
	HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_5,sizeof(VOICE_5), 1000);//������ʾ������ǰ���ػ�����
	while (out_state == 0)
	{
		followTrail();//ѭ��
		if (arriving_the_starting_point_sign == 1)//��鵽�Ѿ�������㣬�ĸ�����������⵽����
		{
			out_state = 1;
			followTrail_distance(500);//��ǰ��һС�ξ���
		}
	}
	out_state = 0;
}

void HandsomeReturnToPlace(void)//��ѭ�����������������
{
  static uint8_t out_state2 = 0;
  moving_right(25, 2520);//���Һ����ߵ��������
  while (out_state2 == 0)
  {
    followTrail();//ѭ��
    if (arriving_the_starting_point_sign == 1)//��鵽�Ѿ�������㣬�ĸ�����������⵽����
    {
			stop();
			HAL_Delay(1000);
      out_state2 = 1;
      RotateOnce(1420);//����ת180�ȣ���ͷ
    }
  }
	out_state2 = 0;
}

void FollowTrailToDesignatedArea(uint8_t zone)//ǰ��ָ������
{
  static uint8_t out_state3 = 0;
  while (out_state3 == 0)
  {
    followTrail();//ѭ��
    if (digital_position == zone)//��鵽�Ѿ��ִ�ָ������
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
		moving_left(10, 300);//������һ�㣬��������
		rotate_servo(50, 40);//��ת�����������㵹��һ������
		LED3_Turn();
		servoControl(0);//����ص���ʼλ��
		moving_right(10, 300);//������һ�㣬�ص��켣
		HAL_Delay(300);
}

void task1(uint8_t mode2_flag,uint8_t mode2_count)//����������һ�����򲢷������
{
	arriving_the_starting_point_sign = 0;
	count_state = 0;
	printf("page 5\xff\xff\xff");//��Ļ��ʾpage 5ҳ�棬
	HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_2,sizeof(VOICE_2), 1000);//������ʾ������ǰ��һ������
	//moving_forward(15, 3000-initialPosition);
	//followTrail_distance(DISTANCE_FROM_STARTING_POINT_TO_ZONE_1 - initialPosition);
	FollowTrailToDesignatedArea(ZONE_1);//ǰ��һ������
	
	ThrowingPackages();

	//moving_backwards(15, 3000);
	//followTrail_distance(FULL_DISTANCE - DISTANCE_FROM_STARTING_POINT_TO_ZONE_1);
	returnToStartingPoint();
//	HandsomeReturnToPlace();//��ѭ�����������������
	if (flag2 == 0)
	{
		HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_9,sizeof(VOICE_9), 1000);//������ʾ������ð�����
	}
	if (mode2_flag == 1 && mode2_count < 2)//�����ģʽ2����ģʽ2ִ�д���С��2
	{
		printf("page 2\xff\xff\xff");//����ģʽ2ҳ��
	}
	HAL_Delay(3000);
}

void task2(uint8_t mode2_flag,uint8_t mode2_count)
{
	arriving_the_starting_point_sign = 0;
	count_state = 0;
	printf("page 6\xff\xff\xff");//��Ļ��ʾpage 6ҳ��
	HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_3,sizeof(VOICE_3), 1000);//������ʾ������ǰ����������
	//moving_forward(15, 3000-initialPosition);
	//followTrail_distance(DISTANCE_FROM_STARTING_POINT_TO_ZONE_2 - initialPosition);
	FollowTrailToDesignatedArea(ZONE_2);//ǰ����������
	
	ThrowingPackages();

	//moving_backwards(15, 3000);
	//followTrail_distance(FULL_DISTANCE - DISTANCE_FROM_STARTING_POINT_TO_ZONE_2);
	returnToStartingPoint();
	//HandsomeReturnToPlace();//��ѭ�����������������
	if (flag2 == 0)
	{
		HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_9,sizeof(VOICE_9), 1000);//������ʾ������ð�����
	}
	if (mode2_flag == 1 && mode2_count < 2)//�����ģʽ2����ģʽ2ִ�д���С��2
	{
		printf("page 2\xff\xff\xff");//����ģʽ2ҳ��
	}
	HAL_Delay(3000);

}

void task3(/*int16_t initialPosition*/ uint8_t mode2_flag,uint8_t mode2_count)
{
	arriving_the_starting_point_sign = 0;
	count_state = 0;
	printf("page 7\xff\xff\xff");//��Ļ��ʾpage 7ҳ��
	HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_4,sizeof(VOICE_4), 1000);//������ʾ������ǰ����������
	//moving_forward(15, 3000-initialPosition);
	//followTrail_distance(DISTANCE_FROM_STARTING_POINT_TO_ZONE_3 - initialPosition);
	FollowTrailToDesignatedArea(ZONE_3);//ǰ����������
	
	ThrowingPackages();

	//moving_backwards(15, 3000);
	//followTrail_distance(FULL_DISTANCE - DISTANCE_FROM_STARTING_POINT_TO_ZONE_3);
	returnToStartingPoint();//��ѭ�����������������
	if (flag2 == 0)
	{
		HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_9,sizeof(VOICE_9), 1000);//������ʾ������ð�����
	}
	if (mode2_flag == 1 && mode2_count < 2)
	{
		printf("page 2\xff\xff\xff");//����ģʽ2ҳ��
	}
	HAL_Delay(3000);
}

