

#include "main.h"
/*!< STM32F10x Standard Peripheral Library old types (maintained for legacy purpose) */
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  /*!< Read Only */
typedef const int16_t sc16;  /*!< Read Only */
typedef const int8_t sc8;   /*!< Read Only */

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef __I int32_t vsc32;  /*!< Read Only */
typedef __I int16_t vsc16;  /*!< Read Only */
typedef __I int8_t vsc8;   /*!< Read Only */

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t uc8;   /*!< Read Only */

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef __I uint32_t vuc32;  /*!< Read Only */
typedef __I uint16_t vuc16;  /*!< Read Only */
typedef __I uint8_t vuc8;   /*!< Read Only */


/*
##################################################
# 变量预处理
##################################################
*/
#ifdef __MAIN
	#define SBIT sbit
	#define EXT
	#define INIT_V1(a,b,c)
	#define INIT_V2(a,b)
#else
	#define SBIT extern bit
	#define EXT extern
	#define INIT_V1(a,b,c) a b##c
	#define INIT_V2(a,b) a##b
#endif

#define IV1 INIT_V1(; ,/,/)
#define IV2 INIT_V2(/,/)

//IV1 加分号 ; 后添加注释符 //
//IV2 添加注释符 //
//## 是连接2个字符的作用

/*
##################################################
# 配置标志位
##################################################
*/
#define TEMP_BDATA 	1	// 0=禁止,1=使能 临时位变量

#define FLAG_C_ASM	FLAG_ASM		// 选择方式

#define FLAGS_TYPE	FLAGS_1X16		// 选择类型

#define	INCX2	3		// 第2个标志间隙(与汇编对应)

#define	INCX3	5		// 第3个标志间隙(与汇编对应)


#define FLAGS_1X8		0		// 0 = 1个 8位
#define FLAGS_2X8		1		// 1 = 2个 8位
#define FLAGS_3X8		2		// 2 = 3个 8位
#define FLAGS_1X16		3		// 3 = 1个16位
#define FLAGS_1X16_1X8	4		// 4 = 1个16位加1个8位

#define FLAG_C			0		// 0 = C方式
#define	FLAG_ASM		1		// 1 = ASM方式

//RTC
#define RTC_H12_AMorPM RTC_H12_AM
#define YE		18		// 0 = 1个 8位
#define MO		8		// 1 = 2个 8位
#define DA		23		// 2 = 3个 8位
#define HO		1		// 3 = 1个16位
#define MI	  1		// 4 = 1个16位加1个8位
#define SE    1 // 0~59

//#define YE		1		// 0 = 1个 8位
//#define MO		1		// 1 = 2个 8位
//#define DA		1		// 2 = 3个 8位
//#define HO		1		// 3 = 1个16位
//#define MI	  1		// 4 = 1个16位加1个8位
//#define SE    1 // 0~59
#define WEEK  1 // 1~7
#define RTC_Format_BINorBCD  RTC_Format_BIN
#define RTC_BKP_DRX    RTC_BKP_DR0 //备份寄存器
#define RTC_BKP_DATA   0X32F2 //2018 //备份SRAM的数据 2018
/*
##################################################
# @Global Variables
##################################################
*/

#define BLIND		0x02		// 0 = 1个 8位
//#define NOBLIND 0x00		1		// 1 = 2个 8位

//------------------------------------------------
// typedef, struct, enum, union
//------------------------------------------------ 
typedef struct 
{
//	 u16 ir35;      //35度校准点
//	 u16 ir200;     //400度校准点
//	 u16 ir300;     //400度校准点	
//	 u16 ir400;     //400度校准点
	 u16 ir400[4];     //400度校准点
	 u8 cal_mode;   //线性模式
	 u8 cal_direction;//方向
	 u16 cal_REF;    //补偿基点
	 float ref1_400; //补偿幅度每度
}Ircal_Flag;

typedef struct 
{
	u8 MainMenuFlag; //主菜单标志层次级数
	u8 MainMenuIndex;//菜单项0--4标志
	u8 M1MenuIndex;//华氏摄氏
	u8 M2MenuIndex;//中心点
	u8 M3MenuIndex;//色板
	u8 M4MenuIndex;//图片号
	u8 M5MenuIndex;//设备项0--5（语言-----原厂设定）
	
	u8 M51MenuIndex;//语言（中英法）
	u8 M52MenuIndex;//时间与日期
	u8 M53MenuIndex;//激光点
	u8 M54MenuIndex;//USB
	u8 M55MenuIndex;//原厂设定
	u8 M56MenuIndex;//拍摄  =3拍照选择，=0返回
	u8 M57Emissivity;
}Menu_TypeFlag;


typedef struct
{
	u8 LauFlag;
	float Lscale;
	u8 Year;
	u8 Month;
	u8 Day;
	u8 Hour;
	u8 Minu;
	u8 TimeFlag;
	u8 Laser;
	u8 USBPC;
	u8 ResetSet;
}SetMenu;

//------------------------------------------------
// u8 Type
//------------------------------------------------

	EXT u8  keynumber;	
	EXT u16  key_delay;
  EXT u8  key_temp;
	EXT	u8  ktemp;
	EXT u8  lkey;
	EXT u8  key_off;
  EXT u8  gKeyModeFlag;

  EXT u8 dis0;
	EXT u8 cal;
  EXT u16 loop;
  EXT u16 loop_1s; 
	EXT u8 cal_loop;
  EXT u8 key7;
  EXT u8 key6;
	EXT u8 cal_p;
	EXT u16 Tem35;
	EXT u16 Tem400;
	
	EXT u8 usbflag; 
	EXT u16 menus;
	EXT u16 totpicnum;  //图片文件总数
	EXT u16 viewpicnum; //当前查看的图片号
	EXT uint8_t meun_flag[16]; //////////////////////////////
	EXT u16 file_name;
  EXT u16 picnum[4];//	
	EXT u16 keytime;  // 定时关机变量
	EXT u8 RtcKeyoff;      // 锁屏关机
	
	EXT u8 keyccd;      // 锁屏扳机
//	EXT s16 bbb;  //图片文件总数
	EXT u16 aaa; //当前查看的图片�
	
	EXT float  irtem; //IR温度
  EXT u16 max2;
	EXT u16 min2;
//	EXT u16 max[4];
	EXT s16 maxT; //最高温度
	EXT s16 minT; //最低温度
	EXT u16 lcdxmax;
	EXT u16 lcdymax;
	EXT u16 lcdxmin;
	EXT u16 lcdymin;
	
	EXT s16 xcam; //可见光x移位
	EXT s16 ycam; //Y移位
	EXT s16 xycam; //xY移位
//	EXT u8 xhtp; //红外x移位
//	EXT u8 yhtp; //Y移位
//	EXT u16 xyhtp; //xY移位	
	EXT u8 language6;
	
	EXT u16 vbat;//电池
	EXT u16 vusb;//USB
	EXT u8  poff;
	EXT u8  sd;
	EXT u8  sdflag;
	EXT u8  sdsave;
	EXT u8  bmp_save;
	EXT	u8 gTemCheckFlag;
	EXT u8 emd ;
	EXT  int16_t Gxy;	

	
	EXT u8  gradScale2;	
	EXT u8  epsilon2;	
	EXT u16 focus;
	EXT u16 focus2;
	//EXT u16 TAHTPA;
	EXT u16 uHtpa8[16];
	EXT u8  aHbit;
	EXT u8  Cbit;
//	EXT u8  ir170;
	
//EXT u16 VddBuf[8]/*VDD缓存区*/;
//EXT u16 PTAT8[8];/*PTAT缓存区*/
//EXT u8  data[258];
//EXT u8  data2[258];	
//EXT u16 eloffstack[256][16];	



