#ifndef __RFID_H__
#define __RFID_H__

#include "main.h"

uint8_t Serial_GetRxFlag_rfid(void);
uint8_t arrays_are_equal(const uint8_t *array1, size_t length1, const uint8_t *array2, size_t length2);
uint8_t Rfid_Get_Num(void);
 
#endif 
