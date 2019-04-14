#ifndef __GD_APP_H
#define __GD_APP_H
#include "stm32f7xx.h"

uint16_t VCP_DataTx(uint8_t* Buf, uint32_t Len,uint8_t flag);
void Deal_Uart(void);
void Read_Init_Para(void);
void USB_Appcall(void);
void inquire_process_image(uint8_t mode);
void Video_Process(void);
void Send_Process(uint8_t mode);
#endif
