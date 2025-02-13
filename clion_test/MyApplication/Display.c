/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/
//TM1620串行通讯口
#define	SET_STB		HAL_GPIO_WritePin(TM1620_STB_GPIO_Port,TM1620_STB_Pin,GPIO_PIN_SET)
#define	CLR_STB		HAL_GPIO_WritePin(TM1620_STB_GPIO_Port,TM1620_STB_Pin,GPIO_PIN_RESET)

#define	SET_DIN		HAL_GPIO_WritePin(TM1620_DIN_GPIO_Port,TM1620_DIN_Pin,GPIO_PIN_SET)
#define	CLR_DIN		HAL_GPIO_WritePin(TM1620_DIN_GPIO_Port,TM1620_DIN_Pin,GPIO_PIN_RESET)

#define	SET_CLK		HAL_GPIO_WritePin(TM1620_CLK_GPIO_Port,TM1620_CLK_Pin,GPIO_PIN_SET)
#define	CLR_CLK		HAL_GPIO_WritePin(TM1620_CLK_GPIO_Port,TM1620_CLK_Pin,GPIO_PIN_RESET)


/* Private variables----------------------------------------------------------*/
uint8_t Disp_Decode[16]    = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};  //数码管译码 0 - F

/* Private function prototypes------------------------------------------------*/
static void TM1620_Write_Byte(uint8_t);                      //TM1620写入字节

static void TM1620_Init(void);                               //TM1620初始化
static void Disp_HEX(Disp_NUM_t,uint8_t,Disp_DP_Status_t);   //数码管显示十六进制
static void Disp_Other(Disp_NUM_t,uint8_t,Disp_DP_Status_t); //数码管显示其他

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
	* @brief  TM1620写入字节
	* @param  dat -> 待写入数据
	* @retval None      
*/
static void TM1620_Write_Byte(uint8_t dat) 
{
	uint8_t i = 0;

	
	//参考数据手册的时序图
	CLR_STB;
	
	for(i=0;i<8;i++)
	{
		CLR_CLK;
		//准备数据位
		if((dat & BIT0) == BIT0) //BIT0为宏定义，值为0x01
			SET_DIN;
		else
			CLR_DIN;
		dat = dat >> 1; //移位，准备下一个比特
		//时钟上升沿发送数据	
		SET_CLK;
        __NOP();
		//__nop();
	}	
}

/*
	* @name   TM1620_Init
	* @brief  TM1620初始化
	* @param  None
	* @retval None      
*/
static void TM1620_Init() 
{
	uint8_t i = 0;
	
	//设置显示模式
	TM1620_Write_Byte(Disp_Mode_GRID6_SEG8); 
	SET_STB;  
	
  //地址自动增加
	TM1620_Write_Byte(Write_Data_Addr_Auto_Add); 
	SET_STB;
	
	//清除显示寄存器
	TM1620_Write_Byte(Disp_SFR_Addr_00H); //设置首地址

	for(i=0;i<Disp_SFR_Addr_Num;i++)
		TM1620_Write_Byte(0x00); 
  SET_STB; 

	//显示
  TM1620_Write_Byte(Display.Brightness);
	SET_STB; 
}

/*
	* @name   Disp_HEX
	* @brief  数码管显示十六进制
  * @param  Disp_NUM:       数码管编号
            Dat：           数据 0 - F 
            Disp_DP_Status：小数点显示状态
	* @retval None      
*/
static void Disp_HEX(Disp_NUM_t Disp_NUM,uint8_t Dat,Disp_DP_Status_t Disp_DP_Status) 
{
	//参数范围检查
	if(Dat > 0x0F)
	{
		System.Assert_Failed();
	}
	
	//设置显示模式
	TM1620_Write_Byte(Disp_Mode_GRID6_SEG8); 
	SET_STB;
	
	//地址固定
	TM1620_Write_Byte(Write_Data_Addr_Fix); 
	SET_STB;
	
	//写地址
	TM1620_Write_Byte(Disp_NUM);
	//写数据
	if(Disp_DP_Status == Disp_DP_ON)
		TM1620_Write_Byte(Disp_Decode[Dat] + 0x80);
	else
		TM1620_Write_Byte(Disp_Decode[Dat]);
	SET_STB;
	
	//显示
  TM1620_Write_Byte(Display.Brightness);
	SET_STB; 
}

/*
	* @name   Disp_Other
	* @brief  数码管显示其他
  * @param  Disp_NUM:       数码管编号
            Dat：           编码数据
            Disp_DP_Status：小数点显示状态
	* @retval None      
*/
static void Disp_Other(Disp_NUM_t Disp_NUM,uint8_t Dat,Disp_DP_Status_t Disp_DP_Status) 
{
	//设置显示模式
	TM1620_Write_Byte(Disp_Mode_GRID6_SEG8); 
	SET_STB;
	
	//地址固定
	TM1620_Write_Byte(Write_Data_Addr_Fix); 
	SET_STB;
	
	//写地址
	TM1620_Write_Byte(Disp_NUM);
	//写数据
	if(Disp_DP_Status == Disp_DP_ON)
		TM1620_Write_Byte(Dat + 0x80);
	else
		TM1620_Write_Byte(Dat);
	SET_STB;
	
	//显示
  TM1620_Write_Byte(Display.Brightness);
	SET_STB; 
}
/*************************************
  End Of File
*************************************/
