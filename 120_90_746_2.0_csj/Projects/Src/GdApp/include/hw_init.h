#ifndef __HW_INIT_H
#define __HW_INIT_H

#include "main.h"

#define DMA_INSTANCE               DMA2_Stream0
#define DMA_CHANNEL                DMA_CHANNEL_0
#define EVAL_I2Cx_TIMING           ((uint32_t)0x40912732)

void Board_Init(void);
void DMA_Copy(uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);
void I2C_Init(uint8_t num);
void INT_Configuration(uint32_t Val); 

extern I2C_HandleTypeDef hEvalI2c1,hEvalI2c2,hEvalI2c3;
extern SPI_HandleTypeDef hspi3,hspi4,hspi5,hspi6;
#endif
