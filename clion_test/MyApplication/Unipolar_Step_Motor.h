#ifndef __Unipolar_Step_Motor_H__
#define __Unipolar_Step_Motor_H__

#include "MyApplication.h"

//�궨��
#define	SET_Motor_A	HAL_GPIO_WritePin(Step_Motor_A_GPIO_Port,Step_Motor_A_Pin,GPIO_PIN_SET);
#define	CLR_Motor_A	HAL_GPIO_WritePin(Step_Motor_A_GPIO_Port,Step_Motor_A_Pin,GPIO_PIN_RESET);

#define	SET_Motor_B	HAL_GPIO_WritePin(Step_Motor_B_GPIO_Port,Step_Motor_B_Pin,GPIO_PIN_SET);
#define	CLR_Motor_B	HAL_GPIO_WritePin(Step_Motor_B_GPIO_Port,Step_Motor_B_Pin,GPIO_PIN_RESET);

#define	SET_Motor_C	HAL_GPIO_WritePin(Step_Motor_C_GPIO_Port,Step_Motor_C_Pin,GPIO_PIN_SET);
#define	CLR_Motor_C	HAL_GPIO_WritePin(Step_Motor_C_GPIO_Port,Step_Motor_C_Pin,GPIO_PIN_RESET);

#define	SET_Motor_D	HAL_GPIO_WritePin(Step_Motor_D_GPIO_Port,Step_Motor_D_Pin,GPIO_PIN_SET);
#define	CLR_Motor_D	HAL_GPIO_WritePin(Step_Motor_D_GPIO_Port,Step_Motor_D_Pin,GPIO_PIN_RESET);

#define Circle_Set_Value (uint8_t)8 //ת����Ȧ��

//����ö������
//״̬
typedef enum
{
	Start_State  	= (uint8_t)0,
	Stop_State  	= (uint8_t)1,
}Status_t;
//����
typedef enum
{
	Forward_State = (uint8_t)0,
	Reverse_State = (uint8_t)1,
}Direction_t;
//�ٶȵȼ�
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
//�Ӽ���
typedef enum
{
	Speed_up    = (uint8_t)0, //����
	Speed_down  = (uint8_t)1, //����
}Speed_Change_t;

//����ģʽ
typedef enum
{
	Drive_Mode_Single_4_Beats    = (uint8_t)0, //������ - �����Ϊ5.625/32(�ͺ�28BYJ-48)������������С
	Drive_Mode_Double_4_Beats    = (uint8_t)1, //˫���� - �����Ϊ5.625/32(�ͺ�28BYJ-48)�������������
	Drive_Mode_8_Beats           = (uint8_t)2, //����   - �����Ϊ5.625/64(�ͺ�28BYJ-48)���������Ⱦ���
}Drive_Mode_t;


//����ṹ������
typedef struct
{
  uint8_t Status;    //�������״̬
	uint8_t Direction; //�����������
	uint8_t Speed;     //��������ٶ�
	uint8_t Circle;    //�������ת��Ȧ��
	Drive_Mode_t Drive_Mode;   //�����������ģʽ
	uint16_t Pulse_Cnt;        //��������������
	uint16_t One_Circle_Pulse; //�������ת��һȦ��������
	
	void (*Direction_Adjust)(void);        //��������������
	void (*Speed_Adjust)(Speed_Change_t);  //��������ٶȵ���
	void (*Step_One_Pulse)(void);          //�����������һ������
} Unipolar_Step_Motor_t;

/* extern variables-----------------------------------------------------------*/
extern Unipolar_Step_Motor_t  Unipolar_Step_Motor;

#endif
/********************************************************
  End Of File
********************************************************/
