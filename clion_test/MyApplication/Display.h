#ifndef __Display__
#define __Display__

//宏定义
#include "MyApplication.h"

////定义枚举类型

//显示模式
typedef enum
{
	Disp_Mode_GRID4_SEG10  = 0x00,
	Disp_Mode_GRID5_SEG9   = 0x01,
	Disp_Mode_GRID6_SEG8   = 0x02,
} Disp_Mode_t;

//写数据地址模式
typedef enum
{
	Write_Data_Addr_Fix      = 0x44,
	Write_Data_Addr_Auto_Add = 0x40,
} Write_Data_Addr_Mode_t;

//辉度等级
typedef enum
{
	Brightness_level_0  	= 0x80,
	Brightness_level_1  	= 0x88,
	Brightness_level_2  	= 0x89,
	Brightness_level_3  	= 0x8A,
	Brightness_level_4  	= 0x8B,
	Brightness_level_5  	= 0x8C,
	Brightness_level_6  	= 0x8D,
	Brightness_level_7  	= 0x8E,
	Brightness_level_8  	= 0x8F,
} Brightness_level_t;

//显示寄出去地址
typedef enum
{
	Disp_SFR_Addr_Num   = (uint8_t)12,
	
	Disp_SFR_Addr_00H  	= 0xC0,
	Disp_SFR_Addr_01H  	= 0xC1,
	Disp_SFR_Addr_02H  	= 0xC2,
	Disp_SFR_Addr_03H  	= 0xC3,
	Disp_SFR_Addr_04H  	= 0xC4,
	Disp_SFR_Addr_05H  	= 0xC5,
	Disp_SFR_Addr_06H  	= 0xC6,
	Disp_SFR_Addr_07H  	= 0xC7,
	Disp_SFR_Addr_08H  	= 0xC8,
	Disp_SFR_Addr_09H  	= 0xC9,
	Disp_SFR_Addr_0AH  	= 0xCA,
	Disp_SFR_Addr_0BH  	= 0xCB,
} Disp_SFR_Addr_t;

//数码管编号
typedef enum
{
	Disp_NUM_1  	= Disp_SFR_Addr_0AH,   //最右边
	Disp_NUM_2  	= Disp_SFR_Addr_08H,
	Disp_NUM_3  	= Disp_SFR_Addr_06H,
	Disp_NUM_4  	= Disp_SFR_Addr_04H,
	Disp_NUM_5  	= Disp_SFR_Addr_02H,
	Disp_NUM_6  	= Disp_SFR_Addr_00H,   //最左边
} Disp_NUM_t;

//数码管小数点状态
typedef enum
{
	Disp_DP_OFF  = 0x01,
	Disp_DP_ON   = 0x02,
} Disp_DP_Status_t;

//定义结构体类型
typedef struct
{
	Brightness_level_t  Brightness;
	
	void (*TM1620_Init)(void);                              //TM1620初始化
	void (*Disp_HEX)(Disp_NUM_t,uint8_t,Disp_DP_Status_t);  //数码管显示十六进制
	void (*Disp_Other)(Disp_NUM_t,uint8_t,Disp_DP_Status_t);//数码管显示其他
} Display_t;

/* extern variables-----------------------------------------------------------*/
extern Display_t Display;

/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
