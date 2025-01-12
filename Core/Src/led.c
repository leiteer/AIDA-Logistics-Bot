#include "gpio.h"

void LED3_On(void)
{
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
}

void LED3_Off(void)
{
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
}

void LED2_On(void)
{
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_SET);
}

void LED2_Off(void)
{
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_1, GPIO_PIN_RESET);
}

void LED2_Turn(void)
{
  HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_1);
}

void LED3_Turn(void)
{
  HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14);
}
