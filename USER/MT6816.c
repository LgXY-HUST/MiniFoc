#include "MT6816.h"

uint16_t ToSendVal[2]={reg03 , reg04};
uint16_t ToReadVal[2]={0};
float getmagval=0;
void MT6816_Init(void)
{
	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_12 , GPIO_PIN_SET);	
}

float MT6816_ReadVal(void)
{
	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_12 , GPIO_PIN_RESET);
  HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)&ToSendVal[0], (uint8_t *)&ToReadVal[0], 1, HAL_MAX_DELAY);	
//	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_12 , GPIO_PIN_SET);	
//	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_12 , GPIO_PIN_RESET);
  HAL_SPI_TransmitReceive(&hspi2, (uint8_t *)&ToSendVal[1], (uint8_t *)&ToReadVal[1], 1, HAL_MAX_DELAY);	
	HAL_GPIO_WritePin(GPIOB , GPIO_PIN_12 , GPIO_PIN_SET);			
	float val=(((ToReadVal[0]&0xff)<<6)+((ToReadVal[1]&0xf6)>>2));	
	//return (((ToReadVal[0]&0xff)<<6)+((ToReadVal[1]&0xf6)>>2));///16384.f*360.f;
	return val;

}

