#ifndef __Unipolar_Step_Motor_H__
#define __Unipolar_Step_Motor_H__

#include "MyApplication.h"

//宏定义
#define	SET_Motor_A	HAL_GPIO_WritePin(Step_Motor_A_GPIO_Port,Step_Motor_A_Pin,GPIO_PIN_SET);
#define	CLR_Motor_A	HAL_GPIO_WritePin(Step_Motor_A_GPIO_Port,Step_Motor_A_Pin,GPIO_PIN_RESET);

#define	SET_Motor_B	HAL_GPIO_WritePin(Step_Motor_B_GPIO_Port,Step_Motor_B_Pin,GPIO_PIN_SET);
#define	CLR_Motor_B	HAL_GPIO_WritePin(Step_Motor_B_GPIO_Port,Step_Motor_B_Pin,GPIO_PIN_RESET);

#define	SET_Motor_C	HAL_GPIO_WritePin(Step_Motor_C_GPIO_Port,Step_Motor_C_Pin,GPIO_PIN_SET);
#define	CLR_Motor_C	HAL_GPIO_WritePin(Step_Motor_C_GPIO_Port,Step_Motor_C_Pin,GPIO_PIN_RESET);

#define	SET_Motor_D	HAL_GPIO_WritePin(Step_Motor_D_GPIO_Port,Step_Motor_D_Pin,GPIO_PIN_SET);
#define	CLR_Motor_D	HAL_GPIO_WritePin(Step_Motor_D_GPIO_Port,Step_Motor_D_Pin,GPIO_PIN_RESET);

#define Circle_Set_Value (uint8_t)8 //转动的圈数

//定义枚举类型
//状态
typedef enum
{
	Start_State  	= (uint8_t)0,
	Stop_State  	= (uint8_t)1,
}Status_t;
//方向
typedef enum
{
	Forward_State = (uint8_t)0,
	Reverse_State = (uint8_t)1,
}Direction_t;
//速度等级
typedef enum
{
	Speed_1  = (uint8_t)100, //100*0.1ms 
	Speed_2  = (uint8_t)90,
	Speed_3  = (uint8_t)80,
	Speed_4  = (uint8_t)70,
	Speed_5  = (uint8_t)60,       //6ms
	Speed_6  = (uint8_t)50, //10KHz    50*0.1ms = 5ms
	Speed_7  = (uint8_t)40,
	Speed_8  = (uint8_t)30,
	Speed_9  = (uint8_t)20, //2ms
}Speed_t;
//加减速
typedef enum
{
	Speed_up    = (uint8_t)0, //加速
	Speed_down  = (uint8_t)1, //减速
}Speed_Change_t;

//驱动模式
typedef enum
{
	Drive_Mode_Single_4_Beats    = (uint8_t)0, //单四拍 - 步距角为5.625/32(型号28BYJ-48)，驱动力度最小
	Drive_Mode_Double_4_Beats    = (uint8_t)1, //双四拍 - 步距角为5.625/32(型号28BYJ-48)，驱动力度最大
	Drive_Mode_8_Beats           = (uint8_t)2, //八拍   - 步距角为5.625/64(型号28BYJ-48)，驱动力度居中
}Drive_Mode_t;


//定义结构体类型
typedef struct
{
  uint8_t Status;    //步进电机状态
	uint8_t Direction; //步进电机方向
	uint8_t Speed;     //步进电机速度
	uint8_t Circle;    //步进电机转动圈数
	Drive_Mode_t Drive_Mode;   //步进电机驱动模式
	uint16_t Pulse_Cnt;        //步进电机脉冲计数
	uint16_t One_Circle_Pulse; //步进电机转动一圈的脉冲数
	
	void (*Direction_Adjust)(void);        //步进电机方向调整
	void (*Speed_Adjust)(Speed_Change_t);  //步进电机速度调整
	void (*Step_One_Pulse)(void);          //步进电机步进一个脉冲
} Unipolar_Step_Motor_t;

/* extern variables-----------------------------------------------------------*/
extern Unipolar_Step_Motor_t  Unipolar_Step_Motor;

#endif
/********************************************************
  End Of File
********************************************************/
