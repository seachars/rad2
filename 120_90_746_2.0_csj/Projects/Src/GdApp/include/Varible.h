#ifndef __VARIBLE_H
#define __VARIBLE_H

#include "Own_Defines.h"
#include "stm32f7xx.h"
#include "usbd_def.h"
#include "stm32f7xx_hal_def.h"
#include "Sensor.h"

struct Uart_Flag
{
	uint8_t Set_VSK_Flag;
	uint8_t Set_GFID_Flag;
	uint8_t Set_INT_Flag;
	uint8_t Set_Gain_Flag;
	uint8_t Set_VDAC_Flag;
	uint8_t Set_RES_Flag;
	
	uint8_t Set_PWCTL_ADC_Flag;
	uint8_t Set_PWCTL_COL_Flag;
	uint8_t Set_PWCTL_Flag;
	uint8_t Set_BIAS_MODE_Flag;
	uint8_t Set_IDAC_VBIAS_Flag;
	uint8_t Set_P_COMP_Flag;
	uint8_t Set_REF_SEL_Flag;
	
	uint8_t cursor_on;
	uint8_t g_ucsave_setting_en;
	uint8_t g_ucfactory_default;
	
	uint8_t Update_flag;

	uint8_t GFID_flag;
	uint8_t SEL_flag;	

};	 

 struct Uart_Protocl
{
	uint8_t usb_option;
	uint8_t g_ucUart_rx_done;
	
	uint8_t g_ucfunction_cmd;
	uint8_t g_ucpage_cmd;
	uint8_t g_ucoption_cmd;
	uint8_t g_ucdata_cmd_h;
	uint8_t g_ucdata_cmd_l;
	
	uint8_t g_RxBuffer[10];
	
	uint8_t g_ucUartRxLen;	
	uint8_t g_ucResponse_Sendchar_flag;
	uint8_t g_ucoption_num;
	
	
	uint8_t USB_DATA_Buffer[64];
	uint8_t check_state;
	uint8_t deal_pos;
	uint8_t g_ucUSB_rx_done;
	uint8_t USB_ReceiveLength;
	
	USBD_HandleTypeDef USB_OTG_dev;
};


struct Uart_Parameter
{
	struct Uart_Protocl Uart_Protocl120;
};

struct Flash_Parameter
{
	volatile uint16_t VSK_Value; //VSK	
	struct SPI_Reg_Data Reg_Data120[10]; 	
};

struct Sensor_Parameter
{
	uint8_t  ReConfig_Flag;
	uint16_t GFID_Value; //GFID

	uint8_t  INT_Value; //INT
	uint8_t  Gain_Value; //GAIN
	uint8_t  VDAC_Value; 
	uint8_t  RES_Value;
	
	uint8_t  PWCTL_ADC; //INT
	uint8_t  PWCTL_COL; //GAIN
	uint8_t  PWCTL; 
	uint8_t  BIAS_MODE;
	uint8_t  IDAC_VBIAS; //INT
	uint8_t  PCOMP; //GAIN 
	uint8_t  REF_SEL;
	
	uint8_t   test_mode;
	
	int16_t  FPA_Tem;
	int16_t  NTC_Tem;
	int16_t  Temp101;
	int16_t  NUC_All;
	const uint16_t VSK_Backup;
	const uint8_t INT_Backup;
	const uint8_t Reg_Data120_Backup[10]; //寄存器设置备份
	struct Flash_Parameter Flash_Parameter120;	
	struct Uart_Flag Uart_Flag120;
};



struct Image_Parameter
{
	uint8_t *temp_xdata;         
	uint8_t *X_Data;    

	uint16_t*Y16_Data;  

	uint16_t*Y16_LastData;
	
	unsigned int us_avg_shutter;

	unsigned char	 shutter_id;
	volatile uint8_t g_usx_cursor;
	volatile uint8_t g_usy_cursor;
	uint8_t Image_Ready;

	uint8_t time_1s;

	uint16_t AD_Values;
	
	uint8_t       AutoCompensateTime;
	uint16_t      CompensateNUCVtemp;      //焦温变化NUC闭环阈值
	uint16_t      CompensateShuttterVtemp; //焦温变化快门补偿阈值
	
	int16_t       PreNUCTemp;
	int16_t       PreShutterTemp;

};


extern struct Sensor_Parameter  Sensor120_Parameter;
extern struct Image_Parameter Image_Parameter120;
extern struct Uart_Parameter Uart_Parameter120;

extern const unsigned char IMAGE_Head[10];
extern const unsigned char IMAGE_End[10];
extern struct Loop_Data Loop_Data120;

#endif
