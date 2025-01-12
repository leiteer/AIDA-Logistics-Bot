#include "gpio.h"
#include "motor.h"
#include "usart.h"
#include "grayscale_sensor.h"

//ѭ��������
#define LEFT_SENSOR GPIO_PIN_8      //���� 
#define LEFT_CENTER_SENSOR GPIO_PIN_7 // ���� 
#define RIGHT_CENTER_SENSOR GPIO_PIN_10 //���� 
#define RIGHT_SENSOR GPIO_PIN_12      // ����

extern uint8_t Voice_flag1;
extern uint8_t arriving_the_starting_point_sign,count_state;
extern const uint8_t VOICE_11[16];

void followTrail(void)  //ѭ��
{
//		static uint8_t Voice_flag1 = 0;
    uint8_t warning_sign = 0;

    uint8_t leftValue = HAL_GPIO_ReadPin(GPIOE, LEFT_SENSOR);  
    uint8_t leftCenterValue = HAL_GPIO_ReadPin(GPIOE, LEFT_CENTER_SENSOR);  
    uint8_t rightCenterValue = HAL_GPIO_ReadPin(GPIOE, RIGHT_CENTER_SENSOR);  
    uint8_t rightValue = HAL_GPIO_ReadPin(GPIOE, RIGHT_SENSOR);  
//    uint8_t obstacle_avoidance_back = HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1);  
		uint8_t obstacle_avoidance_ahead = HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_9); 
		
    if (/*obstacle_avoidance_back == 0 || */obstacle_avoidance_ahead == 0)   //���Ϲ���
    {
      warning_sign = 1;
			if (Voice_flag1 ==0)
      {
        HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_11,sizeof(VOICE_11), 1000); //������ ��ע����á�
        Voice_flag1 = 1;
      }
    }
		else 
		{
			warning_sign = 0;
		}

    if (leftValue == 1 && leftCenterValue == 1 && rightCenterValue == 1 && rightValue == 1) //��鵽���
    {
      if (count_state == 0)
      {
        arriving_the_starting_point_sign = 1;
        count_state = 1;
      }
    }

    if (warning_sign == 0) //��������
    {
         
    if ((leftValue == 0 && leftCenterValue == 0 && rightCenterValue == 0 && rightValue == 1) || (leftValue == 0 && leftCenterValue == 0 && rightCenterValue == 1 && rightValue == 0) || (leftValue == 0 && leftCenterValue == 0 && rightCenterValue == 1 && rightValue == 1) )
    {
        turnRight();  
    } 
    else if ((leftValue == 1 && leftCenterValue == 0 && rightCenterValue == 0 && rightValue == 0) || (leftValue == 0 && leftCenterValue == 1 && rightCenterValue == 0 && rightValue == 0) || (leftValue == 1 && leftCenterValue == 1 && rightCenterValue == 0 && rightValue == 0))
    {  
        turnLeft();  
    } 
    else if ((leftValue == 0 && leftCenterValue == 1 && rightCenterValue == 1 && rightValue == 0) || (leftValue == 1 && leftCenterValue == 1 && rightCenterValue == 1 && rightValue == 1) || (leftValue == 0 && leftCenterValue == 0 && rightCenterValue == 0 && rightValue == 0))
    {  
        moveForward();  
    } 
    else
    {  
        
        stop();  
    } 
    }

    if (warning_sign == 1) //���� ���Ϲ���
    {
      if (obstacle_avoidance_ahead == 0)   
      {
        int8_t speed = 15;
				MOTOR_A_SetSpeed(speed);
				MOTOR_B_SetSpeed(speed+1);
				MOTOR_C_SetSpeed(-(speed+1));
				MOTOR_D_SetSpeed(-speed);
      }
    }
}

void followTrail_distance(int16_t distance)//ѭ��ָ������
{
	for (int16_t i = 0; i < distance; i++)
	{
		followTrail();
		HAL_Delay(1);
	}
	stop(); 
}
