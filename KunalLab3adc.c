#include<stdio.h>
#include<stdint.h>
#include"common.h"
#include "stm32f3xx_hal.h"

ADC_HandleTypeDef hadc;

void gpiointADC()
{
int rc;
GPIO_InitTypeDef  GPIO_InitStruct;
__GPIOA_CLK_ENABLE();
__ADC1_CLK_ENABLE();

GPIO_InitStruct.Pin = GPIO_PIN_2;
GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
GPIO_InitStruct.Alternate = 0;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct); 

hadc.Instance = ADC1;
hadc.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV1;
hadc.Init.Resolution = ADC_RESOLUTION12b;
hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
hadc.Init.EOCSelection = EOC_SINGLE_CONV;
hadc.Init.LowPowerAutoWait = DISABLE;
hadc.Init.ContinuousConvMode = DISABLE;
hadc.Init.NbrOfConversion = 1;
hadc.Init.DiscontinuousConvMode = DISABLE;
hadc.Init.NbrOfDiscConversion = 0;
hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
hadc.Init.ExternalTrigConvEdge = 0;
hadc.Init.DMAContinuousRequests = DISABLE;
hadc.Init.Overrun = OVR_DATA_OVERWRITTEN;
rc = HAL_ADC_Init(&hadc);
if(rc != HAL_OK) {
printf("ADC1 initialization failed with rc=%u\n",rc);
}
}

uint32_t  ReadADC(int channel)
{
uint32_t val;

HAL_StatusTypeDef rc;
ADC_ChannelConfTypeDef config;
/* Configure the selected channel */
config.Channel = channel;
config.Rank = 1;  /* Rank needs to be 1, otherwise
no conversion is done */
config.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
config.SingleDiff = ADC_SINGLE_ENDED;
config.OffsetNumber = ADC_OFFSET_NONE;
config.Offset = 0;
rc = HAL_ADC_ConfigChannel(&hadc,&config);
if(rc != HAL_OK) {
printf(
"ADC channel configure failed with rc=%u\n",
(unsigned)rc);
return 0;
}

rc = HAL_ADC_Start(&hadc);
if(rc != HAL_OK) {
printf(
"ADC start failed with rc=%u\n",
(unsigned)rc);
return 0;
}

/* Wait for end of conversion */
rc = HAL_ADC_PollForConversion(&hadc, 100);
if(rc != HAL_OK) {
printf(
"ADC poll for conversion failed with "
"rc=%u\n",(unsigned)rc);
return 0;
}
/* Read the ADC converted values */
val = HAL_ADC_GetValue(&hadc);
/* Stop the ADC peripheral */
rc = HAL_ADC_Stop(&hadc);
if(rc != HAL_OK) {
printf("ADC stop failed with "
"rc=%u\n",(unsigned)rc);
return 0;
}
return val;
}

void CmdADC( int mode)
{
int Value;
if(mode!= CMD_INTERACTIVE) 
return;
Value = ReadADC(2);
printf("ADC value : %d \n", Value);
return;
}
ADD_CMD("adcInit", gpiointADC, "initialising adc")
ADD_CMD("adc", CmdADC,"read adc")

