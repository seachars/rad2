
#ifndef __ADS1115_H
#define __ADS1115_H
#include "main.h"

extern int16_t LenNTCRead(void);
extern int16_t ShutterRead(void);
extern signed int Ads1110_Read(void);
extern void ADSChanelSelect(uint8_t num);
extern void SensorUpdate(void);
#endif