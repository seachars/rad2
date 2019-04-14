#include "hw_init.h"
#include "Camera.h"
#include "Varible.h"
#include "gd_app.h"
#include "GD_Flash.h"
#include "Shutter.h"

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  /*##-1- Enable peripheral clock #################################*/
  /* TIMx Peripheral clock enable */
  TIMx_CLK_ENABLE();
  
  /*##-2- Configure the NVIC for TIMx ########################################*/
  /* Set the TIMx priority */
  HAL_NVIC_SetPriority(TIMx_IRQn, 3, 0);

  /* Enable the TIMx global Interrupt */
  HAL_NVIC_EnableIRQ(TIMx_IRQn);
}

void SystemClock_Config(void)
{
	
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
	
	RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
	
  HAL_StatusTypeDef  ret = HAL_OK;
  
  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();
  
  /* The voltage scaling allows optimizing the power consumption when the device is 
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */

	  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100; //216
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  //RCC_OscInitStruct.PLL.PLLR = 7;
  
  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
  /* Activate the OverDrive to reach the 200 MHz Frequency */  
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }
  
	

  // /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2; 
	
  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_8);
  if(ret != HAL_OK)
  {
    while(1) { ; }
  }

	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIQ = 2;
  PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV8;
  PeriphClkInitStruct.PLLSAIDivQ = 1;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
	PeriphClkInitStruct.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLLSAIP;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }	
}


void USB_Init(void)
{
	  /* Init Device Library */
  USBD_Init(&Uart_Parameter120.Uart_Protocl120.USB_OTG_dev, &VCP_Desc, 0);
  
  /* Add Supported Class */
  USBD_RegisterClass(&Uart_Parameter120.Uart_Protocl120.USB_OTG_dev, USBD_CDC_CLASS);
  
  /* Add CDC Interface Class */
  USBD_CDC_RegisterInterface(&Uart_Parameter120.Uart_Protocl120.USB_OTG_dev, &USBD_CDC_fops);
  
  /* Start Device Process */
  USBD_Start(&Uart_Parameter120.Uart_Protocl120.USB_OTG_dev);

}

//-----------------------------------------------------------------------DMA
void DMA_Copy(uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{
	DMA_HandleTypeDef     DmaHandle;
  /*## -1- Enable DMA2 clock #################################################*/

	
  /*##-2- Select the DMA functional Parameters ###############################*/
  DmaHandle.Init.Channel = DMA_CHANNEL;                     /* DMA_CHANNEL_0                    */
  DmaHandle.Init.Direction = DMA_MEMORY_TO_MEMORY;          /* M2M transfer mode                */
  DmaHandle.Init.PeriphInc = DMA_PINC_ENABLE;               /* Peripheral increment mode Enable */
  DmaHandle.Init.MemInc = DMA_MINC_ENABLE;                  /* Memory increment mode Enable     */
  DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE; /* Peripheral data alignment : Word */
  DmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;    /* memory data alignment : Word     */
  DmaHandle.Init.Mode = DMA_NORMAL;                         /* Normal DMA mode                  */
  DmaHandle.Init.Priority = DMA_PRIORITY_HIGH;              /* priority level : high            */
  DmaHandle.Init.FIFOMode = DMA_FIFOMODE_DISABLE;           /* FIFO mode disabled               */
  DmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  DmaHandle.Init.MemBurst = DMA_MBURST_SINGLE;              /* Memory burst                     */
  DmaHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;           /* Peripheral burst                 */

  /*##-3- Select the DMA instance to be used for the transfer : DMA2_Stream0 #*/
  DmaHandle.Instance = DMA_INSTANCE;

  /*##-4- Initialize the DMA stream ##########################################*/
  if (HAL_DMA_Init(&DmaHandle)== HAL_OK)
  {
		if(HAL_DMA_Start(&DmaHandle,SrcAddress,DstAddress,DataLength)== HAL_OK)
		{
			HAL_DMA_PollForTransfer(&DmaHandle, HAL_DMA_FULL_TRANSFER, 200);
		}
  }	 
	
}



//SPI
SPI_HandleTypeDef hspi3,hspi4,hspi5,hspi6;

void SPI6_GPIO_Init(void)
{
	GPIO_InitTypeDef gpio_init_structure;

	__HAL_RCC_GPIOG_CLK_ENABLE();
	
	//SPI GPIO
	//SPI6
	gpio_init_structure.Pin       = GPIO_PIN_12|GPIO_PIN_14;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Alternate = GPIO_AF5_SPI6;
  HAL_GPIO_Init(GPIOG, &gpio_init_structure);
	
	gpio_init_structure.Pin       = GPIO_PIN_13;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLDOWN;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Alternate = GPIO_AF5_SPI6;
  HAL_GPIO_Init(GPIOG, &gpio_init_structure);
	
	gpio_init_structure.Pin       = GPIO_PIN_8;         //SPI_CS
  gpio_init_structure.Mode      = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;

  HAL_GPIO_Init(GPIOG, &gpio_init_structure);	

}

void SPI3_GPIO_Init(void)	
{
	GPIO_InitTypeDef gpio_init_structure;

	__HAL_RCC_GPIOC_CLK_ENABLE();
		//SPI3
	gpio_init_structure.Pin       = GPIO_PIN_11|GPIO_PIN_12;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(GPIOC, &gpio_init_structure);
	
	gpio_init_structure.Pin       = GPIO_PIN_10;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLDOWN;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Alternate = GPIO_AF6_SPI3;
  HAL_GPIO_Init(GPIOC, &gpio_init_structure);
	
	gpio_init_structure.Pin       = GPIO_PIN_0;         //SPI_CS
  gpio_init_structure.Mode      = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;

  HAL_GPIO_Init(GPIOC, &gpio_init_structure);	
}

void SPI4_GPIO_Init(void)	
{
	GPIO_InitTypeDef gpio_init_structure;
	
	__HAL_RCC_GPIOE_CLK_ENABLE();
		//SPI3
	gpio_init_structure.Pin       = GPIO_PIN_5|GPIO_PIN_6;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Alternate = GPIO_AF5_SPI4;
  HAL_GPIO_Init(GPIOE, &gpio_init_structure);
	
	gpio_init_structure.Pin       = GPIO_PIN_2; //CLK
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLDOWN;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Alternate = GPIO_AF5_SPI4;
  HAL_GPIO_Init(GPIOE, &gpio_init_structure);
	
	gpio_init_structure.Pin       = GPIO_PIN_4;         //SPI_CS
  gpio_init_structure.Mode      = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;

  HAL_GPIO_Init(GPIOE, &gpio_init_structure);	
}

void SPI5_GPIO_Init(void)
{
	GPIO_InitTypeDef gpio_init_structure;
	
	__HAL_RCC_GPIOF_CLK_ENABLE();
	//SPI GPIO
	
	//SPI5
	gpio_init_structure.Pin       = GPIO_PIN_7 | GPIO_PIN_8| GPIO_PIN_9;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Alternate = GPIO_AF5_SPI5;
  HAL_GPIO_Init(GPIOF, &gpio_init_structure);
	
	gpio_init_structure.Pin       = GPIO_PIN_6;         //SPI_CS
  gpio_init_structure.Mode      = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOF, &gpio_init_structure);		
	
}


void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
{
	if(hspi->Instance==SPI6)
	{		
		SPI6_GPIO_Init();
		__HAL_RCC_SPI6_CLK_ENABLE(); 		
	}
	
	if(hspi->Instance==SPI5)
	{
		SPI5_GPIO_Init();
		__HAL_RCC_SPI5_CLK_ENABLE(); 
	}
	
	if(hspi->Instance==SPI3)
	{
		SPI3_GPIO_Init();
		__HAL_RCC_SPI3_CLK_ENABLE(); 
	}
	
	if(hspi->Instance==SPI4)
	{
		SPI4_GPIO_Init();
		__HAL_RCC_SPI4_CLK_ENABLE(); 
	}

}

void Sensor_SPI_Init(void)
{
	#if NK2047A
  hspi6.Instance = SPI6;
  hspi6.Init.Mode = SPI_MODE_MASTER;
  hspi6.Init.Direction = SPI_DIRECTION_2LINES;
  hspi6.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi6.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi6.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi6.Init.NSS = SPI_NSS_SOFT;
  hspi6.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi6.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi6.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi6.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi6.Init.CRCPolynomial = 7;

  if (HAL_SPI_Init(&hspi6) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }
	
	#elif NK2047B
	hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 7;

  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }
	#elif NK1092A
	hspi4.Instance = SPI4;
  hspi4.Init.Mode = SPI_MODE_MASTER;
  hspi4.Init.Direction = SPI_DIRECTION_2LINES;
  hspi4.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi4.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi4.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi4.Init.NSS = SPI_NSS_SOFT;
  hspi4.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi4.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi4.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi4.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi4.Init.CRCPolynomial = 7;

  if (HAL_SPI_Init(&hspi4) != HAL_OK)
  {
    //_Error_Handler(__FILE__, __LINE__);
  }
	#endif

}

void FlashSPIInit(void)
{
	hspi6.Instance = SPI6;
  hspi6.Init.Mode = SPI_MODE_MASTER;
  hspi6.Init.Direction = SPI_DIRECTION_2LINES;
  hspi6.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi6.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi6.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi6.Init.NSS = SPI_NSS_SOFT;
  hspi6.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi6.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi6.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi6.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi6.Init.CRCPolynomial = 7;

  if (HAL_SPI_Init(&hspi6) != HAL_OK)
  {
    
  }
}


I2C_HandleTypeDef hEvalI2c1,hEvalI2c2,hEvalI2c3;

void I2C1_GPIO_Init(void)
{	
	GPIO_InitTypeDef gpio_init_structure;
	
	__HAL_RCC_GPIOB_CLK_ENABLE();
	//I2C GPIO
	
	gpio_init_structure.Pin       = GPIO_PIN_8 | GPIO_PIN_9;
  gpio_init_structure.Mode      = GPIO_MODE_AF_OD;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(GPIOB, &gpio_init_structure);
	
}

void I2C2_GPIO_Init(void)
{	
	GPIO_InitTypeDef gpio_init_structure;
	
	__HAL_RCC_GPIOH_CLK_ENABLE();
	//I2C GPIO
	
	gpio_init_structure.Pin       = GPIO_PIN_4 | GPIO_PIN_5;
  gpio_init_structure.Mode      = GPIO_MODE_AF_OD; 
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Alternate = GPIO_AF4_I2C2;
  HAL_GPIO_Init(GPIOH, &gpio_init_structure);	
}

void I2C3_GPIO_Init(void)
{	
	GPIO_InitTypeDef gpio_init_structure;
	
	__HAL_RCC_GPIOH_CLK_ENABLE();
	//I2C GPIO
	
	gpio_init_structure.Pin       = GPIO_PIN_7 | GPIO_PIN_8;
  gpio_init_structure.Mode      = GPIO_MODE_AF_OD; 
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Alternate = GPIO_AF4_I2C3;
  HAL_GPIO_Init(GPIOH, &gpio_init_structure);	
}


void Other_GPIO_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
	//other GPIO
	//INT Adjust
	__HAL_RCC_GPIOG_CLK_ENABLE(); 
	__HAL_RCC_GPIOC_CLK_ENABLE();  
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_DMA2_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull  = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	//shutter
	GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_2,GPIO_PIN_RESET);	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,GPIO_PIN_RESET);	
	
	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_6,GPIO_PIN_SET);		
	
	//LED
	GPIO_InitStruct.Pin =GPIO_PIN_8|GPIO_PIN_9; 
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_SET);	
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_SET);	
	
	//LED
	GPIO_InitStruct.Pin =GPIO_PIN_6; //tec_en
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOF,GPIO_PIN_6,GPIO_PIN_SET);	
	//MCO
	GPIO_InitStruct.Pin       = GPIO_PIN_8;
  GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP; 
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	HAL_RCC_MCOConfig(RCC_MCO1,RCC_MCO1SOURCE_PLLCLK,RCC_MCODIV_5);
	
}

//I2C
void I2C_Init(uint8_t num)
{	  

	  if(num==1)
		{			
			if(HAL_I2C_GetState(&hEvalI2c1) == HAL_I2C_STATE_RESET)
			{
				I2C1_GPIO_Init();
				__HAL_RCC_I2C1_CLK_ENABLE();		
			
				__HAL_RCC_I2C1_FORCE_RESET();		
			
				__HAL_RCC_I2C1_RELEASE_RESET();
				
				hEvalI2c1.Instance              = I2C1;
				hEvalI2c1.Init.Timing           = EVAL_I2Cx_TIMING;
				hEvalI2c1.Init.OwnAddress1      = 0x00;
				hEvalI2c1.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
				hEvalI2c1.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
				hEvalI2c1.Init.OwnAddress2      = 0x00;
				hEvalI2c1.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
				hEvalI2c1.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;
			 
				HAL_I2C_Init(&hEvalI2c1);			
			}
		}
		
		if(num==3)
		{
			if(HAL_I2C_GetState(&hEvalI2c3) == HAL_I2C_STATE_RESET)
			{
				I2C3_GPIO_Init();
				__HAL_RCC_I2C3_CLK_ENABLE();		
			
				__HAL_RCC_I2C3_FORCE_RESET();		
			
				__HAL_RCC_I2C3_RELEASE_RESET();
				
				hEvalI2c3.Instance              = I2C3;
				hEvalI2c3.Init.Timing           = EVAL_I2Cx_TIMING;
				hEvalI2c3.Init.OwnAddress1      = 0x03;
				hEvalI2c3.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
				hEvalI2c3.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
				hEvalI2c3.Init.OwnAddress2      = 0x04;
				hEvalI2c3.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
				hEvalI2c3.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;

				HAL_I2C_Init(&hEvalI2c3);			
			}
		}
		
		if(num==2)
		{
			if(HAL_I2C_GetState(&hEvalI2c2) == HAL_I2C_STATE_RESET)
			{
				I2C2_GPIO_Init();
				__HAL_RCC_I2C2_CLK_ENABLE();		
			
				__HAL_RCC_I2C2_FORCE_RESET();		
			
				__HAL_RCC_I2C2_RELEASE_RESET();
				
				hEvalI2c2.Instance              = I2C2;
				hEvalI2c2.Init.Timing           = EVAL_I2Cx_TIMING;
				hEvalI2c2.Init.OwnAddress1      = 0x01;
				hEvalI2c2.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
				hEvalI2c2.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
				hEvalI2c2.Init.OwnAddress2      = 0x02;
				hEvalI2c2.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
				hEvalI2c2.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;

				HAL_I2C_Init(&hEvalI2c2);			
			}
		}
		
}

void INT_Configuration(uint32_t Val) 
{
		uint8_t INT_Value=0;	
		uint8_t Bits_5,Bits_4,Bits_3,Bits_2,Bits_1,Bits_0;
	
		if(Val<10)
			Val=10;
		if(Val>=73)
			Val=73;
		
		INT_Value=Val-10; //VAL:10~73   INT_Value: 0~63
		
		Bits_5=(INT_Value&0x20)>>5;
		Bits_4=(INT_Value&0x10)>>4;
		Bits_3=(INT_Value&0x08)>>3;
		Bits_2=(INT_Value&0x04)>>2;
		Bits_1=(INT_Value&0x02)>>1;
		Bits_0=(INT_Value&0x01)>>0;
		
		if(Bits_5==1)
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_SET);
		}
		
		else if(Bits_5==0)
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_13,GPIO_PIN_RESET);
		}
		
	  if(Bits_4==1)
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);
		}
		
		else if(Bits_4==0)
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);
		}
		
		if(Bits_3==1)
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_SET);
		}
		
		else if(Bits_3==0)
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,GPIO_PIN_RESET);
		}
				
		if(Bits_2==1)
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_SET);
		}
		
		else if(Bits_2==0)
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_10,GPIO_PIN_RESET);
		}
		
		if(Bits_1==1)
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_SET);
		}
		
		else if(Bits_1==0)
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,GPIO_PIN_RESET);
		}
		
		if(Bits_0==1)
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,GPIO_PIN_SET);
		}
		
		else if(Bits_0==0)
		{
			HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,GPIO_PIN_RESET);
		}
		
		BSP_CAMERA_Stop();
		HAL_Delay(10);
		
		BSP_CAMERA_Init();	

    BSP_CAMERA_ContinuousStart((uint8_t *)Image_Parameter120.temp_xdata);
}


uint8_t IR_CAMERA_Init(uint32_t Resolution)
{
	
  //DCMI_HandleTypeDef  phdcmi;
  uint8_t status = CAMERA_ERROR;
	static DMA_HandleTypeDef hdma_eval;
  GPIO_InitTypeDef gpio_init_structure;
  
	__HAL_RCC_DCMI_CLK_ENABLE();

  /* Enable DMA2 clock */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* Enable GPIO clocks */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOI_CLK_ENABLE();
	
  /*** Configures the DCMI to interface with the camera module ***/
  /* DCMI configuration */
  hDcmiEval.Init.CaptureRate      = DCMI_CR_ALL_FRAME;
  hDcmiEval.Init.HSPolarity       = DCMI_HSPOLARITY_LOW;
  hDcmiEval.Init.SynchroMode      = DCMI_SYNCHRO_HARDWARE;
  hDcmiEval.Init.VSPolarity       = DCMI_VSPOLARITY_LOW;
  hDcmiEval.Init.ExtendedDataMode = DCMI_EXTEND_DATA_8B;
  hDcmiEval.Init.PCKPolarity      = DCMI_PCKPOLARITY_RISING;
	
  hDcmiEval.Instance              = DCMI;
  
	HAL_DCMI_Init(&hDcmiEval);		
	
	/*** Configure the GPIO ***/
  /* Configure DCMI GPIO as alternate function */
  gpio_init_structure.Pin       = GPIO_PIN_9 | GPIO_PIN_10| GPIO_PIN_11| GPIO_PIN_12| GPIO_PIN_14;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOH, &gpio_init_structure);

  gpio_init_structure.Pin       = GPIO_PIN_4 | GPIO_PIN_5| GPIO_PIN_6| GPIO_PIN_7;
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOI, &gpio_init_structure);

  gpio_init_structure.Pin       = GPIO_PIN_4 | GPIO_PIN_6;                                  
  gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull      = GPIO_PULLUP;
  gpio_init_structure.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  gpio_init_structure.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOA, &gpio_init_structure);	


  /*** Configure the DMA ***/
  /* Set the parameters to be configured */
  hdma_eval.Init.Channel             = DMA_CHANNEL_1;
  hdma_eval.Init.Direction           = DMA_PERIPH_TO_MEMORY;
  hdma_eval.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_eval.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_eval.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_eval.Init.MemDataAlignment    = DMA_PDATAALIGN_BYTE;
  hdma_eval.Init.Mode                = DMA_CIRCULAR;
  hdma_eval.Init.Priority            = DMA_PRIORITY_HIGH;
  hdma_eval.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
  hdma_eval.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
  hdma_eval.Init.MemBurst            = DMA_MBURST_SINGLE;
  hdma_eval.Init.PeriphBurst         = DMA_PBURST_SINGLE;

  hdma_eval.Instance = DMA2_Stream1;

  /* Associate the initialized DMA handle to the DCMI handle */
  __HAL_LINKDMA(&hDcmiEval, DMA_Handle, hdma_eval);

  /*** Configure the NVIC for DCMI and DMA ***/
  /* NVIC configuration for DCMI transfer complete interrupt */
  HAL_NVIC_SetPriority(DCMI_IRQn, 0x01, 0);
  HAL_NVIC_EnableIRQ(DCMI_IRQn);

  /* NVIC configuration for DMA2D transfer complete interrupt */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0x01, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

  /* Configure the DMA stream */
  HAL_DMA_Init(hDcmiEval.DMA_Handle);	

  status =CAMERA_OK; 

  return status;
}


void Board_Init(void)
{
	HAL_Init();
	SystemClock_Config(); //时钟初始化
	
	USB_Init();	 //USB初始化
	
	Image_Parameter120.X_Data=(uint8_t*)malloc(COLUMN*(ROW+2)*2); //分配DMA接受缓冲器
	memset((void*)Image_Parameter120.X_Data,0x00,COLUMN*(ROW+2)*2);
	
	Image_Parameter120.temp_xdata=(uint8_t*)malloc(COLUMN*(ROW+2)*2); //分配用于存储模组原始值的数据
	memset((void*)Image_Parameter120.temp_xdata,0x00,COLUMN*(ROW+2)*2);
	
  	MemoryAlloc(); //sensor处理所需空间 保证堆空间160KByte以上
	
	Other_GPIO_Init(); //板上普通GPIO口初始化
	
	I2C_Init(2); 
	I2C_Init(3); 
	
	FlashSPIInit();	
	
	Sensor_SPI_Init(); //Sensor 初始化
	
	Shutter_On();		
	HAL_Delay(5);
	Shutter_Stop();
	
	BSP_CAMERA_Init(); //ok
	
	BSP_CAMERA_ContinuousStart(Image_Parameter120.temp_xdata);
}
