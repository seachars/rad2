
#ifndef __I2C_H
#define __I2C_H
#include "main.h"

extern  void I2C_ByteWrite(uint8_t Address, uint8_t WriteAddr, uint8_t dat);
extern  void I2C_Write(uint8_t*Buffer,uint8_t Addr,uint8_t len);
extern  void I2C_Read(uint8_t Addr,uint8_t Reg,uint8_t *Buffer,uint8_t len);
extern  uint16_t I2C_ReadAds1110(unsigned char Address);
#endif