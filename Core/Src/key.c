#include "gpio.h"
#include "key.h"

uint8_t Key_Num1(void)
{
  uint8_t Keynum = 0;
  if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 1)
  {
    HAL_Delay(20);
		while( HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 1);
		HAL_Delay(20);
		Keynum=1;
	}
  return Keynum;
}
