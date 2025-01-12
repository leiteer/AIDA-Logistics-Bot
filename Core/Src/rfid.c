#include "usart.h"
#include "rfid.h"
#include "screen.h"

extern uint8_t Serial_RxFlag_rfid,Serial_RxPacket_rfid[6];
extern uint8_t Rfid_1_str[6],Rfid_2_str[6],Rfid_3_str[6];

// 获取RFID串口接收标志位
uint8_t Serial_GetRxFlag_rfid(void)
 {
  if (Serial_RxFlag_rfid == 1)
  {
   Serial_RxFlag_rfid = 0;
   return 1;
  }
  return 0;
 }
 
 uint8_t arrays_are_equal(const uint8_t *array1, size_t length1, const uint8_t *array2, size_t length2) {  
    // 比较两个数组是否相等，如果长度不同则直接返回0，否则逐个元素比较
    if (length1 != length2) {  
        return 0;
    }  
    for (size_t i = 0; i < length1; i++) {  
        if (array1[i] != array2[i]) {  
            return 0;
        }  
    }  
 
    return 1; 
} 
 
 uint8_t Rfid_Get_Num(void)
{
    // 根据接收到的RFID数据判断对应的数字并输出到屏幕
    uint8_t num = 0;
  if (arrays_are_equal(Serial_RxPacket_rfid, 6, Rfid_1_str, 6))
  {
   serial_screen_output("1");
    num = 1;
  }
    else if (arrays_are_equal(Serial_RxPacket_rfid, 6, Rfid_2_str, 6))
    {
   serial_screen_output("2");
        num = 2;
    }
    else if (arrays_are_equal(Serial_RxPacket_rfid, 6, Rfid_3_str, 6))
    {
   serial_screen_output("3");
        num = 3;
    }
  //memset(Serial_RxPacket_rfid,0,sizeof(Serial_RxPacket_rfid));
    return num;
}
