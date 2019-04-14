#ifndef __OWN_DEFINES_H
#define __OWN_DEFINES_H

#include "main.h"

//About Uart 
#define FRAME_HEADER0    0X55
#define FRAME_HEADER1    0XAA
#define RESPONSE_LEN     0X01
#define UPLINK_LEN       0X13
#define FRAME_END        0XF0
#define STATUS_PAGE   0X00
#define SETUP_PAGE    0X01
#define VIDEO_PAGE    0X02
#define ADVANCE_PAGE  0XA0
#define EXPERT_PAGE   0XA1
#define MACH_NAME     0x0a
#define Uart_TIME_OUT     0xffffff
//About PCBA
#define NK2047A 0
#define NK2047B 0
#define NK1092A 1
#define HARDWARE 1

#define Y16ALG       0  //Y16算法开关
#define AUTO_SHUTTER 1  //自动快门
#define PERIOD_HALFMIN  750//1500 自动快门时间

#define ROW 90	         //????
#define COLUMN	120 		//????

#define YEAR  2018
#define MONTH 0X06
#define DAY   0x17

#define Y16_DATA  0
#define TEST_DATA 1
#define Y8_DATA   2
#define X16_DATA  3
#define NUC_DATA  4
//256kB
#define ADDR_FLASH_SECTOR_1    ((uint32_t)0x08008000) 
#define ADDR_FLASH_SECTOR_2    ((uint32_t)0x08010000) 
#define ADDR_FLASH_SECTOR_3    ((uint32_t)0x08018000) 
#define ADDR_FLASH_SECTOR_4    ((uint32_t)0x08020000) /* Base address of Sector 22, 128 Kbytes */
#define ADDR_FLASH_SECTOR_5    ((uint32_t)0x08040000)
#define ADDR_FLASH_SECTOR_6    ((uint32_t)0x08080000)
#define ADDR_FLASH_SECTOR_7    ((uint32_t)0x080c0000)

#define Parma_ADDRESS             ADDR_FLASH_SECTOR_4


#define  LED1_ON()               HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_RESET)//led1
#define  LED1_OFF()              HAL_GPIO_WritePin(GPIOA,GPIO_PIN_3,GPIO_PIN_SET)//led1

#define  LED2_ON()               HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET)//led1
#define  LED2_OFF()              HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET)//led1
#define  LED2_ONOFF()            HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_8)//led1

						 
#define  SHUTTERON  { HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_SET);\
											 HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,GPIO_PIN_RESET);\
										 }
						         
#define  SHUTTEROFF  { HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET);\
												HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,GPIO_PIN_SET);\
										  }

#define  SHUTTERSTOP  { HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET);\
												 HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,GPIO_PIN_RESET);\
										  }													

#endif

								 
								 
								 

								 