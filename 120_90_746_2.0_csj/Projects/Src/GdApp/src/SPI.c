#include "SPI.h"
#include "hw_init.h"


uint8_t SPI_Read_Byte(uint8_t pData)
{
	uint8_t temp;
	uint8_t ret=0;
	
	#if    NK2047A
	
	ret=HAL_SPI_Receive(&hspi6, &temp, 1,100);
	#elif  NK2047B
	ret=HAL_SPI_Receive(&hspi3, &temp, 1,100);
	#elif NK1092A
	ret=HAL_SPI_Receive(&hspi4, &temp, 1,100);
	#endif
	
	return temp;
}

void SPI_SendByte(uint8_t pData)
{
	uint8_t temp;
	
	#if   NK2047A
	HAL_SPI_TransmitReceive(&hspi6,&pData,&temp,1,100);
	#elif NK2047B
	HAL_SPI_TransmitReceive(&hspi3,&pData,&temp,1,100);
	#elif NK1092A
	HAL_SPI_TransmitReceive(&hspi4,&pData,&temp,1,100);
	#endif
}
void SPI_FLASH_CS_LOW(void)
{
	#if   NK2047A
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_8,GPIO_PIN_RESET);
	#elif NK2047B
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,GPIO_PIN_RESET);
	#elif NK1092A
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_RESET);
	#endif
}	
void SPI_FLASH_CS_HIGH(void)
{
	#if   NK2047A
	HAL_GPIO_WritePin(GPIOG, GPIO_PIN_8,GPIO_PIN_SET);
	#elif NK2047B
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0,GPIO_PIN_SET);
	#elif NK1092A
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4,GPIO_PIN_SET);
	#endif
}	
