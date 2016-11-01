#include<stdio.h>
#include<stdint.h>
#include"common.h"
#include "stm32f3xx_hal.h"

void gpioinit(int mode)
{
if(mode != CMD_INTERACTIVE) {
    return;
  }
__GPIOE_CLK_ENABLE();

GPIO_InitTypeDef  GPIO_InitStruct;
GPIO_InitStruct.Pin = (GPIO_PIN_8 | GPIO_PIN_9 
| GPIO_PIN_10|GPIO_PIN_11 | GPIO_PIN_12 |GPIO_PIN_13 | GPIO_PIN_14 |GPIO_PIN_15);
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
GPIO_InitStruct.Alternate = 0;
HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
return;
}

void gpio(int mode)
{
if(mode != CMD_INTERACTIVE) {
    return;
  }

uint32_t pin;
uint32_t state;

fetch_uint32_arg(&pin);
fetch_uint32_arg(&state);

if((state != 0) && (state != 1))
{
printf("enter 0 or 1 in the second input\n");
}
else
{
switch(pin)
{
case 8:
HAL_GPIO_WritePin(GPIOE,GPIO_PIN_8,state);
break;

case 9:
HAL_GPIO_WritePin(GPIOE,GPIO_PIN_9,state);
break;

case 10:
HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,state);
break;

case 11:
HAL_GPIO_WritePin(GPIOE,GPIO_PIN_11,state);
break;

case 12:
HAL_GPIO_WritePin(GPIOE,GPIO_PIN_12,state);
break;

case 13:
HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,state);
break;

case 14:
HAL_GPIO_WritePin(GPIOE,GPIO_PIN_14,state);
break;

case 15:
HAL_GPIO_WritePin(GPIOE,GPIO_PIN_15,state);
break;

default:
printf("Enter between 8-15\n");
break;
}
}
}

ADD_CMD("gpioinit",gpioinit,"initializes the gpio ports");
ADD_CMD("gpio",gpio,"enter port no between 8-15 and then enter 1 or 0 to turn ON or OFF led's");
