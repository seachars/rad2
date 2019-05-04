/**
  ******************************************************************************
  * @file    USB_Device/CDC_Standalone/Src/main.c
  * @author  Smile
  * @version V2.0.0
  * @date    28-Oct-2018
  * @brief   Sensor Capture&&USB device  Demo main file
  ******************************************************************************
**/
#include "hw_init.h"
#include "gd_app.h"
#include "Varible.h"
#include "GD_Flash.h"
#include "Uart_App.h"
#include "Sensor_Control.h"
#include "Sensor.h"
#include "Shutter.h"
#include "SPI.h"
#include "I2C.h"
#include "cLCD.h"

int get_cnt=0;
int process_cnt=0;

int main(void)
{
  	Board_Init(); //板上硬件初始化
	Sensor_Init(); //模组及其外设初始化
	
	Image_Parameter120.shutter_id=SEL_LOOP;	
	//在id为0时再响应其他非零值，避免状态机不能跳出
	uint32_t r=0x3f;
	uint32_t g=0x5f;
	uint32_t b=0x7f;


  while (1)
  {
  		
  		
		if(Image_Parameter120.Image_Ready==1) //保证一帧数据的完整性
		{

			 //闭环状态机
			if(Image_Parameter120.shutter_id!=IDLE)
			  Image_Parameter120.shutter_id=Shutter_State((unsigned short*)(Image_Parameter120.X_Data),Image_Parameter120.shutter_id,Sensor120_Parameter.Flash_Parameter120.Reg_Data120,Loop_Data120);
			
			 Deal_Uart();		//USB指令执行
				
			 if(Uart_Parameter120.Uart_Protocl120.USB_OTG_dev.dev_state == USBD_STATE_CONFIGURED)
			 {
				 //USB指令接收
					USBD_CDC_ReceivePacket(&Uart_Parameter120.Uart_Protocl120.USB_OTG_dev);
					if(Uart_Parameter120.Uart_Protocl120.USB_ReceiveLength>0)
					{
						Uart_Parameter120.Uart_Protocl120.deal_pos=0;
						//USB命令解析
						USB_Appcall();							
						Uart_Parameter120.Uart_Protocl120.USB_ReceiveLength=0;
					}
					
					if(Image_Parameter120.shutter_id<=SHUTTER)
					{	
						Video_Process();	//图像处理//////////////////////
					  //send////////////
						Send_Process(Sensor120_Parameter.test_mode);	//根据上位机请求上报不同的图像数据	//////////////////
						process_cnt++;
					}						
				}			 
				Image_Parameter120.Image_Ready=0;			
		}				
	}

  
}


void BSP_CAMERA_FrameEventCallback(void) //DCMI帧中断回调
{
		//DMA获取数据到原始数据存储区
		if(Image_Parameter120.Image_Ready!=1)
		{			
			 DMA_Copy((uint32_t)(Image_Parameter120.temp_xdata+COLUMN*4),(uint32_t)Image_Parameter120.X_Data,COLUMN*ROW*2);				
			 Image_Parameter120.Image_Ready=1;
			 get_cnt++;
		}
		
		LED2_ONOFF();
	 	APP_Tick();	  //获取各温传温度信息	快门控制策略		
		
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
