#include "I2C.h"
#include "hw_init.h"
/**
  * @brief  Manages error callback by re-initializing I2C.
  * @param  Addr: I2C Address
  * @retval None
  */
static void I2Cx_Error(uint8_t num,uint8_t Addr)
{
	if(num==1)
	{
		/* De-initialize the I2C communication bus */
		HAL_I2C_DeInit(&hEvalI2c1);
	}
	
	if(num==2)
	{
		/* De-initialize the I2C communication bus */
		HAL_I2C_DeInit(&hEvalI2c2);
	}
	
	if(num==3)
	{
		/* De-initialize the I2C communication bus */
		HAL_I2C_DeInit(&hEvalI2c3);
	}		
		/* Re-Initialize the I2C communication bus */
		I2C_Init(num);	
}



/**
  * @brief  Reads multiple data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @param  MemAddress: internal memory address   
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
static HAL_StatusTypeDef I2Cx_ReadMultiple(I2C_HandleTypeDef hEvalI2cx,uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t num=0;
	
	
	if(hEvalI2cx.Instance==I2C1)
	{
		num=1;
	}
	
	if(hEvalI2cx.Instance==I2C2)
	{
		num=2;
	}
	
	if(hEvalI2cx.Instance==I2C3)
	{
		num=3;
	}
	
  status = HAL_I2C_Mem_Read(&hEvalI2cx, Addr, (uint16_t)Reg, MemAddSize, Buffer, Length, 300);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* I2C error occurred */
    I2Cx_Error(num,Addr);
  }
  return status;    
}

/**
  * @brief  Writes a value in a register of the device through BUS in using DMA mode.
  * @param  Addr: Device address on BUS Bus.  
  * @param  Reg: The target register address to write
  * @param  MemAddress: internal memory address  
  * @param  Buffer: The target register value to be written 
  * @param  Length: buffer size to be written
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_WriteMultiple(I2C_HandleTypeDef hEvalI2cx,uint8_t Addr, uint16_t Reg, uint16_t MemAddSize, uint8_t *Buffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;
	uint8_t num=0;
	
	if(hEvalI2cx.Instance==I2C1)
	{
		num=1;
	}
	
	if(hEvalI2cx.Instance==I2C2)
	{
		num=2;
	}
	
	if(hEvalI2cx.Instance==I2C3)
	{
		num=3;
	}
  
  status = HAL_I2C_Mem_Write(&hEvalI2cx, Addr, (uint16_t)Reg, MemAddSize, Buffer, Length, 300);
  
  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initiaize the I2C Bus */
    I2Cx_Error(num,Addr);
  }
  return status;
}



void I2C_ByteWrite(uint8_t Address, uint8_t WriteAddr, uint8_t dat)
{
	I2Cx_WriteMultiple(hEvalI2c2,Address,WriteAddr,I2C_MEMADD_SIZE_8BIT,&dat,1);
}

void I2C_Write(uint8_t *Buffer,uint8_t Addr,uint8_t len)
{
	I2Cx_WriteMultiple(hEvalI2c2,Addr,Buffer[0],I2C_MEMADD_SIZE_8BIT,&Buffer[1],len);
}

void I2C_Read(uint8_t Addr,uint8_t Reg,uint8_t *Buffer,uint8_t len)
{
	I2Cx_ReadMultiple(hEvalI2c2,Addr,Reg,I2C_MEMADD_SIZE_8BIT,(uint8_t*)(&Buffer[0]),len);
}


uint16_t I2C_ReadAds1110(unsigned char Address)
{
	uint8_t temp_Ads[3];
	HAL_I2C_Master_Receive(&hEvalI2c2,Address,temp_Ads,2,100);
	return (temp_Ads[0]<<8|temp_Ads[1]);
}

unsigned short int BoardADC_Read(void)
{
	
}