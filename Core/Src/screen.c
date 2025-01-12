#include <stdio.h>
#include "usart.h"
#include "screen.h"

void serial_screen_output(char* str)
{
     // 通过串口输出到屏幕的函数，重复发送三次以确保显示
     printf("t1.txt=\"%s\"\xff\xff\xff",str);
     HAL_Delay(10);
     printf("t1.txt=\"%s\"\xff\xff\xff",str);
     HAL_Delay(10);
     printf("t1.txt=\"%s\"\xff\xff\xff",str);
     HAL_Delay(10);
}
