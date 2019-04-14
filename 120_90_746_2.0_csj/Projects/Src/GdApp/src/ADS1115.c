#include "ADS1115.h"
#include "I2C.h"

void ADS1115Write(uint8_t Reg,uint16_t Val)
{
	uint8_t Buf[3]={0};
	
  Buf[0]=Reg;
	Buf[1]=Val>>8&0x00ff;
	Buf[2]=Val&0x00ff;
	
	I2C_Write(Buf,0x90,2);//tep101 设置	//需重写	
}

uint16_t ADS1115ReadRegValue(uint8_t Addr,uint8_t Reg)
{
	uint8_t temp[2]={0};
	I2C_Read(Addr,Reg,temp,2);
	
	return (temp[0]<<8|temp[1]);
}

void ADSChanelSelect(uint8_t num)
{
	uint16_t Ret=0;
	switch(num)
	{
		case 0:
						{
							ADS1115Write(0x01,0xc383);//tep101 设置	//需重写	
							break;
						}
						
		case 1:
						{
							ADS1115Write(0x01,0xd383);//tep101 设置	//需重写
							break;
						}
						
		case 2:
						{
							ADS1115Write(0x01,0xe383);//tep101 设置	//需重写
							break;
						}
					
		default:
						break;		
	}
	
}


int16_t ShutterRead(void)
{
  volatile int ads_temputure=0;
	volatile int64_t ad=0;
	int64_t x3=0;
	int64_t x2=0;	

	ad=ADS1115ReadRegValue(0x91,0x00);

	ads_temputure =(12736130490197.3+121840.2729*ad*ad-4.0235*ad*ad*ad-1821807621.6914*ad)/1000000000; 

	return ads_temputure;
}

int16_t LenNTCRead(void)
{
	volatile int16_t ads_temputure=0;
  volatile int64_t ad1=0;	
	
	ad1=ADS1115ReadRegValue(0x91,0x00);

	
	ads_temputure =(12736130490197.3+121840.2729*ad1*ad1-4.0235*ad1*ad1*ad1-1821807621.6914*ad1)/1000000000; 
	
	return ads_temputure;
}


signed int Ads1110_Read(void)
{	
	volatile int ads_temputure=0;
	volatile int d;
	
	d=ADS1115ReadRegValue(0x91,0x00);
	ads_temputure = (338180000-18181.804*d)/10000; //*100  20180428	
	
	return ads_temputure;
}


void SensorUpdate(void)
{
	static uint16_t update_cnt=0;
	
	if(update_cnt<7)
				update_cnt++;
	else
		update_cnt=0;
	
	if(update_cnt==1)
	{
		ADSChanelSelect(2);
		
	}
	else if(update_cnt==2)
	{
		Sensor120_Parameter.FPA_Tem=Ads1110_Read();
	}
	else if(update_cnt==3)
	{
		ADSChanelSelect(0);
		
	}
	else if(update_cnt==4)
	{
		Sensor120_Parameter.NTC_Tem=LenNTCRead();
	}
	else if(update_cnt==5)
	{
		ADSChanelSelect(1);
		
	}
	else if(update_cnt==6)
	{
		Sensor120_Parameter.Temp101=ShutterRead();
	}

}	