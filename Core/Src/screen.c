#include <stdio.h>
#include "usart.h"
#include "screen.h"

void serial_screen_output(char* str)
{
     // ͨ�������������Ļ�ĺ������ظ�����������ȷ����ʾ
     printf("t1.txt=\"%s\"\xff\xff\xff",str);
     HAL_Delay(10);
     printf("t1.txt=\"%s\"\xff\xff\xff",str);
     HAL_Delay(10);
     printf("t1.txt=\"%s\"\xff\xff\xff",str);
     HAL_Delay(10);
}
