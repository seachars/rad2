#include "Varible.h"

//图像协议头尾
const unsigned char IMAGE_Head[10]={0x55,0xaa,0x03,0x04,0x06,0x07,0x08,0x09,0x10,0x1f};
const unsigned char IMAGE_End[10]={0x0c,0x0b,0x03,0x04,0x06,0x07,0x08,0x09,0x10,0x1f};

                         
//模组相关参数
struct Sensor_Parameter Sensor120_Parameter={ \
			.ReConfig_Flag=0,
			.GFID_Value=200,
			.INT_Value=60,	
			.Gain_Value=1,
			.VDAC_Value=0x0f,
			.RES_Value=0x0a,
			.test_mode=0,
			
			.FPA_Tem=0x00,
			.NTC_Tem=0x00,
			.Temp101=0x00,
			.VSK_Backup=1023,
			.INT_Backup=50,
			.Reg_Data120_Backup={
														0x7f, 
														0x0c,
														0xea,
														0xc8,
														0x1c,
														0x30,
														0x00,
														0x30,
														0x6d,
														0x24,	
											    },
			.Flash_Parameter120={
														.VSK_Value=1023,
														.Reg_Data120={
																						{0x10,0x7f}, 
																						{0x15,0x0c},
																						{0x16,0xea},
																						{0x17,0xc8},
																						{0x18,0x1c},
																						{0x19,0x30},
																						{0x1a,0x00},
																						{0x1b,0x30},
																						{0xf0,0x6d},
																						{0xf1,0x24},	
														
																					},
													},											
};

//串口通信相关参数
 struct Uart_Parameter Uart_Parameter120={ \
			 .Uart_Protocl120={														
														.g_ucUSB_rx_done=0,
														.g_ucUart_rx_done=0,
														.g_ucfunction_cmd=0,
														.g_ucpage_cmd=0,
														.g_ucoption_cmd=0,
														.g_ucdata_cmd_h=0,
														.g_ucdata_cmd_l=0,
														.g_ucoption_num=0x0,
														.g_ucResponse_Sendchar_flag=0x0,
														.g_RxBuffer={0},
														.USB_DATA_Buffer={0},
			 
												},

};	
 
struct Loop_Data Loop_Data120={					
												
												.GFID_High=15000, 
												.GFID_Low=1000,
												.RES_High=15000,
												.RES_Low=1000,
												.NUC_High=6000,
												.NUC_Low=4000,
												.ONTime=2,
												.OFFTime=2,
												.HoldTime=1,
												};

//图像相关参数

 struct  Image_Parameter   Image_Parameter120 ={ 
      
			.us_avg_shutter=0,
			.g_usx_cursor=60,
      .g_usy_cursor=45,
			.Image_Ready=0,
			.time_1s=0,
			.AD_Values=0x3fff,
			.AutoCompensateTime=2,
	    .CompensateNUCVtemp=60,
	    .CompensateShuttterVtemp=20,
};
