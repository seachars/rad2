#include "stm32f7xx_hal.h"
#include "cLCD.h"

static void _delay_(__IO uint32_t nCount)
	{
	HAL_Delay(nCount);
	}

static void _delay1ms_(__IO uint32_t nCount)
	{
	HAL_Delay(nCount);
	}



typedef struct
	{
		__IO uint16_t LCD_REG;
		__IO uint16_t LCD_RAM;
	} LCD_TypeDef;

#define LCD_BASE           ((uint32_t)(0x60000000 | 0x0C000000))
#define LCD                ((LCD_TypeDef *) LCD_BASE)
#define MAX_POLY_CORNERS   200
	
u16 DeviceCode;

void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{
  /* Write 16-bit Index, then Write Reg */
  LCD->LCD_REG = LCD_Reg;
  /* Write 16-bit Reg */
  LCD->LCD_RAM = LCD_RegValue;
}

void wr_reg(uint8_t LCD_Reg, uint16_t LCD_RegValue)
{
  /* Write 16-bit Index, then Write Reg */
  LCD->LCD_REG = LCD_Reg;
  /* Write 16-bit Reg */
  LCD->LCD_RAM = LCD_RegValue;
}

///////////////////////ST7789//////////////////////////
void LCD_write_command(__IO uint16_t i)
{
	  i=i;
      LCD->LCD_REG=i;
}

void LCD_write_data(__IO uint16_t i)
{
	 i=i;
     LCD->LCD_RAM=i;
}





unsigned short LCD_read_data(void)
{
	 unsigned short temp;
	  LCD->LCD_REG=0x2e;
	  temp= LCD->LCD_RAM;
	  temp= LCD->LCD_RAM;
    return  temp;
}





//设置刷屏模式
void LCD_Mode(u8 mode)
{
	LCD_write_command(0x0036);
	switch(mode)//常用4(横屏)和7(竖屏)
	{
		case 1:LCD_write_data(0x0000);;;break;//向左向上:←↖
		case 2:LCD_write_data(0x0020);;;break;//向上向左:↑↖
		case 3:LCD_write_data(0x0040);;;break;//向右向上:→↗
		case 4:LCD_write_data(0x0060);;;break;//向上向右:↑↗
		case 5:LCD_write_data(0x0080);;;break;//向左向下:←↙
		case 6:LCD_write_data(0x00a0);;;break;//向下向左:↓↙
		case 7:LCD_write_data(0x00c0);;;break;//向右向下:→↘
		case 8:LCD_write_data(0x00e0);;;break;//向下向右:↓↘	
	}
}



void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)//光标
	{
/////////ST7789///////////
	
		LCD_write_command(0x2A);	
  	LCD_write_data(Xpos>>8); // 列
		LCD_write_data(Xpos%256); // 列
		LCD_write_data(1); // 列
		LCD_write_data(0x3f); // 列

		
		LCD_write_command(0x2B);	//Row Address Set -320max	
  	LCD_write_data(Ypos>>8); // 列
		LCD_write_data(Ypos%256); // 列
		LCD_write_data(0); // 列
		LCD_write_data(239); // 列
		//LCD_write_command(0x2C);	//0x2cWrite Memory Start			
	}




void LCD_SetPoint(u16 x,u16 y,u16 point)
	{
  if ( (x>320)||(y>240) ) return;
  LCD_SetCursor(x,y);

  LCD->LCD_RAM = point;//LCD_WriteRAM(point);	
	}


void delay_(__IO uint32_t nCount)
	{
	__IO uint32_t index = 0; 
	for(index = (1 * nCount); index != 0; index--)
		{
		}
	}
	

//开始写GRAM
void LCD_WriteRAM_Prepare(void)
{
 	LCD->LCD_REG=0x2c;	  
}


void LCD_Clear(u32 color)
{
	u32 index=0;      
	u32 totalpoint=320; 
	totalpoint*=240; 			//得到总点数
	LCD_SetCursor(0x00,0x0000);			//设置光标位置 
	LCD_WriteRAM_Prepare();     		//开始写入GRAM	 	  
	for(index=0;index<totalpoint;index++)
	{
		LCD->LCD_RAM=color;	
	} 
} 


///////////////////////ST7789END///////////////////////




void LCD_Init(void)
	{ 
	__IO uint32_t lcdid = 0;
  
/* Configure the LCD Control pins --------------------------------------------*/
 // LCD_CtrlLinesConfig();
/* Configure the FSMC Parallel interface -------------------------------------*/
 //LCD_FSMCConfig();
	 //bbb = read_data(); 	
	/*	
	RSTTFT_H;
	_delay_(80);	
	RSTTFT_L;
	_delay_(120);	;
	RSTTFT_H;*/
	  _delay_(120);	
	  LCD_write_command(0x11);
	  _delay_(50); // delay 50 ms 
		  
	  LCD_write_command(0xb2);
	  LCD_write_data(0x0c);
	  LCD_write_data(0x0c);
	  LCD_write_data(0x00);
	  LCD_write_data(0x33);
	  LCD_write_data(0x33);
	  LCD_write_command(0xb7);//门限
	  LCD_write_data(0x35);
	  //---------------------------------ST7789S Power setting--------------------------------------//
	  LCD_write_command(0xbb);//Power control	调 VCOM
	  LCD_write_data(0x35);
	  LCD_write_command(0xc0);
	  LCD_write_data(0x2c);
	  LCD_write_command(0xc2);
	  LCD_write_data(0x01);
	  LCD_write_command(0xc3);
	  LCD_write_data(0x0b);
	  LCD_write_command(0xc4);
	  LCD_write_data(0x20);
	  LCD_write_command(0xc6);//Power control  调频率
	  LCD_write_data(0x0f);
	  LCD_write_command(0xca);
	  LCD_write_data(0x0f);
	  LCD_write_command(0xc8);
	  LCD_write_data(0x08);
	  LCD_write_command(0x55);
	  LCD_write_data(0x90);
	  LCD_write_command(0xd0);
	  LCD_write_data(0xa4);
	  LCD_write_data(0xa1);
	  //--------------------------------ST7789S gamma setting---------------------------------------//
	  LCD_write_command(0xe0);
	  LCD_write_data(0xd0);
	  LCD_write_data(0x00);
	  LCD_write_data(0x02);
	  LCD_write_data(0x07);
	  LCD_write_data(0x0b);
	  LCD_write_data(0x1a);
	  LCD_write_data(0x31);
	  LCD_write_data(0x54);
	  LCD_write_data(0x40);
	  LCD_write_data(0x29);
	  LCD_write_data(0x12);
	  LCD_write_data(0x12);
	  LCD_write_data(0x12);
	  LCD_write_data(0x17);
	  LCD_write_command(0xe1);
	  LCD_write_data(0xd0);
	  LCD_write_data(0x00);
	  LCD_write_data(0x02);
	  LCD_write_data(0x07);
	  LCD_write_data(0x05);
	  LCD_write_data(0x25);
	  LCD_write_data(0x2d);
	  LCD_write_data(0x44);
	  LCD_write_data(0x45);
	  LCD_write_data(0x1c);
	  LCD_write_data(0x18);
	  LCD_write_data(0x16);
	  LCD_write_data(0x1c);
	  LCD_write_data(0x1d);
	
	  LCD_write_command(0x003a);	  //LCD色彩位设置
	LCD_write_data(0x0055); 	  //16BIT
	
	  LCD_write_command(0x0020); //?
	  
	  LCD_Mode(4);//1-8扫描模?6 4  
	
	  LCD_write_command(0x0029);	  

	
  
	}


#if 1

void test_color(uint32_t r,uint32_t g,uint32_t b)
{
	uint16_t  *p;
	int i;
	uint16_t  color;
	p = (uint16_t  *)LCD_COMMAND_ADDR;
	*p=LCD_COMMAND_COMMENT;
	p = (uint16_t  *)LCD_DATA_ADDR;
	
	color=((r>>3)<<11)|((g>>2)<<5)|((b>>3)<<0);

	for(i=0;i<LCD_PIXELs;i++)
		{
			*p=color;
		}
	
}

int start_x_col=1;

void test_colorBar(void)
{
	uint16_t  *p;
	int i,j;
	uint16_t  color;
	uint32_t r=0,g=0,b=0;
	int step;
	int speed;
	int x_col;
	p = (uint16_t  *)LCD_COMMAND_ADDR;
	*p=LCD_COMMAND_COMMENT;
	p = (uint16_t  *)LCD_DATA_ADDR;
	
	step=1;
	speed=4;

	for(i=0;i<LCD_HEIGHT;i++)
		{
		for (j=0;j<LCD_WIDTH;j++)
			{
			x_col=(j*speed);	
			if ((x_col>=0)&(x_col<256))
				{
					r=x_col;
					g=0;
					b=0;
				}
			
			else if ((x_col>=255)&(x_col<512))
				{
					r=0;
					g=x_col;
					b=0;
				}

			else if ((x_col>=512)&(x_col<768))
				{
					r=0;
					g=0;
					b=x_col;
				}
			else
				{
					r=255;
					g=255;
					b=255;
				}
				
			color=((r>>3)<<11)|((g>>2)<<5)|((b>>3)<<0);
			*p=color;

			}

		}
	
}


uint16_t bitcolor=0;

void test_moveBar(void)
{
	__IO uint16_t  *p;
	int y,x;
	uint16_t  color;
	uint32_t r=0,g=0,b=0;

	int speed;

	p = (uint16_t  *)LCD_COMMAND_ADDR;
	*p=LCD_COMMAND_COMMENT;
	LCD_SetCursor(0,0);
	p = (uint16_t  *)LCD_DATA_ADDR;
	//_delay_(10);
	
	speed=1;
	start_x_col=start_x_col<<1;
	if (start_x_col==0x8000) start_x_col=1;
	
	if (bitcolor<15)
		{
				bitcolor++;
		}
	else
		{
				bitcolor=0;
		}
		
	/*
	for(y=0;y<20;y++)
		{
		for (x=0;x<LCD_WIDTH;x++)
			{
			
			if ((y>start_x_col)&(y<(start_x_col+100)))	
				{
					
					r=255;
					g=0;
					b=0;
					//*p=x;
					color=0x5f;
				}

			else 
				{
					//*p=y;
					
					r=1;
					g=0;
					b=0;
					//color=(1<<bitcolor);;
					color=0x23;
				}
			
			color=((r>>3)<<11)|((g>>2)<<5)|(b>>3);
			//color=0x23;
			LCD_SetPoint(x, y, color);
			//*p=color;

			}

		}*/
	LCD_Clear(start_x_col);	
	//LCD_write_command(0x0020);		
	//_delay1ms_(50000);
}
#endif

