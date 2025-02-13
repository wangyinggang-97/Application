/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/
//TM1620����ͨѶ��
#define	SET_STB		HAL_GPIO_WritePin(TM1620_STB_GPIO_Port,TM1620_STB_Pin,GPIO_PIN_SET)
#define	CLR_STB		HAL_GPIO_WritePin(TM1620_STB_GPIO_Port,TM1620_STB_Pin,GPIO_PIN_RESET)

#define	SET_DIN		HAL_GPIO_WritePin(TM1620_DIN_GPIO_Port,TM1620_DIN_Pin,GPIO_PIN_SET)
#define	CLR_DIN		HAL_GPIO_WritePin(TM1620_DIN_GPIO_Port,TM1620_DIN_Pin,GPIO_PIN_RESET)

#define	SET_CLK		HAL_GPIO_WritePin(TM1620_CLK_GPIO_Port,TM1620_CLK_Pin,GPIO_PIN_SET)
#define	CLR_CLK		HAL_GPIO_WritePin(TM1620_CLK_GPIO_Port,TM1620_CLK_Pin,GPIO_PIN_RESET)


/* Private variables----------------------------------------------------------*/
uint8_t Disp_Decode[16]    = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};  //��������� 0 - F

/* Private function prototypes------------------------------------------------*/
static void TM1620_Write_Byte(uint8_t);                      //TM1620д���ֽ�

static void TM1620_Init(void);                               //TM1620��ʼ��
static void Disp_HEX(Disp_NUM_t,uint8_t,Disp_DP_Status_t);   //�������ʾʮ������
static void Disp_Other(Disp_NUM_t,uint8_t,Disp_DP_Status_t); //�������ʾ����

/* Public variables-----------------------------------------------------------*/
Display_t Display = 
{
	Brightness_level_3,
	
	TM1620_Init,
	Disp_HEX,
	Disp_Other
};

/*
	* @name   TM1620_Write_Byte
	* @brief  TM1620д���ֽ�
	* @param  dat -> ��д������
	* @retval None      
*/
static void TM1620_Write_Byte(uint8_t dat) 
{
	uint8_t i = 0;

	
	//�ο������ֲ��ʱ��ͼ
	CLR_STB;
	
	for(i=0;i<8;i++)
	{
		CLR_CLK;
		//׼������λ
		if((dat & BIT0) == BIT0) //BIT0Ϊ�궨�壬ֵΪ0x01
			SET_DIN;
		else
			CLR_DIN;
		dat = dat >> 1; //��λ��׼����һ������
		//ʱ�������ط�������	
		SET_CLK;
        __NOP();
		//__nop();
	}	
}

/*
	* @name   TM1620_Init
	* @brief  TM1620��ʼ��
	* @param  None
	* @retval None      
*/
static void TM1620_Init() 
{
	uint8_t i = 0;
	
	//������ʾģʽ
	TM1620_Write_Byte(Disp_Mode_GRID6_SEG8); 
	SET_STB;  
	
  //��ַ�Զ�����
	TM1620_Write_Byte(Write_Data_Addr_Auto_Add); 
	SET_STB;
	
	//�����ʾ�Ĵ���
	TM1620_Write_Byte(Disp_SFR_Addr_00H); //�����׵�ַ

	for(i=0;i<Disp_SFR_Addr_Num;i++)
		TM1620_Write_Byte(0x00); 
  SET_STB; 

	//��ʾ
  TM1620_Write_Byte(Display.Brightness);
	SET_STB; 
}

/*
	* @name   Disp_HEX
	* @brief  �������ʾʮ������
  * @param  Disp_NUM:       ����ܱ��
            Dat��           ���� 0 - F 
            Disp_DP_Status��С������ʾ״̬
	* @retval None      
*/
static void Disp_HEX(Disp_NUM_t Disp_NUM,uint8_t Dat,Disp_DP_Status_t Disp_DP_Status) 
{
	//������Χ���
	if(Dat > 0x0F)
	{
		System.Assert_Failed();
	}
	
	//������ʾģʽ
	TM1620_Write_Byte(Disp_Mode_GRID6_SEG8); 
	SET_STB;
	
	//��ַ�̶�
	TM1620_Write_Byte(Write_Data_Addr_Fix); 
	SET_STB;
	
	//д��ַ
	TM1620_Write_Byte(Disp_NUM);
	//д����
	if(Disp_DP_Status == Disp_DP_ON)
		TM1620_Write_Byte(Disp_Decode[Dat] + 0x80);
	else
		TM1620_Write_Byte(Disp_Decode[Dat]);
	SET_STB;
	
	//��ʾ
  TM1620_Write_Byte(Display.Brightness);
	SET_STB; 
}

/*
	* @name   Disp_Other
	* @brief  �������ʾ����
  * @param  Disp_NUM:       ����ܱ��
            Dat��           ��������
            Disp_DP_Status��С������ʾ״̬
	* @retval None      
*/
static void Disp_Other(Disp_NUM_t Disp_NUM,uint8_t Dat,Disp_DP_Status_t Disp_DP_Status) 
{
	//������ʾģʽ
	TM1620_Write_Byte(Disp_Mode_GRID6_SEG8); 
	SET_STB;
	
	//��ַ�̶�
	TM1620_Write_Byte(Write_Data_Addr_Fix); 
	SET_STB;
	
	//д��ַ
	TM1620_Write_Byte(Disp_NUM);
	//д����
	if(Disp_DP_Status == Disp_DP_ON)
		TM1620_Write_Byte(Dat + 0x80);
	else
		TM1620_Write_Byte(Dat);
	SET_STB;
	
	//��ʾ
  TM1620_Write_Byte(Display.Brightness);
	SET_STB; 
}
/*************************************
  End Of File
*************************************/
