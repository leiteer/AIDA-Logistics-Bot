/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <stdint.h>  
#include "stm32h7xx_it.h"
#include "servo.h"
#include "motor.h"
#include "grayscale_sensor.h"
#include "rfid.h"
#include "screen.h"
#include "contral.h"
#include "led.h"
#include "key.h"
//#include "voice.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// ���峵����ʻ���ܾ���͸��������ʼ�����
#define FULL_DISTANCE 10500
#define DISTANCE_FROM_STARTING_POINT_TO_ZONE_1 4700
#define DISTANCE_FROM_STARTING_POINT_TO_ZONE_2 5300
#define DISTANCE_FROM_STARTING_POINT_TO_ZONE_3 5900
#define MODE1 12  //ģʽѡ��ģʽһ��Ӧֵ12
#define MODE2 13
#define MODE3 14
#define MODE4 17
#define DEL 16    //����   
#define SURE 18   //ȷ��
#define OUTPUT_SIZE 100  
// ����ģʽ��ִ�б�־λ
#define MODE_1_EXECUTION 1  //��־λ
#define MODE_1_NOT_EXECUT 0
#define MODE_2_EXECUTION 1
#define MODE_2_NOT_EXECUT 0

char output[OUTPUT_SIZE]; 

//#define ZONE_1 1 //����1
//#define ZONE_2 2
//#define ZONE_3 3
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* ��������*/
//�ѽ���ģʽһ ����ǰ����ά��ɨ������ 41
const uint8_t VOICE_1[41] = {0xFD, 0x00, 0x26, 0x01, 0x01, 0xD2, 0xD1, 0xBD, 0xF8, 0xC8, 0xEB, 0xC4, 0xA3, 0xCA, 0xBD, 0xD2, 0xBB, 0x20, 0xD5, 0xFD, 0xD4, 0xDA, 0xC7, 0xB0, 0xCD, 0xF9, 0xB6, 0xFE, 0xCE, 0xAC, 0xC2, 0xEB, 0xC9, 0xA8, 0xC3, 0xE8, 0xC7, 0xF8, 0xD3, 0xF2, 0xD5};//0xFD 0x00 0x26 0x01 0x01 0xD2 0xD1 0xBD 0xF8 0xC8 0xEB 0xC4 0xA3 0xCA 0xBD 0xD2 0xBB 0x20 0xD5 0xFD 0xD4 0xDA 0xC7 0xB0 0xCD 0xF9 0xB6 0xFE 0xCE 0xAC 0xC2 0xEB 0xC9 0xA8 0xC3 0xE8 0xC7 0xF8 0xD3 0xF2 0xD5
//����ǰ��һ������ 22
const uint8_t VOICE_2[22] = {0xFD, 0x00, 0x13, 0x01, 0x01, 0xD5, 0xFD, 0xD4, 0xDA, 0xC7, 0xB0, 0xCD, 0xF9, 0xD2, 0xBB, 0xBA, 0xC5, 0xC7, 0xF8, 0xD3, 0xF2, 0x83};//0xFD 0x00 0x13 0x01 0x01 0xD5 0xFD 0xD4 0xDA 0xC7 0xB0 0xCD 0xF9 0xD2 0xBB 0xBA 0xC5 0xC7 0xF8 0xD3 0xF2 0x83
//����ǰ���������� 22
const uint8_t VOICE_3[22] = {0xFD, 0x00, 0x13, 0x01, 0x01, 0xD5, 0xFD, 0xD4, 0xDA, 0xC7, 0xB0, 0xCD, 0xF9, 0xB6, 0xFE, 0xBA, 0xC5, 0xC7, 0xF8, 0xD3, 0xF2, 0xA2};//0xFD 0x00 0x13 0x01 0x01 0xD5 0xFD 0xD4 0xDA 0xC7 0xB0 0xCD 0xF9 0xB6 0xFE 0xBA 0xC5 0xC7 0xF8 0xD3 0xF2 0xA2
//����ǰ���������� 22
const uint8_t VOICE_4[22] = {0xFD, 0x00, 0x13, 0x01, 0x01, 0xD5, 0xFD, 0xD4, 0xDA, 0xC7, 0xB0, 0xCD, 0xF9, 0xC8, 0xFD, 0xBA, 0xC5, 0xC7, 0xF8, 0xD3, 0xF2, 0xDF};//0xFD 0x00 0x13 0x01 0x01 0xD5 0xFD 0xD4 0xDA 0xC7 0xB0 0xCD 0xF9 0xC8 0xFD 0xBA 0xC5 0xC7 0xF8 0xD3 0xF2 0xDF
//����ǰ���ػ����� 22
const uint8_t VOICE_5[22] = {0xFD, 0x00, 0x13, 0x01, 0x01, 0xD5, 0xFD, 0xD4, 0xDA, 0xC7, 0xB0, 0xCD, 0xF9, 0xD4, 0xD8, 0xBB, 0xF5, 0xC7, 0xF8, 0xD3, 0xF2, 0xD7};//0xFD 0x00 0x13 0x01 0x01 0xD5 0xFD 0xD4 0xDA 0xC7 0xB0 0xCD 0xF9 0xD4 0xD8 0xBB 0xF5 0xC7 0xF8 0xD3 0xF2 0xD7
//�ѽ���ģʽ�� �뽫��������������̨ 41
const uint8_t VOICE_6[41] = {0xFD, 0x00, 0x26, 0x01, 0x01, 0xD2, 0xD1, 0xBD, 0xF8, 0xC8, 0xEB, 0xC4, 0xA3, 0xCA, 0xBD, 0xB6, 0xFE, 0x20, 0xC7, 0xEB, 0xBD, 0xAB, 0xB0, 0xFC, 0xB9, 0xFC, 0xB7, 0xC5, 0xD6, 0xC3, 0xD3, 0xDA, 0xD4, 0xD8, 0xCE, 0xEF, 0xCC, 0xA8, 0xA3, 0xA1, 0xD0};//0xFD 0x00 0x26 0x01 0x01 0xD2 0xD1 0xBD 0xF8 0xC8 0xEB 0xC4 0xA3 0xCA 0xBD 0xB6 0xFE 0x20 0xC7 0xEB 0xBD 0xAB 0xB0 0xFC 0xB9 0xFC 0xB7 0xC5 0xD6 0xC3 0xD3 0xDA 0xD4 0xD8 0xCE 0xEF 0xCC 0xA8 0xA3 0xA1 0xD0
//�ѽ���ģʽ�� ����������˳�� 35
const uint8_t VOICE_7[35] = {0xFD, 0x00, 0x20, 0x01, 0x01, 0xD2, 0xD1, 0xBD, 0xF8, 0xC8, 0xEB, 0xC4, 0xA3, 0xCA, 0xBD, 0xC8, 0xFD, 0x20, 0xC7, 0xEB, 0xCA, 0xE4, 0xC8, 0xEB, 0xD4, 0xCB, 0xCB, 0xCD, 0xCB, 0xB3, 0xD0, 0xF2, 0xA3, 0xA1, 0xDD};//0xFD 0x00 0x20 0x01 0x01 0xD2 0xD1 0xBD 0xF8 0xC8 0xEB 0xC4 0xA3 0xCA 0xBD 0xC8 0xFD 0x20 0xC7 0xEB 0xCA 0xE4 0xC8 0xEB 0xD4 0xCB 0xCB 0xCD 0xCB 0xB3 0xD0 0xF2 0xA3 0xA1 0xDD
//�ѽ���ģʽ�ģ���ת���ƶ��豸���� 38
const uint8_t VOICE_8[38] = {0xFD, 0x00, 0x23, 0x01, 0x01, 0xD2, 0xD1, 0xBD, 0xF8, 0xC8, 0xEB, 0xC4, 0xA3, 0xCA, 0xBD, 0xCB, 0xC4, 0xA3, 0xAC, 0xC7, 0xEB, 0xD7, 0xAA, 0xB5, 0xBD, 0xD2, 0xC6, 0xB6, 0xAF, 0xC9, 0xE8, 0xB1, 0xB8, 0xB2, 0xD9, 0xD7, 0xF7, 0x9C };//0xFD 0x00 0x23 0x01 0x01 0xD2 0xD1 0xBD 0xF8 0xC8 0xEB 0xC4 0xA3 0xCA 0xBD 0xCB 0xC4 0xA3 0xAC 0xC7 0xEB 0xD7 0xAA 0xB5 0xBD 0xD2 0xC6 0xB6 0xAF 0xC9 0xE8 0xB1 0xB8 0xB2 0xD9 0xD7 0xF7 0x9C 
//����ð��� 16
const uint8_t VOICE_9[16] = {0xFD, 0x00, 0x0D, 0x01, 0x01, 0xC7, 0xEB, 0xB7, 0xC5, 0xD6, 0xC3, 0xB0, 0xFC, 0xB9, 0xFC, 0xB2};//0xFD 0x00 0x0D 0x01 0x01 0xC7 0xEB 0xB7 0xC5 0xD6 0xC3 0xB0 0xFC 0xB9 0xFC
//������� 14
const uint8_t VOICE_10[14] = {0xFD, 0x00, 0x0B, 0x01, 0x01, 0xC8, 0xCE, 0xCE, 0xF1, 0xCD, 0xEA, 0xB3, 0xC9, 0x92 };//0xFD 0x00 0x0B 0x01 0x01 0xC8 0xCE 0xCE 0xF1 0xCD 0xEA 0xB3 0xC9 0x92 
//ע����� 16
const uint8_t VOICE_11[16] = {0xFD,0x00,0x0D,0x01,0x01,0xC7,0xEB,0xD7,0xA2,0xD2,0xE2,0xB1,0xDC,0xC8,0xC3,0xFF};
//��ά��ɨ��ɹ� 20
const uint8_t VOICE_12[20] = {0xFD,0x00,0x11,0x01,0x01,0xB6,0xFE,0xCE,0xAC,0xC2,0xEB,0xCA,0xB6,0xB1,0xF0,0xB3,0xC9,0xB9,0xA6,0xB7};	
	
char *strx,*extstrx,*Readystrx; 
char RxBuffer[10],Rxcouter; 

// static unsigned char intArray[10];
// ����ȫ�ֱ��������飬���ڴ洢����״̬������
uint8_t arriving_the_starting_point_sign = 0,count_state = 0;

char tast[4];
char *strstr(const char *, const char *); 
uint8_t Res,flag1=0,digital_position;
uint8_t Serial_RxFlag=0;
int16_t initialPosition;
uint8_t RxData,RxData_rfid,Serial_Num=0,value=0;
uint8_t Serial_RxPacket[1];
uint8_t Serial_RxFlag1=0;
uint8_t Pattern=0,skip=0,exit1=0;
uint8_t sequential_number[3];
char str_number[3];
uint8_t Serial_RxFlag_rfid=0,Serial_RxPacket_rfid[6];
uint8_t Rfid_1_str[6] = {0x02, 0x20, 0x00, 0x04, 0x00, 0xAA},Rfid_2_str[6] = {0x02, 0x20, 0x00, 0x04, 0x00, 0xDA},Rfid_3_str[6] = {0x02, 0x20, 0x00, 0x04, 0x00, 0x7A};
uint8_t Voice_flag=0,Voice_flag1=0;
uint8_t flag2 = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
/* USER CODE BEGIN PFP */
 
void uint8_array_to_number_string(const uint8_t *array, size_t length) 
// �� uint8_t ����ת��Ϊ�����ַ����ĺ���
{  
    if (!array || length == 0) {  
        output[0] = '\0';  
        return;  
    }  
    size_t offset = 0;  
 
    for (size_t i = 0; i < length; i++) {  
 
        if (offset < OUTPUT_SIZE - 1) {  
            offset += snprintf(output + offset, OUTPUT_SIZE - offset, "%d", array[i]);  
        }  
        if (offset >= OUTPUT_SIZE - 1) {  
            break;   
        }  
    }  
    output[offset < OUTPUT_SIZE ? offset : OUTPUT_SIZE - 1] = '\0'; 
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// ����UART������ɻص�����
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
 UNUSED(huart);
  if (huart->Instance == USART3) 
  {
  if (flag1 == 0)
    {
      RxBuffer[Rxcouter++] = Res;
    }
    if (Rxcouter >= 1 && flag1 == 0) 
    {
      Serial_RxFlag=1;
   flag1++;
   Res = 0;
    }
   
  if (flag1 == 1)
    {
      digital_position = Res;
    }
    HAL_UART_Receive_IT(&huart3, (uint8_t *)&Res, 1); 
  }
  
 static uint8_t RxState = 0;
 static uint8_t pRxPacket = 0;
  if (huart->Instance == USART10) 
  {
        if (RxState == 0)
        {
            if (RxData == 0xA5)
            {
                RxState = 1;
                pRxPacket = 0;
            }
        }
        else if (RxState == 1)
        {
            Serial_RxPacket[pRxPacket] = RxData;
            RxState = 2;
        }
        else if (RxState == 2)
        {
            if (RxData == 0x5A)
            {
                RxState = 0;
                Serial_RxFlag1 = 1;
            }
        }
 
        HAL_UART_Receive_IT(&huart10, (uint8_t *)&RxData, 1);
  }
  
 if (huart->Instance == USART2) 
  {
        if (RxState == 0)
        {
            if (RxData == 0xA5)
            {
                RxState = 1;
                pRxPacket = 0;
            }
        }
        else if (RxState == 1)
        {
            Serial_RxPacket[pRxPacket] = RxData;
            RxState = 2;
        }
        else if (RxState == 2)
        {
            if (RxData == 0x5A)
            {
                RxState = 0;
                Serial_RxFlag1 = 1;
            }
        }
 
        HAL_UART_Receive_IT(&huart2, (uint8_t *)&RxData, 1);
  }
  
 if (huart->Instance == USART6) 
  {
        if (RxState == 0)
        {
            if (RxData == 0xA5)
            {
                RxState = 1;
                pRxPacket = 0;
            }
        }
        else if (RxState == 1)
        {
            Serial_RxPacket[pRxPacket] = RxData;
            RxState = 2;
        }
        else if (RxState == 2)
        {
            if (RxData == 0x5A)
            {
                RxState = 0;
                Serial_RxFlag1 = 1;
            }
        }
 
        HAL_UART_Receive_IT(&huart6, (uint8_t *)&RxData, 1);
  }
  
  static uint8_t RxState_rfid = 0;
  static uint8_t pRxPacket_rfid = 0;
  if (huart->Instance == USART1) 
  {
        if (RxState_rfid == 0)
        {
            if (RxData_rfid == 0x0C)
            {
               RxState_rfid = 1;
               pRxPacket_rfid = 0;
            }
        }
        else if (RxState_rfid == 1)
        {
            Serial_RxPacket_rfid[pRxPacket_rfid] = RxData_rfid;
            pRxPacket_rfid++;
            if (pRxPacket_rfid >=6)
            {
              RxState_rfid = 2;
            }
        }
        else if (RxState_rfid == 2)
        {
            if (RxData_rfid == 0x96)
            {
                RxState_rfid = 0;
                Serial_RxFlag_rfid = 1;
            }
        }
        HAL_UART_Receive_IT(&huart1, (uint8_t *)&RxData_rfid, 1);
  }
}
 
// ��ȡ���ڽ��ձ�־λ
uint8_t Serial_GetRxFlag(void)
 {
  if(Serial_RxFlag==1)
  {
   Serial_RxFlag=0;
   return 1;
  }
  return 0;
 }
 
// ��ȡ���ڽ��ձ�־λ1
uint8_t Serial_GetRxFlag1(void)
{
 if (Serial_RxFlag1 == 1)
 {
  Serial_RxFlag1 = 0;
  return 1;
 }
 return 0;
} 
 
void Serial_GetNum()
{
    // �Ӵ��ڽ������ݲ����ݽ��յ�����������Serial_Num
 if (Serial_GetRxFlag1() == 1)
  {
   if (Serial_RxPacket[0]==0x0A){ Serial_Num = 0;}
   else if(Serial_RxPacket[0]==0);
   else Serial_Num=Serial_RxPacket[0];
  }
}
 
  
 void decimalToString(int num, char* str) 
 {
  // ������ת��Ϊ�ַ���
  sprintf(str, "%d", num);
 }
  
 void charArrayToIntArray(char *input_char_array, unsigned char *output_int_ray)
 {
    // ���ַ�����ת��Ϊ��������
    int length = strlen(input_char_array);
    for (int i = 0; i < length; i++) {
        output_int_ray[i] = input_char_array[i] - '0';
    }
  }


void control_flow(char* order)
{
	unsigned char intArray[3];
	charArrayToIntArray(order, intArray);//���ַ�����ת��Ϊ�������飬��ά��ʶ�������˳���������
	for(uint8_t i=0;i<3;i++)
	{
		if (i == 2)
		{
			flag2 = 1;
		}
		switch(intArray[i]-1)//���ݶ�ά��ʶ�������˳��ִ����Ӧ������
		{
			case 0:
				task1(MODE_2_NOT_EXECUT,NULL);
				break;
			case 1:
				task2(MODE_2_NOT_EXECUT,NULL);
				break;
			case 2:
				task3(MODE_2_NOT_EXECUT,NULL);
				break;
		}
	}
}


  void modeSelection(void) //ģʽѡ����
  {
    while (skip == 0)
    {
      Serial_GetNum(); //�Ӵ��ڽ������ݲ�����Serial_Num���ж���ѡ���ĸ�ģʽ
      if(Serial_Num == MODE1) //�ж��Ƿ�ѡ��ģʽ1
      {
				printf("page 1\xff\xff\xff"); //��ʾģʽ1ҳ��
				LED3_On(); //����LED3����ʾģʽѡ��ɹ�
        Pattern = MODE1; //����ģʽΪģʽ1
        skip = 1;//����ģʽѡ�񣬽���ģʽ1������������
				exit1 = 0;//�˳�ģʽ1������������
      }
      else if(Serial_Num == MODE2)
      {
				printf("page 2\xff\xff\xff");//��ʾģʽ2ҳ��
				LED3_On();
        Pattern = MODE2;
        skip = 1;
				exit1 = 0;
      }
      else if(Serial_Num == MODE3)
      {
				printf("page 3\xff\xff\xff");
				LED3_On();
        Pattern = MODE3;
        skip = 1;
				exit1 = 0;
      }
			else if(Serial_Num == MODE4)
      {
				printf("page 4\xff\xff\xff");
				LED3_On();
        Pattern = MODE4;
        skip = 1;
				exit1 = 0;
      }
    }
  }

  void modeExit(void) //���·��ؼ����˳�ģʽ
  {
    Serial_GetNum();//�Ӵ��ڽ������ݲ�����Serial_Num������
    if(Serial_Num == 16) //�ж��Ƿ��˳�ģʽ
    {
			printf("page 0\xff\xff\xff"); //�ص���ʼҳ��
      LED3_Off();//Ϩ��LED3����ʾģʽ�˳��ɹ�
      /*��ʼ��ȫ�ֱ���*/
      Pattern = 0;
      skip = 0;
			exit1 = 1;
			Voice_flag=0;
      flag2 = 0;
			digital_position = 0;
			
    }
  }

	
  void mode1(uint8_t pattern) //ģʽһ������������
  {
		uint8_t State=0;//״̬��
    while (pattern == MODE1 && exit1 == 0) //�ж�ģʽ�Ƿ�Ϊģʽһ���˳���־�Ƿ�Ϊ1
    { 
      Serial_GetNum();//�Ӵ��ڽ������ݲ�����Serial_Num
      value=Serial_Num;//���մ������ݣ���ֵ��value
      if (Voice_flag ==0)
      {
        HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_1,sizeof(VOICE_1), 1000);//������ʾ���ѽ���ģʽ1����ֻ˵һ��
        Voice_flag = 1;
      }
      
      if (value != 0 && State == 0 && value!=50 && value==18)
      {
        followTrail_distance(DISTANCE_FROM_INITIAL_POSITION_TO_QR_CODE);//ǰ������ά������
				Serial_Num=50;
        State = 1;//����״̬1
      }
      
      if(Serial_GetRxFlag() == 1 && State == 1 ) //���յ���ά������Ķ�ά��
      {
        /*�ж϶�ά��ʶ�������*/
				if (RxBuffer[0] == '1')  
				{  
						strcpy(tast, "123");  
				}  
				else if (RxBuffer[0] == '2')  
				{  
						strcpy(tast, "213");  
				}  
				else if (RxBuffer[0] == '3')  
				{  
						strcpy(tast, "312");  
				}  
        HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_12,sizeof(VOICE_12), 1000);//������ʾ����ά��ʶ��ɹ���
        serial_screen_output(tast);//��Ļ��ʾ��ά��ʶ�������
        HAL_Delay(2500);
        control_flow(tast);//���ݶ�ά��ʶ�������˳��ִ����Ӧ������
        State = 2;
      }	
			if(State == 2 ) //����ִ�����
      {
				printf("page 9\xff\xff\xff");//��ʾ����ҳ��
				State = 3;
				HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_10,sizeof(VOICE_10), 1000);//������ʾ������ִ����ϡ�
      }	
			modeExit();//���˳����˳�ģʽ
		}
  }
	
  
	 void mode2(uint8_t pattern)//ģʽ��������������
  {
		uint8_t State=0; //״̬��
    static uint8_t count=0;
    while (pattern == MODE2 && exit1 == 0)//�ж�ģʽ�Ƿ�Ϊģʽ�����˳���־�Ƿ�Ϊ1
    {
      if (Voice_flag ==0)
      {
        HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_6,sizeof(VOICE_6), 1000);//������ʾ���ѽ���ģʽ2����ֻ˵һ��
        Voice_flag = 1;
      }
			
			if (State == 0 && Serial_GetRxFlag_rfid() == 1 )//�������̨�ϼ�⵽RFID��ǩ���룬�ж�����Ƿ�ŵ�������
      {
				if (Rfid_Get_Num() == 1)//�ж�����Ƿ�Ϊ1�����
				{
					task1(MODE_2_EXECUTION,count);//ִ������1�������ŵ�1��λ
          count++;
				}
				else if (Rfid_Get_Num() == 2)//�ж�����Ƿ�Ϊ2�����
				{
					task2(MODE_2_EXECUTION,count);//ִ������2�������ŵ�2��λ
          count++;
				}
				else if (Rfid_Get_Num() == 3)//�ж�����Ƿ�Ϊ3�����
				{
					task3(MODE_2_EXECUTION,count);//ִ������3�������ŵ�3��λ
          count++;//��������1
				}
        if (count == 3)//�������������3��˵����������ִ�����
        {
          count = 0;
          State = 1;
        }
      if(State == 1 ) 
      {
				printf("page 9\xff\xff\xff");//��ʾ����ҳ��
				State = 3;
				HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_10,sizeof(VOICE_10), 1000);//������ʾ������ִ����ϡ�
      }	
      }
		 modeExit();//���˳����˳�ģʽ
		}
  }
	
  
	 void mode3(uint8_t pattern)//ģʽ��������������
  {
    uint8_t State=0,a=0;
		Serial_Num=0;
    while (pattern == MODE3 && exit1 == 0)
    { 
   	  Serial_GetNum();//�Ӵ��ڽ������ݲ�����Serial_Num
      value=Serial_Num;
      if (Voice_flag ==0)
      {
        HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_7,sizeof(VOICE_7), 1000);//������ʾ���ѽ���ģʽ3����ֻ˵һ��
        Voice_flag = 1;
      }
      if (value != 0 && State == 0 && a < 3 && value!=50)
      {
        sequential_number[a] = value;//���������ݴ������飬��ʾ�˹������˳��
        a++;
				Serial_Num=50;
      }
      if (a == 3 && State == 0 && sequential_number[2] != 0 && sequential_number[0] != 0 && sequential_number[1] != 0)//����˹��������
      {
				State = 1;
        uint8_array_to_number_string(sequential_number, sizeof(sequential_number) / sizeof(sequential_number[0])); //������ת��Ϊ�ַ�������ʾ˳�����ȫ�ֱ���output
      }
      if (State == 1)
      {
				printf("t0.txt=\"%s\"\xff\xff\xff",output);//��Ļ��ʾ˳��
				LED3_Turn();
				State = 2;//����״̬2
      }
			if(State == 2 && value!=50 && value==18) 
      {
        control_flow(output);//����˳��ִ����Ӧ������
        State = 3;//����״̬3
      }	
			if(State == 3 ) 
      {
				printf("page 9\xff\xff\xff");//��ʾ����ҳ��
				State = 4;
				HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_10,sizeof(VOICE_10), 1000);//������ʾ������ִ����ϡ�
      }
			modeExit();//���˳����˳�ģʽ
		}
  }

	
  void mode4(uint8_t pattern)//ģʽ�ĵ�����������
  {
		uint8_t speed = 15;
    while (pattern == MODE4 && exit1 == 0)//�ж�ģʽ�Ƿ�Ϊģʽ�ģ��˳���־�Ƿ�Ϊ1
    {
      Serial_GetNum();//�Ӵ��ڽ������ݲ����ñ���Serial_Num
			if (Voice_flag ==0)
      {
        HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_8,sizeof(VOICE_8), 1000);//������ʾ���ѽ���ģʽ4����ֻ˵һ��
        Voice_flag = 1;//ֻ��ʾһ��
      }
     
      if(Serial_Num == 8)//���ǰ���ǰ����������������С��ǰ��
      {
        MOTOR_A_SetSpeed(-speed);
        MOTOR_B_SetSpeed(-(speed+1));
        MOTOR_C_SetSpeed(speed+1);
        MOTOR_D_SetSpeed(speed);
      }

     
      if(Serial_Num == 11)//���ǰ��º��˼�������������С������
      {
        MOTOR_A_SetSpeed(speed);
        MOTOR_B_SetSpeed(speed+1);
        MOTOR_C_SetSpeed(-(speed+1));
        MOTOR_D_SetSpeed(-speed);
      }

     
      if(Serial_Num == 7)//���ǰ�����ת��������������С����ת
      {
        MOTOR_A_SetSpeed(speed);
        MOTOR_B_SetSpeed(-speed);
        MOTOR_C_SetSpeed(-speed);
        MOTOR_D_SetSpeed(speed);
      }

      
      if(Serial_Num == 9)//���ǰ�����ת��������������С����ת
      {
        MOTOR_A_SetSpeed(-speed);
        MOTOR_B_SetSpeed(speed);
        MOTOR_C_SetSpeed(speed);
        MOTOR_D_SetSpeed(-speed);
      }

   
      if(Serial_Num == 15)//���ǰ���ֹͣ������ֹͣ����С��
      {
        MOTOR_A_SetSpeed(0);
        MOTOR_B_SetSpeed(0);
        MOTOR_C_SetSpeed(0);
        MOTOR_D_SetSpeed(0);
      }
			modeExit();//���˳����˳�ģʽ
    }
  }
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART10_UART_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_UART4_Init();
  MX_USART1_UART_Init();
  MX_USART6_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&RxData, 1);
	HAL_UART_Receive_IT(&huart3, (uint8_t *)&Res, 1);
	HAL_UART_Receive_IT(&huart10, (uint8_t *)&RxData, 1);
	HAL_UART_Receive_IT(&huart6, (uint8_t *)&RxData, 1);
	HAL_UART_Receive_IT(&huart1, (uint8_t *)&RxData_rfid, 1);
	ServoPWM_Start();
  MotorPWM_Start(); //����PWM
	servoControl(0); //��ʼ�����
	printf("page 0\xff\xff\xff"); //��ʾ���ص���ʼ����
	//serial_screen_output("321");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    

   /*����ģʽѡ��*/
   LED2_On(); //LED2���𣬱�ʾ��������

	 modeSelection();//ģʽѡ�������ж�ģʽ��������Ӧ��ģʽ�������ı�Pattern�����ж�ģʽ��0Ϊ��ֵ��1Ϊģʽһ��2Ϊģʽ����3Ϊģʽ����4Ϊģʽ��
	 mode1(Pattern);//ģʽһ����
	 mode2(Pattern);//ģʽ������
	 mode3(Pattern);//ģʽ������
	 mode4(Pattern);//ģʽ�ĺ���
		
			/* UART TEST */
//		 HAL_UART_Transmit(&huart6, (uint8_t*)"Received: ", 10, 1000); 
//		 HAL_Delay(1100);
//   HAL_UART_Transmit(&huart10, (uint8_t*)VOICE_1, 12, 1000);
//   HAL_Delay(1000);
		
		/* LED TEST */
		// LED2_On();
		//serial_screen_output("321");
//		 HAL_Delay(1000);
//		 LED2_Off();
//		 HAL_Delay(1000);
//     if(Key_Num1() == 1)
//		 {
//		   LED3_Turn();
//			 serial_screen_output("321");
//     }
		
//		/* PWM TEST */

//     if(Key_Num1() == 1)
//		 {
////		   moving_forward(20, 1000);
////			 HAL_Delay(1000);
////			 moving_backwards(20, 2000);
////			 moving_left(10, 300);
////			 moving_right(10, 300);
////		  MOTOR_A_SetSpeed(-10);
////		  MOTOR_B_SetSpeed(-10);
////			MOTOR_C_SetSpeed(10);
////			MOTOR_D_SetSpeed(-10);
//			 turnRight();  
//			 
//     }
//		moveForward();  

		/*Servo TEST*/
//    if(Key_Num1() == 1)
//    {
//			rotate_servo(50, 40);
//			LED3_Turn();
//			servoControl(0);
//    }
    
    /*UART TEST*/
//		int16_t number = 0;
//    char strNumber[10]; 
//    number = __HAL_TIM_GET_COUNTER(&htim1);
//    decimalToString(number, strNumber);
//		 
//		if(Key_Num1() == 1)
//		{
//			printf("page 4\xff\xff\xff"); 
//    }
//    printf("Number of Encoder: %s\n", strNumber);
//		HAL_Delay(1000);


	/*Bluetooth Test*/
//		Serial_GetNum();
//	  if(Key_Num1() == 1)
//		{
//			HAL_UART_Transmit(&huart10, &Serial_Num, 1, 1000); 
//	    LED3_Turn();
//    }


//   /*mode test*/
//  modeSelection();
//  mode1(Pattern);
//  mode2(Pattern);
//  mode3(Pattern);
//  mode4(Pattern);

    /*xunji TEST*/
//    uint8_t leftValue = HAL_GPIO_ReadPin(GPIOE, LEFT_SENSOR);  
//    uint8_t leftCenterValue = HAL_GPIO_ReadPin(GPIOE, LEFT_CENTER_SENSOR);  //闂備浇娉曢崳锕傚�?閿燂�?????1 闂備浇娉曢崳锕傚�?閿燂�?????0
//    uint8_t rightCenterValue = HAL_GPIO_ReadPin(GPIOE, RIGHT_CENTER_SENSOR);  
//    uint8_t rightValue = HAL_GPIO_ReadPin(GPIOE, RIGHT_SENSOR); 
//    printf("leftValue:%d\n",leftValue);
//    printf("leftCenterValue:%d\n",leftCenterValue);
//    printf("rightCenterValue:%d\n",rightCenterValue);
//    printf("rightValue:%d\n",rightValue);
//    printf("-----------\n");
//		HAL_Delay(500);	

//    uint8_t leftValue = HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_0);  
//    uint8_t leftCenterValue = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1);  //闂備浇娉曢崳锕傚�?閿燂�?????1 闂備浇娉曢崳锕傚�?閿燂�?????0
//    uint8_t rightCenterValue = HAL_GPIO_ReadPin(GPIOE, RIGHT_CENTER_SENSOR);  
//    uint8_t rightValue = HAL_GPIO_ReadPin(GPIOE, RIGHT_SENSOR); 

//	 if (leftValue == 1)  //black 1 write 0
//		 {
//				LED3_On();
//      
//     }
//		else
//		{
//			LED3_Off();
//		}

//		followTrail();

//		if(Key_Num1() == 1)
//		{
//			LED3_Turn();
////			moving_right(25, 2550);
////			RotateOnce(1500);
//			HandsomeReturnToPlace();
////		followTrail_distance(2000);
////			returnToStartingPoint();
////			arriving_the_starting_point_sign = 0;
////			count_state = 0;
//    }

		/*rfid TEST*/
//		if (Serial_GetRxFlag_rfid() == 1)
//		{
//			HAL_UART_Transmit(&huart1, (uint8_t*)"11", 2, 1000);
//			if (Rfid_Get_Num() == 1)
//			{
//				LED3_Turn();
//				HAL_UART_Transmit(&huart1, (uint8_t*)"01", 2, 1000);
//			}
//      else if (Rfid_Get_Num() == 2)
//      {
//				LED3_Turn();
//        HAL_UART_Transmit(&huart1, (uint8_t*)"02", 2, 1000);
//      }
//      else if (Rfid_Get_Num() == 3)
//      {
//				//LED3_Turn();
//        HAL_UART_Transmit(&huart1, (uint8_t*)"03", 2, 1000);
//      }
//    
//		}
//		 if(Key_Num1() == 1)
//		 {
//		    HAL_UART_Transmit(&huart1, (uint8_t*)"99", 2, 1000);
//     }

		/*bizhang TEST*/
//    uint8_t obstacle_avoidance_back = HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_1);  
//		uint8_t obstacle_avoidance_ahead = HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_9); 
//	  if (obstacle_avoidance_ahead == 0)   
//    {
//      LED3_On();
//    }
//    else
//    {
//      LED3_Off();
//    }

		/*voice TEST*/
//    if(Key_Num1() == 1)
//		 {
//			 LED3_Turn();
//			 HAL_UART_Transmit(&huart4, (uint8_t*)VOICE_12,sizeof(VOICE_12), 1000);
////		VoiceAnnouncements((uint8_t *)VOICE_2);
//    }  
		/*hengyi TEST*/
//		static int16_t a = 1600;
//    if(Key_Num1() == 1)
//		 {
//			  LED3_Turn();
//				RotateOnce(a); //1800
//			  a+=100;
//			 moving_right(25, 2700);
//			 HandsomeReturnToPlace();
//     } 
		 
		 /*tuxiang TEST*/
//		 if (digital_position == 1)
//		 {
//				LED3_On();
//      
//     }
//		 if (digital_position == 2)
//		 {
//				LED3_Off();
//      
//     }
//		 if (digital_position == 3)
//		 {
//				LED3_On();
//      
//     }

		/*xunji_back TEST*/
//      static uint8_t State1 = 1;
//		  if(Serial_GetRxFlag() == 1 && State1 == 1 ) 
//      {
//				if (RxBuffer[0] == '1')  
//				{  
//						strcpy(tast, "123");  
//				}  
//				else if (RxBuffer[0] == '2')  
//				{  
//						strcpy(tast, "213");  
//				}  
//				else if (RxBuffer[0] == '3')  
//				{  
//						strcpy(tast, "321");  
//				}  
//        printf("page 1\xff\xff\xff");
//        serial_screen_output(tast);
//        HAL_Delay(2000);
////        control_flow(tast/*,MODE_1_EXECUTION*/);
//        State1 = 2;
//      }	
//			if(State1 == 2 ) 
//      {
//				printf("page 9\xff\xff\xff");
//				State1 = 3;
//      }	
		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = 64;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 32;
  RCC_OscInitStruct.PLL.PLLP = 1;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_3;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 4096;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

 /* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
