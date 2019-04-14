#include "gd_app.h"
#include "main.h"
#include "hw_init.h"
#include "uart_app.h"
#include "Varible.h"
#include "GD_Flash.h"
#include "hw_init.h"
#include "usbd_cdc.h"
#include "Sensor.h"
#include "Sensor_Control.h"
#include "SPI.h"


uint16_t VCP_DataTx(uint8_t* Buf, uint32_t Len,uint8_t Mode_flag)
{
	volatile uint32_t i=0;
	
	if(Mode_flag==1)
	{
		for(i=0;i<Len;i++)
		{				
			
			UserTxBuffer[UserTxBufPtrIn] = Buf[2*i];
			UserTxBufPtrIn++;			
			
			/* To avoid buffer overflow */
			if(UserTxBufPtrIn == APP_RX_DATA_SIZE)
			{
				UserTxBufPtrIn = 0;
			}				
		}		
	}
	
	if(Mode_flag==2)
	{
		for(i=0;i<Len;i+=2)
		{			
			
			UserTxBuffer[UserTxBufPtrIn] = Buf[i+1];
			UserTxBufPtrIn++;	

			if(UserTxBufPtrIn == APP_RX_DATA_SIZE)
			{
				UserTxBufPtrIn = 0;
			}				
			
			UserTxBuffer[UserTxBufPtrIn] = Buf[i];
				UserTxBufPtrIn++;		
			
			/* To avoid buffer overflow */
			if(UserTxBufPtrIn == APP_RX_DATA_SIZE)
			{
				UserTxBufPtrIn = 0;
			}			 	
		}			
  }
	
	else
	{
			for(i=0;i<Len;i++)//len=120*90*2=21600
			{
				UserTxBuffer[UserTxBufPtrIn] = Buf[i];
				UserTxBufPtrIn++;						
				/* To avoid buffer overflow */
				if(UserTxBufPtrIn == APP_RX_DATA_SIZE)
				{
				UserTxBufPtrIn = 0;
				}					
				  
			}	
///////////////////////////////////////////////////////			
//		if(Len==21600)
//		{
//			for(i=0;i<Len;i++)//len=120*90*2=21600
//			{
//				
//			if((Len-UserTxBufPtrIn-2)>0x0)
//			{
//				UserTxBuffer[Len-UserTxBufPtrIn-2] = Buf[i];
//			}
//				UserTxBufPtrIn++;						
//				/* To avoid buffer overflow */
//				if(UserTxBufPtrIn == APP_RX_DATA_SIZE)
//				{
//				UserTxBufPtrIn = 0;
//				}				  
//			}				
//		}
////////////////////////////////////////////////////////
			
	}
  return USBD_OK;
}


void Deal_Uart(void)
{	
	if(Sensor120_Parameter.Uart_Flag120.Set_INT_Flag==1)
	{
		INT_Configuration(Sensor120_Parameter.INT_Value);
		if(Sensor120_Parameter.INT_Value>=74)
			Sensor120_Parameter.INT_Value=74;
		Sensor120_Parameter.Uart_Flag120.Set_INT_Flag=0;		
	}
	
	Sensor_ReConfig();
	if(Sensor120_Parameter.ReConfig_Flag==1)
	{
		Sensor_Reg_Initial(Sensor120_Parameter.Flash_Parameter120.Reg_Data120); //smile1
		Sensor120_Parameter.ReConfig_Flag=0;
	}
						 
	if(Sensor120_Parameter.Uart_Flag120.g_ucsave_setting_en==1)
	{
		Set_Parameter();
		Sensor120_Parameter.Uart_Flag120.g_ucsave_setting_en=0;
	}
	
	if(Sensor120_Parameter.Uart_Flag120.g_ucfactory_default==1)
	{
		Set_Parameter_Default();
		Sensor120_Parameter.Uart_Flag120.g_ucfactory_default=0;
	}
	
}


void Read_Init_Para(void)
{
		uint8_t temp;
		temp=SensorReadReg(0x16);
		Sensor120_Parameter.RES_Value=temp&0X0F;		
		Sensor120_Parameter.VDAC_Value=(temp&0XF0)>>4;		
		Sensor120_Parameter.GFID_Value=SensorReadReg(0x17);		
		Sensor120_Parameter.Gain_Value=(SensorReadReg(0x10)>>4)&0X07;	
	  Sensor120_Parameter.PWCTL_ADC=((SensorReadReg(0x15)&0x30)>>4);
    Sensor120_Parameter.PWCTL_COL=((SensorReadReg(0x15)&0x0c)>>2);
	  Sensor120_Parameter.PWCTL=((SensorReadReg(0x15)&0x03)>>0);
	  Sensor120_Parameter.PCOMP=((SensorReadReg(0x1B)&0x30)>>4);
	  Sensor120_Parameter.IDAC_VBIAS=((SensorReadReg(0x18)&0x03)>>0);
		Sensor120_Parameter.REF_SEL=((SensorReadReg(0x1A)&0x30)>>4);
	  Sensor120_Parameter.BIAS_MODE=((SensorReadReg(0x18)&0x20)>>5);
}


void inquire_process_image(uint8_t mode)
{
	uint16_t i=0;
	volatile uint8_t status_data[240]={0};	
	
	//IsShutter
	status_data[0]=0x55;
	status_data[1]=0xaa;
	
	status_data[2]=Sensor120_Parameter.Flash_Parameter120.VSK_Value&0x00ff;
	status_data[3]=(Sensor120_Parameter.Flash_Parameter120.VSK_Value>>8)&0x00ff;
	
	status_data[4]=Sensor120_Parameter.INT_Value&0x00ff;
	status_data[5]=Sensor120_Parameter.Gain_Value;
	status_data[6]=Sensor120_Parameter.Flash_Parameter120.Reg_Data120[3].Reg_Value;
	status_data[7]=(Sensor120_Parameter.Flash_Parameter120.Reg_Data120[2].Reg_Value&0xf0)>>4;
	status_data[8]=Sensor120_Parameter.Flash_Parameter120.Reg_Data120[2].Reg_Value&0X0F;
	status_data[9]=Sensor120_Parameter.Uart_Flag120.cursor_on;
	
	status_data[10]=Image_Parameter120.g_usx_cursor;
		
	status_data[11]=Image_Parameter120.g_usy_cursor;
	
	status_data[12]=Image_Parameter120.AD_Values&0x00ff;
	status_data[13]=(Image_Parameter120.AD_Values>>8)&0x00ff;
	
	status_data[14]=Sensor120_Parameter.FPA_Tem&0x00ff;
	status_data[15]=(Sensor120_Parameter.FPA_Tem>>8)&0x00ff;
	
	status_data[16]=Sensor120_Parameter.Temp101&0x00ff;
	status_data[17]=(Sensor120_Parameter.Temp101>>8)&0x00ff;
	
	status_data[19]=0x00; //nuc
	status_data[20]=0x00; //本底
	status_data[21]=0x00; //nuc
	status_data[22]=0x00; //保存参数
	status_data[23]=0x00; //恢复参数
	
	status_data[24]=YEAR&0x00ff;
	status_data[25]=(YEAR>>8)&0x00ff;  
	status_data[26]=MONTH;
	status_data[27]=DAY;
	
	
	
	status_data[28]=Sensor120_Parameter.NTC_Tem&0x00ff;
	status_data[29]=(Sensor120_Parameter.NTC_Tem>>8)&0x00ff;
	
	status_data[30]=Sensor120_Parameter.PWCTL_ADC;
	status_data[31]=Sensor120_Parameter.PWCTL_COL;
	status_data[32]=Sensor120_Parameter.PWCTL;
	status_data[33]=Sensor120_Parameter.PCOMP;
	status_data[34]=Sensor120_Parameter.IDAC_VBIAS;
	status_data[35]=Sensor120_Parameter.REF_SEL;
	status_data[36]=Sensor120_Parameter.BIAS_MODE;
	
	status_data[39]=Sensor120_Parameter.NUC_All;
	status_data[40]=Sensor120_Parameter.test_mode;
	
	status_data[41]=IsShutter; //test; 计算K成功标志
	status_data[42]=IsShutter;
	
	status_data[43]=IsShutter;
	
	status_data[44]=Image_Parameter120.us_avg_shutter&0x00ff;
	status_data[45]=(Image_Parameter120.us_avg_shutter>>8)&0x00ff;
	
	
	status_data[101]=0;
	status_data[238]=0xC0;
	status_data[239]=0xF0;
	
	
	for(i=0;i<240;i++)
	{		
		UserTxBuffer[UserTxBufPtrIn] =status_data[i];
		UserTxBufPtrIn++;			
		
		/* To avoid buffer overflow */
		if(UserTxBufPtrIn == APP_RX_DATA_SIZE)
		{
			UserTxBufPtrIn = 0;
		}				
	}		
	
}


void Video_Process(void)
{
	uint32_t index=0;
	
	index=Image_Parameter120.g_usx_cursor*COLUMN+Image_Parameter120.g_usy_cursor;
	
	if(index<ROW*COLUMN-1)
		Image_Parameter120.AD_Values=*((unsigned short*)Image_Parameter120.X_Data+2*index);
	
	Image_Parameter120.Y16_Data=NUCbyTwoPoint((unsigned short*)(Image_Parameter120.X_Data));
}

void SendY16(void)
{
	#if Y16ALG
	if(Image_Parameter120.Y16_LastData==NULL)
	{
		Image_Parameter120.Y16_LastData=(uint16_t*)malloc(COLUMN*ROW*2); //分配DMA接受缓冲器
		memcpy((void*)Image_Parameter120.Y16_LastData,(void*)Image_Parameter120.Y16_Data,COLUMN*ROW*2);
	}
	else
		gdTimeFieldFilter((unsigned short*)Image_Parameter120.Y16_Data,Image_Parameter120.Y16_LastData, COLUMN, ROW,10);		

	gdSharpenImage(Image_Parameter120.Y16_LastData,(unsigned short*)Image_Parameter120.Y16_Data,COLUMN, ROW);	
	#endif
	
	VCP_DataTx((uint8_t*)(Image_Parameter120.Y16_Data),COLUMN*ROW*2,0);	
}

void SendY8(void)
{	
	gdUndistort((unsigned short *)(Image_Parameter120.Y16_Data), (unsigned short *)Image_Parameter120.X_Data, COLUMN, ROW);		
	gdLinearDRT((unsigned char *)Image_Parameter120.Y16_Data, (unsigned short *)Image_Parameter120.X_Data, COLUMN, ROW, 5, 50, 200);	
	
	VCP_DataTx((uint8_t*)(Image_Parameter120.Y16_Data),COLUMN*ROW*2,0);				
}

void Send_Process(uint8_t mode)
{
	VCP_DataTx ( (uint8_t*)IMAGE_Head, 10,0); //帧头
	switch(mode)
	{
		case 0: //Y16模式
					{						
						SendY16();
					}
					break;
		case 1: //测试模式
					{	
					
					}
					break;
		case 2: //Y8模式
					{
						SendY8();			
					}
					break;
		case 3: //X模式
					{
						VCP_DataTx((unsigned char *)(Image_Parameter120.X_Data),COLUMN*ROW*2,2);						
					}
					break;					
		default:
					break;
	}
	inquire_process_image(0); //参数行
	VCP_DataTx ( (uint8_t*)IMAGE_End, 10,0);	//帧尾
}




void USB_Appcall(void)
{
	uint8_t i=0;
	uint8_t check;
	for(i=0;i<Uart_Parameter120.Uart_Protocl120.USB_ReceiveLength;i++)
	{		
		while(Uart_Parameter120.Uart_Protocl120.deal_pos<Uart_Parameter120.Uart_Protocl120.USB_ReceiveLength)
		{
			switch(Uart_Parameter120.Uart_Protocl120.check_state)
			{
				case 0:							
								if(Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos]==0x55)
								{
									Uart_Parameter120.Uart_Protocl120.check_state=1;
								}
								else
								{
									Uart_Parameter120.Uart_Protocl120.check_state=0;
									Uart_Parameter120.Uart_Protocl120.deal_pos=Uart_Parameter120.Uart_Protocl120.deal_pos+1;								
								}
								break;
								
			 case 1:
							if(Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+1]==0xaa)
							{
								Uart_Parameter120.Uart_Protocl120.check_state=2;
							}
							else
							{							
								Uart_Parameter120.Uart_Protocl120.check_state=0;
								Uart_Parameter120.Uart_Protocl120.deal_pos=Uart_Parameter120.Uart_Protocl120.deal_pos+2;
							}
							break;
			 case 2:
						if(Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+2]==0x00|| \
							 Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+2]==0x05)
						{
							Uart_Parameter120.Uart_Protocl120.check_state=3;
						}
						else
						{
							Uart_Parameter120.Uart_Protocl120.check_state=0;
							Uart_Parameter120.Uart_Protocl120.deal_pos=Uart_Parameter120.Uart_Protocl120.deal_pos+3;	
						}
						break;
						
			 case 3:
						if(Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+2]==0x05)
						{
							Uart_Parameter120.Uart_Protocl120.check_state=3;
							check=Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+2]^ \
							      Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+3]^ \
							      Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+4]^ \
							      Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+5]^ \
							      Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+6]^ \
							      Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+7];												
							if(check==Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+8]&& \
								 Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+9]==0xF0)
							{
								Uart_Parameter120.Uart_Protocl120.g_ucUSB_rx_done=1;
								Uart_Parameter120.Uart_Protocl120.g_ucResponse_Sendchar_flag=1;
								Uart_Parameter120.Uart_Protocl120.g_ucoption_num=0x0;
								
								ProcessUart();
								
								Uart_Parameter120.Uart_Protocl120.check_state=0;
								Uart_Parameter120.Uart_Protocl120.deal_pos=Uart_Parameter120.Uart_Protocl120.deal_pos+10;
								
							}
							else
							{
								Uart_Parameter120.Uart_Protocl120.g_ucUSB_rx_done=0;								
								Uart_Parameter120.Uart_Protocl120.g_ucResponse_Sendchar_flag=1;
								Uart_Parameter120.Uart_Protocl120.g_ucoption_num=0x1;
								
								Uart_Parameter120.Uart_Protocl120.check_state=0;
								Uart_Parameter120.Uart_Protocl120.deal_pos=Uart_Parameter120.Uart_Protocl120.deal_pos+10;	
							}
						}
						else
						{
							Uart_Parameter120.Uart_Protocl120.check_state=0;
							Uart_Parameter120.Uart_Protocl120.deal_pos=Uart_Parameter120.Uart_Protocl120.deal_pos+10;	
						}
						break;
			 default:
								break;
			}
		}		
		
	}
}


	


