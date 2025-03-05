/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/

/* Private variables----------------------------------------------------------*/
static void Peripheral_Set(void); 

/* Public variables-----------------------------------------------------------*/
MyInit_t MyInit = 
{
        0,
	    Peripheral_Set
};

/* Private function prototypes------------------------------------------------*/      


/*
	* @name   Peripheral_Set
	* @brief  外设设置
	* @param  None
	* @retval None      
*/
static void Peripheral_Set()
{
    user_main_info("Project Name is %s",PROJECT_NAME);
    user_main_info("SoftWare_Version is V%.1f", PROJECT_SOFTWARE_VERSION);
    user_main_info("SoftWare_Version is V%.1f", PROJECT_HARDWARE_VERSION);

	  Timer6.Timer6_Start_IT();//启动定时器6
    SPI_Flash.ReadJedecID();
	  
	  lv_init();
	  lv_port_disp_init();
	  lv_port_indev_init();
	
  	SHT30_Init();
	  Servo_Init();
	  
	  Servo_Test();
	
    //触摸屏幕校准	
//	  SPI_Flash.EraseTotal();
//	  user_main_printf("spi flash erase ok!!");
		SPI_Flash.ReadUnfixed(&Touch_Calibrate_Para.Calibrate_Flag,Touch_Calibrate_Para_Addr,sizeof(Touch_Calibrate_Para));
		if(Touch_Calibrate_Para.Calibrate_Flag != Touch_Calibrate_OK) 
		{
			while(!Touch.Calibrate());
		}
//    lv_ex_get_started_1();	
//	  lv_ex_get_started_2();
//	  lv_ex_get_started_3();
//lv_demo_widgets();
//      lv_demo_benchmark();
}

/********************************************************
  End Of File
********************************************************/
