/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/

/* Private function prototypes------------------------------------------------*/      
static void Direction_Adjust(void);        //��������������
static void Speed_Adjust(Speed_Change_t);  //��������ٶȵ���
static void Step_One_Pulse(void);          //�����������һ������

/* Public variables-----------------------------------------------------------*/

//����ṹ�������
Unipolar_Step_Motor_t Unipolar_Step_Motor = 
{
  Stop_State,
	Forward_State, 
	Speed_6,
	0,
	Drive_Mode_8_Beats,
	0,
	(uint16_t)4096,
	
	Direction_Adjust,
	Speed_Adjust,
	Step_One_Pulse
};

/*
	* @name   Direction_Adjust
	* @brief  ֱ������������
	* @param  None
	* @retval None      
*/
static void Direction_Adjust(void)
{
	if(Unipolar_Step_Motor.Status == Start_State)
	{
		//����������з���
		if(Unipolar_Step_Motor.Direction == Reverse_State)
		{
			Unipolar_Step_Motor.Direction = Forward_State;
		}
		else
		{
			Unipolar_Step_Motor.Direction = Reverse_State;
		}
		
		Unipolar_Step_Motor.Circle = Circle_Set_Value;
		Unipolar_Step_Motor.Pulse_Cnt = 0;
	}
}

/*
	* @name   Speed_Adjust
	* @brief  ֱ������ٶȵ���
	* @param  Speed_Change -> �ٶȱ仯
	* @retval None      
*/
static void Speed_Adjust(Speed_Change_t Speed_Change)
{
	if(Unipolar_Step_Motor.Status == Start_State)
	{
		if(Speed_Change == Speed_up)
		{
			//�������ٶ�
			switch(Unipolar_Step_Motor.Speed)
			{
				case Speed_1: Unipolar_Step_Motor.Speed = Speed_2; break;
				case Speed_2: Unipolar_Step_Motor.Speed = Speed_3; break;
				case Speed_3: Unipolar_Step_Motor.Speed = Speed_4; break;
				case Speed_4: Unipolar_Step_Motor.Speed = Speed_5; break;
				case Speed_5: Unipolar_Step_Motor.Speed = Speed_6; break;
				case Speed_6: Unipolar_Step_Motor.Speed = Speed_7; break;
				case Speed_7: Unipolar_Step_Motor.Speed = Speed_8; break;
				case Speed_8: Unipolar_Step_Motor.Speed = Speed_9; break;
				case Speed_9: Unipolar_Step_Motor.Speed = Speed_9; break;
				default:Unipolar_Step_Motor.Speed = Speed_6; 
			}
		}
		else
		{
			//��С����ٶ�
			switch(Unipolar_Step_Motor.Speed)
			{
				case Speed_1: Unipolar_Step_Motor.Speed = Speed_1; break;
				case Speed_2: Unipolar_Step_Motor.Speed = Speed_1; break;
				case Speed_3: Unipolar_Step_Motor.Speed = Speed_2; break;
				case Speed_4: Unipolar_Step_Motor.Speed = Speed_3; break;
				case Speed_5: Unipolar_Step_Motor.Speed = Speed_4; break;
				case Speed_6: Unipolar_Step_Motor.Speed = Speed_5; break;
				case Speed_7: Unipolar_Step_Motor.Speed = Speed_6; break;
				case Speed_8: Unipolar_Step_Motor.Speed = Speed_7; break;
				case Speed_9: Unipolar_Step_Motor.Speed = Speed_8; break;
				default:Unipolar_Step_Motor.Speed = Speed_6;
			}
		}
		
		//���¶�ʱ��7�ļ�ʱ��װ�ؼĴ���
		TIM7 ->ARR = Unipolar_Step_Motor.Speed;
	}
}

/*
	* @name   Step_One_Pulse
	* @brief  �����������һ������
	* @param  Speed_Change -> �ٶȱ仯
	* @retval None      
*/
static void Step_One_Pulse(void)
{
	static uint8_t Position = 0;
	
	//������
	if(Unipolar_Step_Motor.Drive_Mode == Drive_Mode_Single_4_Beats)
	{
		if(Unipolar_Step_Motor.Direction == Forward_State)
		{
			//���򲽽�  A - D - C - B
			switch(Position)
			{
				case 0: SET_Motor_A; CLR_Motor_B; CLR_Motor_C; CLR_Motor_D; break;
				case 1: CLR_Motor_A; CLR_Motor_B; CLR_Motor_C; SET_Motor_D; break;
				case 2: CLR_Motor_A; CLR_Motor_B; SET_Motor_C; CLR_Motor_D; break;
				case 3: CLR_Motor_A; SET_Motor_B; CLR_Motor_C; CLR_Motor_D; break;
				default: System.Error_Handler();
			}
		}
		else
		{
			//���򲽽�  A - B - C - D
			switch(Position)
			{
				case 0: SET_Motor_A; CLR_Motor_B; CLR_Motor_C; CLR_Motor_D; break;
				case 1: CLR_Motor_A; SET_Motor_B; CLR_Motor_C; CLR_Motor_D; break;
				case 2: CLR_Motor_A; CLR_Motor_B; SET_Motor_C; CLR_Motor_D; break;
				case 3: CLR_Motor_A; CLR_Motor_B; CLR_Motor_C; SET_Motor_D; break;
				default: System.Error_Handler();
			}
		}
		
		//����λ����Ϣ
		if((++Position) == 4)
				Position = 0;
	}
	
	//˫����
	if(Unipolar_Step_Motor.Drive_Mode == Drive_Mode_Double_4_Beats)
	{
		if(Unipolar_Step_Motor.Direction == Forward_State)
		{
			//���򲽽�  DA - CD - BC - AB
			switch(Position)
			{
				case 0: SET_Motor_A; CLR_Motor_B; CLR_Motor_C; SET_Motor_D; break;
				case 1: CLR_Motor_A; CLR_Motor_B; SET_Motor_C; SET_Motor_D; break;
				case 2: CLR_Motor_A; SET_Motor_B; SET_Motor_C; CLR_Motor_D; break;
				case 3: SET_Motor_A; SET_Motor_B; CLR_Motor_C; CLR_Motor_D; break;
				default: System.Error_Handler();
			}
		}
		else
		{
			//���򲽽�  DA - AB - BC - CD
			switch(Position)
			{
				case 0: SET_Motor_A; CLR_Motor_B; CLR_Motor_C; SET_Motor_D; break;
				case 1: SET_Motor_A; SET_Motor_B; CLR_Motor_C; CLR_Motor_D; break;
				case 2: CLR_Motor_A; SET_Motor_B; SET_Motor_C; CLR_Motor_D; break;
				case 3: CLR_Motor_A; CLR_Motor_B; SET_Motor_C; SET_Motor_D; break;
				default: System.Error_Handler();
			}
		}
		
		//����λ����Ϣ
		if((++Position) == 4)
				Position = 0;
	}
	
	//������
	if(Unipolar_Step_Motor.Drive_Mode == Drive_Mode_8_Beats)
	{
		if(Unipolar_Step_Motor.Direction == Forward_State)
		{
			//���򲽽� A - DA - D - CD - C - BC - B - AB
			switch(Position)
			{
				case 0: SET_Motor_A; CLR_Motor_B; CLR_Motor_C; CLR_Motor_D; break;
				case 1: SET_Motor_A; CLR_Motor_B; CLR_Motor_C; SET_Motor_D; break;
				case 2: CLR_Motor_A; CLR_Motor_B; CLR_Motor_C; SET_Motor_D; break;
				case 3: CLR_Motor_A; CLR_Motor_B; SET_Motor_C; SET_Motor_D; break;
				case 4: CLR_Motor_A; CLR_Motor_B; SET_Motor_C; CLR_Motor_D; break;
				case 5: CLR_Motor_A; SET_Motor_B; SET_Motor_C; CLR_Motor_D; break;
				case 6: CLR_Motor_A; SET_Motor_B; CLR_Motor_C; CLR_Motor_D; break;
				case 7: SET_Motor_A; SET_Motor_B; CLR_Motor_C; CLR_Motor_D; break;
				default:System.Error_Handler();
			}
		}
		else
		{
			//���򲽽� A - AB - B - BC - C -CD - D - DA 
			switch(Position)
			{
				case 0: SET_Motor_A; CLR_Motor_B; CLR_Motor_C; CLR_Motor_D; break;
				case 1: SET_Motor_A; SET_Motor_B; CLR_Motor_C; CLR_Motor_D; break; 
				case 2: CLR_Motor_A; SET_Motor_B; CLR_Motor_C; CLR_Motor_D; break;
				case 3: CLR_Motor_A; SET_Motor_B; SET_Motor_C; CLR_Motor_D; break;
				case 4: CLR_Motor_A; CLR_Motor_B; SET_Motor_C; CLR_Motor_D; break; 
				case 5: CLR_Motor_A; CLR_Motor_B; SET_Motor_C; SET_Motor_D; break;
				case 6: CLR_Motor_A; CLR_Motor_B; CLR_Motor_C; SET_Motor_D; break;
				case 7: SET_Motor_A; CLR_Motor_B; CLR_Motor_C; SET_Motor_D; break;
				default: System.Error_Handler();
			}
		}
		
		//����λ����Ϣ
		if((++Position) == 8)
				Position = 0;
	}
}
/********************************************************
  End Of File
********************************************************/
