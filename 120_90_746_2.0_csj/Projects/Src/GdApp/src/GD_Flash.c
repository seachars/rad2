#include "GD_Flash.h"
#include "uart_app.h"
#include "main.h"
#include "Own_Defines.h"
#include "Varible.h"
/********************************************************************/

/********************************************************************/
//设置参数后保存参数
void  Set_Parameter(void)
{
	uint8_t i=0;
	uint32_t check=0;
	HAL_FLASH_Unlock();
	HAL_FLASH_OB_Unlock();
	FLASH_Erase_Sector(FLASH_SECTOR_4,FLASH_VOLTAGE_RANGE_3);	
	for(i=0;i<40;i=i+4)
	{	
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Parma_ADDRESS+i, Sensor120_Parameter.Flash_Parameter120.Reg_Data120[i/4].Reg_Value);
	}
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Parma_ADDRESS+40,Sensor120_Parameter.Flash_Parameter120.VSK_Value);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Parma_ADDRESS+44,Sensor120_Parameter.INT_Value);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Parma_ADDRESS+48,Sensor120_Parameter.Uart_Flag120.Update_flag);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Parma_ADDRESS+52,0x05);
	for(i=0;i<10;i++)
	{
		check=check+Sensor120_Parameter.Flash_Parameter120.Reg_Data120[i].Reg_Value;
	}
	check=check+Sensor120_Parameter.Flash_Parameter120.VSK_Value;
	check=check+Sensor120_Parameter.INT_Value;
	check=check+Sensor120_Parameter.Uart_Flag120.Update_flag;
	check=check+0x05;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Parma_ADDRESS+56,check);
	HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();
}


//恢复默认参数
void  Set_Parameter_Default(void)
{
	uint8_t i=0;
	uint32_t check=0;
	
	HAL_FLASH_Unlock();
	HAL_FLASH_OB_Unlock();
	
	FLASH_Erase_Sector(FLASH_SECTOR_4,FLASH_VOLTAGE_RANGE_3);	
	for(i=0;i<40;i=i+4)
	{	
		HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Parma_ADDRESS+i,Sensor120_Parameter.Reg_Data120_Backup[i/4]);
	}
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Parma_ADDRESS+40,Sensor120_Parameter.VSK_Backup);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Parma_ADDRESS+44,Sensor120_Parameter.INT_Backup);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Parma_ADDRESS+48,0x00);
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Parma_ADDRESS+52,0x05);
	for(i=0;i<10;i++)
	{
		check=check+Sensor120_Parameter.Reg_Data120_Backup[i];
	}
	check=check+Sensor120_Parameter.VSK_Backup;
	check=check+Sensor120_Parameter.INT_Backup;
	check=check+0x00;
	check=check+0x05;
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,Parma_ADDRESS+56,check);
	
	HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();
	for(i=0;i<10;i++)
	{
		Sensor120_Parameter.Flash_Parameter120.Reg_Data120[i].Reg_Value=Sensor120_Parameter.Reg_Data120_Backup[i];
	}
	Sensor120_Parameter.Flash_Parameter120.VSK_Value=Sensor120_Parameter.VSK_Backup;
	Sensor120_Parameter.INT_Value=Sensor120_Parameter.INT_Backup;
}

//开机从Flash中加载参数
void  Read_Parameter(void)
{
	uint8_t i=0;
	uint32_t temp1=0,temp2=0,temp3=0,temp4=0,temp5=0;
	uint32_t check=0;
	uint8_t data_temp[10];
	
	HAL_FLASH_Unlock();
	HAL_FLASH_OB_Unlock();
	
	for(i=0;i<40;i=i+4)
	{
		data_temp[i/4]=(int8_t)(*(__IO uint32_t*)(Parma_ADDRESS+i));		  
	}
	temp1=(int32_t)(*(__IO uint32_t*)(Parma_ADDRESS+40));	
	temp2=(int32_t)(*(__IO uint32_t*)(Parma_ADDRESS+44));
	temp3=(int32_t)(*(__IO uint32_t*)(Parma_ADDRESS+48));
	temp4=(int32_t)(*(__IO uint32_t*)(Parma_ADDRESS+52));
	temp5=(int32_t)(*(__IO uint32_t*)(Parma_ADDRESS+56));
	
	for(i=0;i<10;i++)
	{	
		check=check+data_temp[i];
	}
	check=check+temp1;
	check=check+temp2;
	check=check+temp3;
	check=check+0x05;
	
	if(check==temp5)
	{
		for(i=0;i<10;i++)
		{
			Sensor120_Parameter.Flash_Parameter120.Reg_Data120[i].Reg_Value=data_temp[i];
		}
		Sensor120_Parameter.Flash_Parameter120.VSK_Value=temp1;
		Sensor120_Parameter.INT_Value=temp2;
		Sensor120_Parameter.Uart_Flag120.Update_flag=temp3;
	}
	
	else
	{
		Sensor120_Parameter.Flash_Parameter120.VSK_Value=Sensor120_Parameter.VSK_Backup;
		Sensor120_Parameter.INT_Value=Sensor120_Parameter.INT_Backup;
//		Sensor120_Parameter.GFID_Value=
	}
	HAL_FLASH_OB_Lock();
	HAL_FLASH_Lock();
}