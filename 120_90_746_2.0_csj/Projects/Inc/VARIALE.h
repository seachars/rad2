

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
# ±äÁ¿Ô¤´¦Àí
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

//IV1 ¼Ó·ÖºÅ ; ºóÌí¼Ó×¢ÊÍ·û //
//IV2 Ìí¼Ó×¢ÊÍ·û //
//## ÊÇÁ¬½Ó2¸ö×Ö·ûµÄ×÷ÓÃ

/*
##################################################
# ÅäÖÃ±êÖ¾Î»
##################################################
*/
#define TEMP_BDATA 	1	// 0=½ûÖ¹,1=Ê¹ÄÜ ÁÙÊ±Î»±äÁ¿

#define FLAG_C_ASM	FLAG_ASM		// Ñ¡Ôñ·½Ê½

#define FLAGS_TYPE	FLAGS_1X16		// Ñ¡ÔñÀàÐÍ

#define	INCX2	3		// µÚ2¸ö±êÖ¾¼äÏ¶(Óë»ã±à¶ÔÓ¦)

#define	INCX3	5		// µÚ3¸ö±êÖ¾¼äÏ¶(Óë»ã±à¶ÔÓ¦)


#define FLAGS_1X8		0		// 0 = 1¸ö 8Î»
#define FLAGS_2X8		1		// 1 = 2¸ö 8Î»
#define FLAGS_3X8		2		// 2 = 3¸ö 8Î»
#define FLAGS_1X16		3		// 3 = 1¸ö16Î»
#define FLAGS_1X16_1X8	4		// 4 = 1¸ö16Î»¼Ó1¸ö8Î»

#define FLAG_C			0		// 0 = C·½Ê½
#define	FLAG_ASM		1		// 1 = ASM·½Ê½

//RTC
#define RTC_H12_AMorPM RTC_H12_AM
#define YE		18		// 0 = 1¸ö 8Î»
#define MO		8		// 1 = 2¸ö 8Î»
#define DA		23		// 2 = 3¸ö 8Î»
#define HO		1		// 3 = 1¸ö16Î»
#define MI	  1		// 4 = 1¸ö16Î»¼Ó1¸ö8Î»
#define SE    1 // 0~59

//#define YE		1		// 0 = 1¸ö 8Î»
//#define MO		1		// 1 = 2¸ö 8Î»
//#define DA		1		// 2 = 3¸ö 8Î»
//#define HO		1		// 3 = 1¸ö16Î»
//#define MI	  1		// 4 = 1¸ö16Î»¼Ó1¸ö8Î»
//#define SE    1 // 0~59
#define WEEK  1 // 1~7
#define RTC_Format_BINorBCD  RTC_Format_BIN
#define RTC_BKP_DRX    RTC_BKP_DR0 //±¸·Ý¼Ä´æÆ÷
#define RTC_BKP_DATA   0X32F2 //2018 //±¸·ÝSRAMµÄÊý¾Ý 2018
/*
##################################################
# @Global Variables
##################################################
*/

#define BLIND		0x02		// 0 = 1¸ö 8Î»
//#define NOBLIND 0x00		1		// 1 = 2¸ö 8Î»

//------------------------------------------------
// typedef, struct, enum, union
//------------------------------------------------ 
typedef struct 
{
//	 u16 ir35;      //35¶ÈÐ£×¼µã
//	 u16 ir200;     //400¶ÈÐ£×¼µã
//	 u16 ir300;     //400¶ÈÐ£×¼µã	
//	 u16 ir400;     //400¶ÈÐ£×¼µã
	 u16 ir400[4];     //400¶ÈÐ£×¼µã
	 u8 cal_mode;   //ÏßÐÔÄ£Ê½
	 u8 cal_direction;//·½Ïò
	 u16 cal_REF;    //²¹³¥»ùµã
	 float ref1_400; //²¹³¥·ù¶ÈÃ¿¶È
}Ircal_Flag;

typedef struct 
{
	u8 MainMenuFlag; //Ö÷²Ëµ¥±êÖ¾²ã´Î¼¶Êý
	u8 MainMenuIndex;//²Ëµ¥Ïî0--4±êÖ¾
	u8 M1MenuIndex;//»ªÊÏÉãÊÏ
	u8 M2MenuIndex;//ÖÐÐÄµã
	u8 M3MenuIndex;//É«°å
	u8 M4MenuIndex;//Í¼Æ¬ºÅ
	u8 M5MenuIndex;//Éè±¸Ïî0--5£¨ÓïÑÔ-----Ô­³§Éè¶¨£©
	
	u8 M51MenuIndex;//ÓïÑÔ£¨ÖÐÓ¢·¨£©
	u8 M52MenuIndex;//Ê±¼äÓëÈÕÆÚ
	u8 M53MenuIndex;//¼¤¹âµã
	u8 M54MenuIndex;//USB
	u8 M55MenuIndex;//Ô­³§Éè¶¨
	u8 M56MenuIndex;//ÅÄÉã  =3ÅÄÕÕÑ¡Ôñ£¬=0·µ»Ø
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
	EXT u16 totpicnum;  //Í¼Æ¬ÎÄ¼þ×ÜÊý
	EXT u16 viewpicnum; //µ±Ç°²é¿´µÄÍ¼Æ¬ºÅ
	EXT uint8_t meun_flag[16]; //////////////////////////////
	EXT u16 file_name;
  EXT u16 picnum[4];//	
	EXT u16 keytime;  // ¶¨Ê±¹Ø»ú±äÁ¿
	EXT u8 RtcKeyoff;      // ËøÆÁ¹Ø»ú
	
	EXT u8 keyccd;      // ËøÆÁ°â»ú
//	EXT s16 bbb;  //Í¼Æ¬ÎÄ¼þ×ÜÊý
	EXT u16 aaa; //µ±Ç°²é¿´µÄÍ¼Æ¬º
	
	EXT float  irtem; //IRÎÂ¶È
  EXT u16 max2;
	EXT u16 min2;
//	EXT u16 max[4];
	EXT s16 maxT; //×î¸ßÎÂ¶È
	EXT s16 minT; //×îµÍÎÂ¶È
	EXT u16 lcdxmax;
	EXT u16 lcdymax;
	EXT u16 lcdxmin;
	EXT u16 lcdymin;
	
	EXT s16 xcam; //¿É¼û¹âxÒÆÎ»
	EXT s16 ycam; //YÒÆÎ»
	EXT s16 xycam; //xYÒÆÎ»
//	EXT u8 xhtp; //ºìÍâxÒÆÎ»
//	EXT u8 yhtp; //YÒÆÎ»
//	EXT u16 xyhtp; //xYÒÆÎ»	
	EXT u8 language6;
	
	EXT u16 vbat;//µç³Ø
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
	
//EXT u16 VddBuf[8]/*VDD»º´æÇø*/;
//EXT u16 PTAT8[8];/*PTAT»º´æÇø*/
//EXT u8  data[258];
//EXT u8  data2[258];	
//EXT u16 eloffstack[256][16];	



