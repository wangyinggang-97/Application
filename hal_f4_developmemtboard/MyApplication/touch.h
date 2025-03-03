#ifndef __TOUCH_H__
#define __TOUCH_H__

#include "MyApplication.h"

//CS管脚控制
#define  	CLR_SPI_Touch_CS	 HAL_GPIO_WritePin(SPI_Touch_CS_GPIO_Port,SPI_Touch_CS_Pin,GPIO_PIN_RESET)
#define  	SET_SPI_Touch_CS	 HAL_GPIO_WritePin(SPI_Touch_CS_GPIO_Port,SPI_Touch_CS_Pin,GPIO_PIN_SET)

//XT2046读X轴与Y轴的命令
#define 	Touch_X_CMD        0xD0  //读取X轴命令
#define 	Touch_Y_CMD        0x90  //读取Y轴命令
//说明：通过调整Touch_READ_TIMES与Touch_Error，可以调整灵敏度与准确性
//      数字越小，灵敏度越高，但准确性越差，按实际需要调整。
#define   Touch_READ_TIMES   10    //一次读取触摸值的次数
#define   Touch_Error        20    //误差
//X轴与Y轴坐标边界设定
#define   Touch_X_MAX        3800  //X轴最大值
#define   Touch_X_MIN        100   //X轴最小值
#define   Touch_Y_MAX        3800  //Y轴最大值
#define   Touch_Y_MIN        100   //Y轴最小值

#define   Touch_Calibrate_Para_Addr   0
#define   Touch_Calibrate_OK         'Y'
#define  	Dummy_Byte                  0xFF  //假数据

//定义枚举类型

//定义结构体类型
typedef struct
{
    uint8_t Calibrate_Flag; //校准标志位
    uint8_t xOffset;     //X轴偏移量
    uint8_t yOffset;     //Y轴偏移量
    float   xFactor;     //X轴比例因子
    float   yFactor;     //Y轴比例因子
} Touch_Calibrate_Para_t;

typedef struct
{
    uint8_t Touch_Flag;
    uint8_t Force_Calibrate_Flag;

    uint16_t ADC_X; //ADC转换X坐标值
    uint16_t ADC_Y; //ADC转换Y坐标值
    uint16_t LCD_X; //LCD转换X坐标值
    uint16_t LCD_Y; //LCD转换Y坐标值

    LCD_Color_t Color_PEN; //画笔颜色

    void (*Palette_Init)(void);                               //调色板初始化
    void (*Palette_DrawPoint)(uint16_t,uint16_t,LCD_Color_t); //绘图区域画点
    uint8_t (*Read_ADC_XY)(uint16_t *, uint16_t *);           //读触摸IC的XY坐标值
    uint8_t (*Calibrate)(void);                               //触摸屏校准
    uint8_t (*Scan)(void);                                    //触摸屏扫描
} Touch_t;

/* extern variables-----------------------------------------------------------*/
extern Touch_t Touch;
extern Touch_Calibrate_Para_t Touch_Calibrate_Para;

#endif
/********************************************************
  End Of File
********************************************************/
