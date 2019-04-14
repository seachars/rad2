#include "Own_Defines.h"
#include "Varible.h"
#include "Uart_App.h"
#include "GD_Flash.h"
#include "Sensor_Control.h"
#include "Sensor.h"

void setup_process(void)
{
	switch(Uart_Parameter120.Uart_Protocl120.g_ucoption_cmd)
	{

		case 5:
						Sensor120_Parameter.Uart_Flag120.g_ucsave_setting_en= \
		        Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;	

						break;
		case 6:
						Sensor120_Parameter.Uart_Flag120.g_ucfactory_default= \
						Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;							
						break;
		default:
						break;
	}
			

}

void  video_page1_process()
{
	switch(Uart_Parameter120.Uart_Protocl120.g_ucoption_cmd)
	{
		
		case 7:
						Sensor120_Parameter.test_mode=Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;				
						break;
		case 16:
					if(Image_Parameter120.shutter_id==IDLE)
								Image_Parameter120.shutter_id=NUC_LOOP;
						break;
		case 17:
						{
							if(Image_Parameter120.shutter_id==IDLE)
								Image_Parameter120.shutter_id=SHUTTER;		
							
							break;
						}
		default:
						break;
	}

}
void advance_process()
{
	switch(Uart_Parameter120.Uart_Protocl120.g_ucoption_cmd)
	{		
		
		default:
						break;
	}

}
void expert_page0_process()
{
	switch(Uart_Parameter120.Uart_Protocl120.g_ucoption_cmd)
	{		
		case 11:
						Sensor120_Parameter.Flash_Parameter120.VSK_Value=    \
		        (Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_h<<8)+Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;
						Sensor120_Parameter.Uart_Flag120.Set_VSK_Flag=1;
						break;
		
	default:
						break;
	}

}

void expert_page1_process()
{
	switch(Uart_Parameter120.Uart_Protocl120.g_ucoption_cmd)
	{
		
		
		case 6:
						Sensor120_Parameter.GFID_Value=(Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_h<<8)+Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;
						Sensor120_Parameter.Uart_Flag120.Set_GFID_Flag=1;
						break;
		case 7:
						Sensor120_Parameter.INT_Value=(Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_h<<8)+Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;
						if(Sensor120_Parameter.INT_Value>=73)
							Sensor120_Parameter.INT_Value=73;
						if(Sensor120_Parameter.INT_Value<=10)
							Sensor120_Parameter.INT_Value=10;
						Sensor120_Parameter.Uart_Flag120.Set_INT_Flag=1;
						break;
		case 8:
						Sensor120_Parameter.Gain_Value=Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;
						Sensor120_Parameter.Uart_Flag120.Set_Gain_Flag=1;
						break;
	  case 12:						
						
						break;		
		case 13:						
						
						break;	
		default:
						break;
	}

}

void expert_page2_process()
{
	switch(Uart_Parameter120.Uart_Protocl120.g_ucoption_cmd)
	{				
		case 1:

						break;
		case 2:

						break;
		case 3:

						break;		
		case 4:

						break;
		case 5:

						break;		
		default:
						break;
	}

}


void expert_page3_process()
{
	
	
	switch(Uart_Parameter120.Uart_Protocl120.g_ucoption_cmd)
	{		
   	
		case 0X0C:
						Sensor120_Parameter.VDAC_Value=Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;
						Sensor120_Parameter.Uart_Flag120.Set_VDAC_Flag=1;
						break;	
		case 0X0D:
						Sensor120_Parameter.RES_Value=Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;
						Sensor120_Parameter.Uart_Flag120.Set_RES_Flag=1;
						break;	
		case 0X0E:
						
						break;	
		case 0X0F:
						
						break;	
		
		case 0X13:
						Sensor120_Parameter.PWCTL_ADC=Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;
						Sensor120_Parameter.Uart_Flag120.Set_PWCTL_ADC_Flag=1;
						break;	
		case 0X14:
						Sensor120_Parameter.PWCTL_COL=Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;
						Sensor120_Parameter.Uart_Flag120.Set_PWCTL_COL_Flag=1;
						break;	
		case 0X15:
						Sensor120_Parameter.PWCTL=Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;
						Sensor120_Parameter.Uart_Flag120.Set_PWCTL_Flag=1;
						break;	
		case 0X16:
						Sensor120_Parameter.PCOMP=Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;
						Sensor120_Parameter.Uart_Flag120.Set_P_COMP_Flag=1;						
						break;	
		
	  case 0X17:
						Sensor120_Parameter.IDAC_VBIAS=Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;
						Sensor120_Parameter.Uart_Flag120.Set_IDAC_VBIAS_Flag=1;
						break;	
		case 0X18:
						Sensor120_Parameter.REF_SEL=Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;
						Sensor120_Parameter.Uart_Flag120.Set_REF_SEL_Flag=1;
						break;	
		case 0X19:
						Sensor120_Parameter.BIAS_MODE=Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;
						Sensor120_Parameter.Uart_Flag120.Set_BIAS_MODE_Flag=1;
						break;	
		case 0X1a:
						
						Sensor120_Parameter.Uart_Flag120.Update_flag=1;
						Set_Parameter();
						HAL_NVIC_SystemReset();				
				break;	
		case 0X1b:
							Sensor120_Parameter.NUC_All=Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l;
							NUC_All_Set(Sensor120_Parameter.NUC_All);
		
		break;	

		
		default:
						break;
	}

}

//Ì½²âÆ÷Ð­Òé½âÎö
void ProcessUart()
{	
	
	if(Uart_Parameter120.Uart_Protocl120.g_ucUart_rx_done==1||Uart_Parameter120.Uart_Protocl120.g_ucUSB_rx_done==1)
	{
		if(Uart_Parameter120.Uart_Protocl120.g_ucUart_rx_done==1)
		{
			Uart_Parameter120.Uart_Protocl120.g_ucfunction_cmd=Uart_Parameter120.Uart_Protocl120.g_RxBuffer[3];
			Uart_Parameter120.Uart_Protocl120.g_ucpage_cmd=Uart_Parameter120.Uart_Protocl120.g_RxBuffer[4];
			Uart_Parameter120.Uart_Protocl120.g_ucoption_cmd=Uart_Parameter120.Uart_Protocl120.g_RxBuffer[5];
			Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_h=Uart_Parameter120.Uart_Protocl120.g_RxBuffer[6];
			Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l=Uart_Parameter120.Uart_Protocl120.g_RxBuffer[7];
			Uart_Parameter120.Uart_Protocl120.g_ucUart_rx_done=0;

		}
		
		else if(Uart_Parameter120.Uart_Protocl120.g_ucUSB_rx_done==1)
		{
			Uart_Parameter120.Uart_Protocl120.g_ucfunction_cmd= \
			Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+3];
			Uart_Parameter120.Uart_Protocl120.g_ucpage_cmd=  \
			Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+4];
			Uart_Parameter120.Uart_Protocl120.g_ucoption_cmd= \
			Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+5];
			Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_h= \
			Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+6];
			Uart_Parameter120.Uart_Protocl120.g_ucdata_cmd_l= \
			Uart_Parameter120.Uart_Protocl120.USB_DATA_Buffer[Uart_Parameter120.Uart_Protocl120.deal_pos+7];
			Uart_Parameter120.Uart_Protocl120.g_ucUSB_rx_done=0;
			Uart_Parameter120.Uart_Protocl120.usb_option=1;
		
		}
		
		if(Uart_Parameter120.Uart_Protocl120.g_ucoption_cmd==0x00)
		{
				;
		}
		
		else if(Uart_Parameter120.Uart_Protocl120.g_ucfunction_cmd==SETUP_PAGE)
		{
			setup_process();
		}
		
		else if(Uart_Parameter120.Uart_Protocl120.g_ucfunction_cmd==VIDEO_PAGE )
			
		{
			if(Uart_Parameter120.Uart_Protocl120.g_ucpage_cmd==0x00)
			{
				video_page1_process();
			}
		}
		
		else if(Uart_Parameter120.Uart_Protocl120.g_ucfunction_cmd==ADVANCE_PAGE)
		{
			advance_process();
		}
		
		else if(Uart_Parameter120.Uart_Protocl120.g_ucfunction_cmd==EXPERT_PAGE)
		{
			if(Uart_Parameter120.Uart_Protocl120.g_ucpage_cmd==0x00)
			{
				expert_page0_process();
			}
			else if(Uart_Parameter120.Uart_Protocl120.g_ucpage_cmd==0x01)
			{
				expert_page1_process();
			}
			if(Uart_Parameter120.Uart_Protocl120.g_ucpage_cmd==0x02)
			{
				expert_page2_process();
			}
			if(Uart_Parameter120.Uart_Protocl120.g_ucpage_cmd==0x03)
			{
				expert_page3_process();
			}
			
		}
		
	}
}