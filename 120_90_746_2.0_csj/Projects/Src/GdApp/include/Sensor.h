#ifndef __SENSOR_H
#define __SENSOR_H

#define  IDLE         0
#define  SHUTTER      1
#define  NUC_LOOP     2
#define  GFID_LOOP    3
#define  SEL_LOOP     4

struct  SPI_Reg_Data
{
	const unsigned char Addr;
	unsigned char Reg_Value;
};

struct  Loop_Data
{
	unsigned short GFID_High;
	unsigned short GFID_Low;
	
	unsigned short RES_High;
	unsigned short RES_Low;
	
	unsigned short NUC_High;
	unsigned short NUC_Low;
	
	unsigned char  ONTime;
	unsigned char  OFFTime;
	unsigned char  HoldTime;
	
};

extern unsigned char IsShutter;

//版本信息
extern unsigned int GetVersion(void);

//探测器初始化类
//Sensor读写函数 
extern void SensorWriteReg(unsigned char addr,unsigned char dat);
extern unsigned char SensorReadReg(unsigned char addr);

extern void Sensor_Reg_Initial(struct SPI_Reg_Data *Reg_Data120);

extern void NUC_All_Set(unsigned char dat);

extern unsigned char Shutter_State(unsigned short*pus_data,unsigned char Shutter_id,struct SPI_Reg_Data *Reg_Data120,struct Loop_Data Loop_Data120);

//温度传感器类 仅适用于NK2074
extern signed int GetFPATem(unsigned char Address);
extern short int GetTep101_Tem(unsigned char Address);
extern short int NTC_Read(void);

//算法类
extern void MemoryAlloc(void);
extern unsigned short*NUCbyTwoPoint(unsigned short*pus_src_data);

extern void BadPointReplace(unsigned short *pus_src_data,unsigned short *pusGain,int nwidth,int nheight);

extern void gdRemoveFlashPoint( unsigned short *pus_src,unsigned short *pus_dst,int nwidth, int  nheight);

extern void gdSharpenImage(unsigned short* pSrc, unsigned short* pDst, int width, int height);
extern void gdTimeFieldFilter(unsigned short* pSrc, unsigned short* pCur, int nWidth, int nHeight, int nThre);

extern void gdLinearDRT(unsigned char* pDst, unsigned short* pSrc, int nWidth, int nHeight, int nDiscardRatio, int nBright, int nContrast);
extern void gdUndistort(unsigned short* pSrc, unsigned short* pDst, int nWidth, int nHeight);

#endif