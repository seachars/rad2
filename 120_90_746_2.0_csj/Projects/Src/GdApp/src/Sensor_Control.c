#include "Varible.h"
#include "Sensor_Control.h"
#include "Sensor.h"
#include "gd_app.h"
#include "GD_Flash.h"
#include "ADS1115.h"

//探测器初始化
void Sensor_Init(void)
{
	Read_Parameter();	
	
	INT_Configuration(Sensor120_Parameter.INT_Value); 
	
	Sensor_Reg_Initial(Sensor120_Parameter.Flash_Parameter120.Reg_Data120); //smile1	

	Read_Init_Para();
}


//定时读取温传
void APP_Tick()
{	
	static uint16_t time_cnt=0;
	#if (NK2047A||NK2047B)
	if(Image_Parameter120.time_1s==1)
	{			
			Sensor120_Parameter.FPA_Tem=GetFPATem(0x91);
		
			Sensor120_Parameter.Temp101=GetTep101_Tem(0x95);
		
			Sensor120_Parameter.NTC_Tem=NTC_Read();			

			Image_Parameter120.time_1s=0;					
	}	
	#elif NK1092A
	SensorUpdate();				
	#endif
	
	#if  AUTO_SHUTTER
	if(Image_Parameter120.shutter_id==IDLE)
	{	
		if (abs(Sensor120_Parameter.FPA_Tem-Image_Parameter120.PreShutterTemp)>Image_Parameter120.CompensateShuttterVtemp)
		{
			Image_Parameter120.shutter_id=SHUTTER;
			Image_Parameter120.PreShutterTemp=Sensor120_Parameter.FPA_Tem;
		}	
		
		if(abs(Sensor120_Parameter.FPA_Tem-Image_Parameter120.PreNUCTemp)>Image_Parameter120.CompensateNUCVtemp)
		{
			Image_Parameter120.shutter_id=NUC_LOOP;
			Image_Parameter120.PreNUCTemp=Sensor120_Parameter.FPA_Tem;			
		}

	}
	
	//计数器
	time_cnt++;	
	if(time_cnt%(Image_Parameter120.AutoCompensateTime*2*PERIOD_HALFMIN)==0) //6S
	{
		if(Image_Parameter120.shutter_id==IDLE)
		{
			Image_Parameter120.shutter_id=NUC_LOOP;
		}				
	}			
  #endif
}

//------------------------------------------------------------------
//解析上位机指令，进行探测器配置
void Sensor_ReConfig(void)
{
	
	if(Sensor120_Parameter.Uart_Flag120.Set_GFID_Flag==1) //GFID
	{
		
		if(Sensor120_Parameter.GFID_Value>=255)
			Sensor120_Parameter.GFID_Value=255;
		Sensor120_Parameter.Flash_Parameter120.Reg_Data120[3].Reg_Value=Sensor120_Parameter.GFID_Value;
		
		Sensor120_Parameter.Uart_Flag120.Set_GFID_Flag=0;
		Sensor120_Parameter.ReConfig_Flag=1;
	}
	
	if(Sensor120_Parameter.Uart_Flag120.Set_Gain_Flag==1)  //Gain
	{
		if(Sensor120_Parameter.Gain_Value>=7)
			Sensor120_Parameter.Gain_Value=7;
		Sensor120_Parameter.Flash_Parameter120.Reg_Data120[0].Reg_Value= \
		((Sensor120_Parameter.Gain_Value<<4)|(Sensor120_Parameter.Flash_Parameter120.Reg_Data120[0].Reg_Value&0x8F));
		
		Sensor120_Parameter.Uart_Flag120.Set_Gain_Flag=0;
		Sensor120_Parameter.ReConfig_Flag=1;
	}
	

	if(Sensor120_Parameter.Uart_Flag120.Set_VDAC_Flag==1)  //VDAC_TRM
	{
		
		if(Sensor120_Parameter.VDAC_Value>=15)
			Sensor120_Parameter.VDAC_Value=15;
		Sensor120_Parameter.Flash_Parameter120.Reg_Data120[2].Reg_Value= \
		((Sensor120_Parameter.VDAC_Value<<4)|(Sensor120_Parameter.Flash_Parameter120.Reg_Data120[2].Reg_Value&0x0f));		
		Sensor120_Parameter.Uart_Flag120.Set_VDAC_Flag=0;
		Sensor120_Parameter.ReConfig_Flag=1;

	}
	
	if(Sensor120_Parameter.Uart_Flag120.Set_RES_Flag==1)   //RES_SEL
	{
		if(Sensor120_Parameter.RES_Value>=15)
			Sensor120_Parameter.RES_Value=15;
		Sensor120_Parameter.Flash_Parameter120.Reg_Data120[2].Reg_Value= \
		((Sensor120_Parameter.RES_Value)|(Sensor120_Parameter.Flash_Parameter120.Reg_Data120[2].Reg_Value&0xF0));
		Sensor120_Parameter.Uart_Flag120.Set_RES_Flag=0;
		Sensor120_Parameter.ReConfig_Flag=1;

	}	

	
	if(Sensor120_Parameter.Uart_Flag120.Set_PWCTL_ADC_Flag==1)   //PWCTL_ADC
	{
		if(Sensor120_Parameter.PWCTL_ADC>=4)
			Sensor120_Parameter.PWCTL_ADC=4;
		
		Sensor120_Parameter.Flash_Parameter120.Reg_Data120[1].Reg_Value= \
		((Sensor120_Parameter.PWCTL_ADC<<4)|(Sensor120_Parameter.Flash_Parameter120.Reg_Data120[1].Reg_Value&0xCF));
		
		Sensor120_Parameter.Uart_Flag120.Set_PWCTL_ADC_Flag=0;
		Sensor120_Parameter.ReConfig_Flag=1;

	}
	
	if(Sensor120_Parameter.Uart_Flag120.Set_PWCTL_COL_Flag==1)   //PWCTL_COL
	{
		if(Sensor120_Parameter.PWCTL_COL>=4)
			Sensor120_Parameter.PWCTL_COL=4;
		
		Sensor120_Parameter.Flash_Parameter120.Reg_Data120[1].Reg_Value= \
		((Sensor120_Parameter.PWCTL_COL<<2)|(Sensor120_Parameter.Flash_Parameter120.Reg_Data120[1].Reg_Value&0xF3));
		
		Sensor120_Parameter.Uart_Flag120.Set_PWCTL_COL_Flag=0;
		Sensor120_Parameter.ReConfig_Flag=1;

	}
	
	if(Sensor120_Parameter.Uart_Flag120.Set_PWCTL_Flag==1)   //PWCTL
	{
		if(Sensor120_Parameter.PWCTL>=4)
			Sensor120_Parameter.PWCTL=4;
		
		Sensor120_Parameter.Flash_Parameter120.Reg_Data120[1].Reg_Value= \
		((Sensor120_Parameter.PWCTL)|(Sensor120_Parameter.Flash_Parameter120.Reg_Data120[1].Reg_Value&0xFC));
		
		Sensor120_Parameter.Uart_Flag120.Set_PWCTL_Flag=0;
		Sensor120_Parameter.ReConfig_Flag=1;

	}
	
	if(Sensor120_Parameter.Uart_Flag120.Set_P_COMP_Flag==1)   //P_COMP
	{
		if(Sensor120_Parameter.PCOMP>=4)
			Sensor120_Parameter.PCOMP=4;
		
		Sensor120_Parameter.Flash_Parameter120.Reg_Data120[7].Reg_Value= \
		((Sensor120_Parameter.PCOMP<<4)|(Sensor120_Parameter.Flash_Parameter120.Reg_Data120[7].Reg_Value&0xCF));
		
		Sensor120_Parameter.Uart_Flag120.Set_P_COMP_Flag=0;
		Sensor120_Parameter.ReConfig_Flag=1;

	}
	
	if(Sensor120_Parameter.Uart_Flag120.Set_IDAC_VBIAS_Flag==1)   //IDAC_VBIAS
	{
		if(Sensor120_Parameter.IDAC_VBIAS>=3)
			Sensor120_Parameter.IDAC_VBIAS=3;
		
		Sensor120_Parameter.Flash_Parameter120.Reg_Data120[4].Reg_Value= \
		((Sensor120_Parameter.IDAC_VBIAS)|(Sensor120_Parameter.Flash_Parameter120.Reg_Data120[4].Reg_Value&0xFC));
		
		Sensor120_Parameter.Uart_Flag120.Set_IDAC_VBIAS_Flag=0;
		Sensor120_Parameter.ReConfig_Flag=1;

	}
	
	if(Sensor120_Parameter.Uart_Flag120.Set_REF_SEL_Flag==1)   //REF_SEL
	{
//		if(Sensor120_Parameter.REF_SEL>=3)
//			Sensor120_Parameter.REF_SEL=3;
//		
//		Sensor120_Parameter.Flash_Parameter120.Reg_Data120[5].Reg_Value= \
//		((Sensor120_Parameter.REF_SEL<<3)|(Sensor120_Parameter.Flash_Parameter120.Reg_Data120[5].Reg_Value&0xF7));
		//设置RV_SEL
		
		if(Sensor120_Parameter.REF_SEL==1)
			Sensor120_Parameter.REF_SEL=3;
		
		Sensor120_Parameter.Flash_Parameter120.Reg_Data120[6].Reg_Value= \
		((Sensor120_Parameter.REF_SEL<<4)|(Sensor120_Parameter.Flash_Parameter120.Reg_Data120[6].Reg_Value&0xCF));
		
		Sensor120_Parameter.Uart_Flag120.Set_REF_SEL_Flag=0;
		Sensor120_Parameter.ReConfig_Flag=1;

	}
	
	if(Sensor120_Parameter.Uart_Flag120.Set_BIAS_MODE_Flag==1)   //BIAS_MODE
	{
		if(Sensor120_Parameter.BIAS_MODE>=1)
			Sensor120_Parameter.BIAS_MODE=1;
		
		Sensor120_Parameter.Flash_Parameter120.Reg_Data120[4].Reg_Value= \
		((Sensor120_Parameter.BIAS_MODE<<5)|(Sensor120_Parameter.Flash_Parameter120.Reg_Data120[4].Reg_Value&0xDF));
		
		Sensor120_Parameter.Uart_Flag120.Set_BIAS_MODE_Flag=0;
		Sensor120_Parameter.ReConfig_Flag=1;

	}	

}