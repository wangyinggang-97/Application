/* Includes ------------------------------------------------------------------*/
#include "MyApplication.h"

/* Private define-------------------------------------------------------------*/
//TCP������
#define TCP_Server  (uint8_t*)"AT+CIPSTART=\"TCP\",\"192.168.1.129\",8888\r\n"  //���Զ�ģ���TCP������
//#define TCP_Server  (uint8_t*)"AT+CIPSTART=\"TCP\",\"192.168.1.132\",8888\r\n"  //�ֻ���ģ���TCP������

//״ָ̬ʾ��
#define WIFI_LED_ON    LED.LED_ON(LED3); 
#define WIFI_LED_OFF   LED.LED_OFF(LED3);
#define WIFI_LED_FLIP  LED.LED_Flip(LED3);

#define TCP_LED_ON     HAL_GPIO_WritePin(OUT_PNP_GPIO_Port,OUT_PNP_Pin,GPIO_PIN_RESET);
#define TCP_LED_OFF    HAL_GPIO_WritePin(OUT_PNP_GPIO_Port,OUT_PNP_Pin,GPIO_PIN_SET);

#define Error_LED_ON   HAL_GPIO_WritePin(OUT_NPN_GPIO_Port,OUT_NPN_Pin,GPIO_PIN_SET);
#define Error_LED_OFF  HAL_GPIO_WritePin(OUT_NPN_GPIO_Port,OUT_NPN_Pin,GPIO_PIN_RESET);


/* Private variables----------------------------------------------------------*/

/* Private function prototypes------------------------------------------------*/
static void Init(void);                            //ESP8266��ʼ��
static void SmartConifg(void);                     //WIFIģ������
static void TCP_Connect_Server(void);              //ͨ��TCP���ӷ�����
static void Transfer_SHT30(void);                  //����SHT30����ʪ��
static void Receive_Information(void);             //������Ϣ
static void DMA_Receive_Set(void);                 //DMA��������
static void Error(void);                           //������Ϣ

static void SendAT(uint8_t *,uint8_t *);           //����ATָ��

/* Public variables-----------------------------------------------------------*/
ESP8266_t  ESP8266 = 
{
	FALSE,
	TIMER6_10S,
	FALSE,

	Init,
	SmartConifg,
	TCP_Connect_Server,
	Transfer_SHT30,
	Receive_Information,
	DMA_Receive_Set,
	Error
};

/*
	* @name   Init
	* @brief  ESP8266��ʼ��
	* @param  None
	* @retval None      
*/
static void Init() 
{
	//��λģ��
	HAL_GPIO_WritePin(WIFI_RST_GPIO_Port,WIFI_RST_Pin,GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(WIFI_RST_GPIO_Port,WIFI_RST_Pin,GPIO_PIN_SET);
	
	//ʹ��ģ��
	HAL_GPIO_WritePin(WIFI_EN_GPIO_Port,WIFI_EN_Pin,GPIO_PIN_SET);
	//��ʱ500ms���ȴ�WIFIģ���ȶ���׼���ý���ATָ��
	HAL_Delay(500);
	
	//ͬ��������
	Timer6.usDelay_Timer = 0;
	do
	{
		//DMA���½�������
   	ESP8266.DMA_Receive_Set();
		
		//����ATָ��
		UART2.SendString((uint8_t*)"AT\r\n");
		//��ʱ100ms���ȴ��������
		HAL_Delay(100);
		
		//��ӡ��Ϣ
		printf("%s",UART2.pucRec_Buffer);
		
		//��ʱ����
		if(Timer6.usDelay_Timer >= TIMER6_10S)
		{
			ESP8266.Error();
			break;
		}
	}
	while(strstr((const char*)UART2.pucRec_Buffer,"OK") == NULL);
}

/*
	* @name   SendAT
	* @brief  ����ATָ��
	* @param  AT_Command  -> �����͵�ATָ��
	          Respond_Str -> ��Ӧ�����а������ַ���
	* @retval None      
*/
static void SendAT(uint8_t * AT_Command,uint8_t * Respond_Str)
{
	uint8_t* const  Ptr_AT_Command   = AT_Command;
	uint8_t* const  Ptr_Respond_Str  = Respond_Str;
	
	//DMA���½�������
	ESP8266.DMA_Receive_Set();
	
	//����ATָ��
	UART2.SendString(Ptr_AT_Command);	
	//��ӡ��Ϣ
	printf("%s",Ptr_AT_Command);
	
	//�ȴ�ģ���Ӧ���ݣ���ʱ������
	Timer6.usDelay_Timer = 0;
	while(strstr((const char*)UART2.pucRec_Buffer,"\r\n") == NULL)
	{
		if(Timer6.usDelay_Timer > TIMER6_100mS)
		{
			ESP8266.Error();
			break;
		}
	}
	//��ʱ10ms��������ȫ���ֽ�
	HAL_Delay(10);
	
	//ģ���Ӧ���ݴ�����
	if(strstr((const char*)UART2.pucRec_Buffer,(const char*)Ptr_Respond_Str) == NULL)
	{
		ESP8266.Error();
	}
	
	//��ӡ��Ϣ
	printf("%s",UART2.pucRec_Buffer);
}

/*
	* @name   SmartConifg
	* @brief  WIFIģ������
	* @param  None
	* @retval None      
*/
static void SmartConifg()
{
	if(ESP8266.SmartConifg_Flag == TRUE)
	{
		//�ر�ָʾ��
		WIFI_LED_OFF;
		TCP_LED_OFF;
		
		//�˳�͸��ģʽ
		*(UART2.pucSend_Buffer + 0) = '+';
		*(UART2.pucSend_Buffer + 1) = '+';
		*(UART2.pucSend_Buffer + 2) = '+';
		UART2.SendArray(UART2.pucSend_Buffer,3);
		HAL_Delay(1000);
		
		//����
		SendAT((uint8_t*)"AT\r\n",(uint8_t*)"OK");                //����AT		
    SendAT((uint8_t*)"ATE0\r\n",(uint8_t*)"OK");              //�رջ���
    SendAT((uint8_t*)"AT+CWMODE_CUR=1\r\n",(uint8_t*)"OK");   //WIFIģ������ΪSTAģʽ
    SendAT((uint8_t*)"AT+CWAUTOCONN=1\r\n",(uint8_t*)"OK");   //�ϵ��Զ����ӵ�AP
    SendAT((uint8_t*)"AT+CWSTARTSMART=2\r\n",(uint8_t*)"OK"); //����SmartConfig(SmartConfig����ΪAirKiss)
		
		printf("Start SmartConfig:\r\n");	
		//�ȴ�������3���ӳ�ʱ�˳�
		Timer6.usDelay_Timer = 0;
		while(Timer6.usDelay_Timer < TIMER6_3min)
		{
			//DMA���½�������
			ESP8266.DMA_Receive_Set();
			
			//WIFIָʾ�ƿ���
			HAL_Delay(100);
			WIFI_LED_FLIP;
			
			//��ӡ��Ϣ
			printf("%s",UART2.pucRec_Buffer);
			
			//�жϻ�ȡAP
			if(strstr((const char*)UART2.pucRec_Buffer, "Smart get wifi info") != NULL) //��ȡ��AP��Ϣ
			{
				Timer6.usDelay_Timer = TIMER6_3min - TIMER6_10S;
			}
			
			//�ж�����AP
			if(strstr((const char*)UART2.pucRec_Buffer, "connected wifi") != NULL) //�ɹ����ӵ�AP
			{
				SendAT((uint8_t*)"AT+CWSTOPSMART\r\n",(uint8_t*)"OK"); //ֹͣSmartConfig
				break;
			}
		}
		
		//�����Ϣ		
		if(Timer6.usDelay_Timer < TIMER6_3min)
		{
			printf("\r\n\r\nSmartconfig Success!\r\n");
			ESP8266.TCP_Connect_Status  = FALSE;
			ESP8266.TCP_Reconnect_Timer = TIMER6_10S; //��������TCP
			//���������־λ
		  ESP8266.SmartConifg_Flag = FALSE;
		}
		else
		{
			printf("\r\n\r\nSmartconfig Fail!\r\n");
			ESP8266.TCP_Connect_Status  = FALSE;
			ESP8266.TCP_Reconnect_Timer = 0;
		}
		//�ر�ָʾ��
		WIFI_LED_OFF;
	}
}

/*
	* @name   TCP_Connect_Server
	* @brief  ͨ��TCP���ӷ�����
	* @param  None
	* @retval None      
*/
static void TCP_Connect_Server()
{
	uint8_t AP_Connect_Flag = FALSE; //AP���ӱ�־λ��ΪTRUE���Ž���TCP����
	
	SendAT((uint8_t*)"AT\r\n",(uint8_t*)"OK");              //����AT		
  SendAT((uint8_t*)"ATE0\r\n",(uint8_t*)"OK");            //�رջ���
  SendAT((uint8_t*)"AT+CWMODE_CUR=1\r\n",(uint8_t*)"OK"); //WIFIģ������ΪSTAģʽ
	
	//��ȡIP
	Timer6.usDelay_Timer = 0;
	do
	{
		//DMA���½�������
	  ESP8266.DMA_Receive_Set();
		//����ATָ��
		UART2.SendString((uint8_t*)"AT+CIFSR\r\n");
		//��ʱ1000ms���ȴ��������
		HAL_Delay(1000);
		
		//��ӡ��Ϣ
		printf("%s",UART2.pucRec_Buffer);
		
		//10sû�л�ȡIP�������ȴ�
		if(Timer6.usDelay_Timer >= TIMER6_10S)
		{
			ESP8266.Error();
			break;
		}
	}
	while(strstr((const char*)UART2.pucRec_Buffer,"0.0.0.0") != NULL);
	//����WIFIָʾ��
	if(Timer6.usDelay_Timer < TIMER6_10S)
	{
		WIFI_LED_ON;	
		AP_Connect_Flag = TRUE;
		printf("AP connect success!\r\n");
	}
	else
	{
		WIFI_LED_OFF;
		AP_Connect_Flag = FALSE;
		printf("AP connect fail,auto entry Smartconfig mode!\r\n");
		ESP8266.SmartConifg_Flag = TRUE;
	}	
	
	//�ȴ��ȶ����ӵ�AP
	Timer6.usDelay_Timer = 0;
	do
	{
		//DMA���½�������
	  ESP8266.DMA_Receive_Set();
		//����ATָ��
		UART2.SendString((uint8_t*)"AT\r\n");
		//��ʱ100ms���ȴ��������
		HAL_Delay(100);
		
		//��ӡ��Ϣ
		printf("%s",UART2.pucRec_Buffer);
		
		//10sû��ͬ������ʱ������
		if(Timer6.usDelay_Timer >= TIMER6_10S)
		{
			ESP8266.Error();
			break;
		}
	}
	while(strstr((const char*)UART2.pucRec_Buffer,"OK") == NULL);
	
	//���ӷ�����
	if(AP_Connect_Flag == TRUE)
	{	
		printf("Connect TCP Server!\r\n");
		
		Timer6.usDelay_Timer = 0;
		do
		{
			//DMA���½�������
			ESP8266.DMA_Receive_Set();
			//����ATָ��
			UART2.SendString(TCP_Server);
			//��ʱ500ms���ȴ��������
			HAL_Delay(500);
			
			//��ӡ��Ϣ
			printf("%s",UART2.pucRec_Buffer);
			
			//10sû�����ӵ�TCP Server
			if(Timer6.usDelay_Timer >= TIMER6_10S)
			{
				printf("Connect TCP Server Failure!\r\n");		
				
				ESP8266.TCP_Connect_Status = FALSE;
				TCP_LED_OFF;
				break;
			}
			
			//���ӵ�������
			if(strstr((const char*)UART2.pucRec_Buffer,"CONNECT") != NULL)
			{
				printf("Connect TCP Server Success!\r\n");

				//ʹ��͸��ģʽ
				SendAT((uint8_t*)"AT+CIPMODE=1\r\n",(uint8_t*)"OK"); //ʹ��͸��
				SendAT((uint8_t*)"AT+CIPSEND\r\n",(uint8_t*)">");    //��ʼ����
				
				ESP8266.TCP_Connect_Status = TRUE;
				TCP_LED_ON;
				Error_LED_OFF;
				break;
			}
		}
		while(strstr((const char*)UART2.pucRec_Buffer,"CONNECT") == NULL);
		
		//DMA���½������ã���ʼ����TCP��������ָ��
		ESP8266.DMA_Receive_Set();
	}
}

/*
	* @name   Transfer_SHT30
	* @brief  ����SHT30����ʪ��
	* @param  NONE
	* @retval None      
*/
static void Transfer_SHT30()
{
  float    Temp_float = 0;
	uint16_t Temp_uint16 = 0;
	//�¶�ֵ  -40��125�棬����0.1��
	if(SHT30.fTemperature < 0)
	{
		Temp_float = 0 - SHT30.fTemperature;
		*(UART2.pucSend_Buffer + 0) = '-';
	}
	else
	{
		Temp_float = SHT30.fTemperature;
		*(UART2.pucSend_Buffer + 0) = ' ';
	}
	
	Temp_uint16 = (uint16_t)(Temp_float*10);
	if(Temp_uint16 < 10) //0.x
	{
		*(UART2.pucSend_Buffer + 1) = ' ';
		*(UART2.pucSend_Buffer + 2) = ' ';
		*(UART2.pucSend_Buffer + 3) = '0';
		*(UART2.pucSend_Buffer + 4) = '.';
		*(UART2.pucSend_Buffer + 5) = Temp_uint16 + '0';
	}
	else if(Temp_uint16 < 100)//x.x
	{
		*(UART2.pucSend_Buffer + 1) = ' ';
		*(UART2.pucSend_Buffer + 2) = ' ';
		*(UART2.pucSend_Buffer + 3) = Temp_uint16/10 + '0';
		*(UART2.pucSend_Buffer + 4) = '.';
		*(UART2.pucSend_Buffer + 5) = Temp_uint16%10 + '0';
	}
	else if(Temp_uint16 < 1000)//xx.x
	{
		*(UART2.pucSend_Buffer + 1) = ' ';
		*(UART2.pucSend_Buffer + 2) = Temp_uint16/100 + '0';
		*(UART2.pucSend_Buffer + 3) = Temp_uint16%100/10 + '0';
		*(UART2.pucSend_Buffer + 4) = '.';
		*(UART2.pucSend_Buffer + 5) = Temp_uint16%10 + '0';
	}
	else//xxx.x
	{
		*(UART2.pucSend_Buffer + 1) = Temp_uint16/1000 + '0';
		*(UART2.pucSend_Buffer + 2) = Temp_uint16%1000/100 + '0';
		*(UART2.pucSend_Buffer + 3) = Temp_uint16%100/10 + '0';
		*(UART2.pucSend_Buffer + 4) = '.';
		*(UART2.pucSend_Buffer + 5) = Temp_uint16%10 + '0';
	}
	//���ݴ���
	UART2.SendString((uint8_t *)"The Temperature of SHT30 is ");
	HAL_Delay(3);  //��ʱ���ȴ��ַ���������   ʱ�� = (11*1000ms)/115200 * 28 = 2.68ms
	UART2.SendArray(UART2.pucSend_Buffer,6);
	HAL_Delay(1);  //��ʱ���ȴ����鷢����     ʱ�� = (11*1000ms)/115200 * 6 = 0.58ms
	UART2.SendString((uint8_t *)"��\r\n");
	HAL_Delay(1);  //��ʱ���ȴ��ַ���������   ʱ�� = (11*1000ms)/115200 * 4 = 0.39ms
	
	//ʪ��ֵ 0 - 100%RH������1%RH
	if(SHT30.ucHumidity < 10)
	{
		*(UART2.pucSend_Buffer + 0) = ' ';
		*(UART2.pucSend_Buffer + 1) = SHT30.ucHumidity + '0';
	}
	else
	{
		*(UART2.pucSend_Buffer + 0) = SHT30.ucHumidity/10 + '0';
		*(UART2.pucSend_Buffer + 1) = SHT30.ucHumidity%10 + '0';
	}
	
	*(UART2.pucSend_Buffer + 2) = '%';
	*(UART2.pucSend_Buffer + 3) = 'R';
	*(UART2.pucSend_Buffer + 4) = 'H';

	//���ݴ���
	UART2.SendString((uint8_t *)"The Humidity of SHT30 is ");
	HAL_Delay(3);  //��ʱ���ȴ��ַ���������   ʱ�� = (11*1000ms)/115200 * 25 = 2.39ms
	UART2.SendArray(UART2.pucSend_Buffer,5);
}

/*
	* @name   Receive_Information
	* @brief  ������Ϣ
	* @param  None 
	* @retval None      
*/
static void Receive_Information()
{	
	if(ESP8266.TCP_Connect_Status == TRUE)
	{
		printf("Received information from the TCP server\r\n");
	  printf("%s",UART2.pucRec_Buffer);
		printf("\r\n");
		
		//�л��̵���״̬
		if(strstr((const char*)UART2.pucRec_Buffer,"Flip Relay") != NULL)
	  {
			Relay.Relay_Flip();
		}
		//�л�������״̬
		/*if(strstr((const char*)UART2.pucRec_Buffer,"Flip Buzzer") != NULL)
	  {
			if(Buzzer.Status == Buzzer_Status_OFF)
			{
				Buzzer.ON();
			}
			else
			{
				Buzzer.OFF();
			}
		}*/
		
		//DMA���½������ã�����TCP����������ָ��
		ESP8266.DMA_Receive_Set();
	}
}

/*
	* @name   DMA_Receive_Set
	* @brief  DMA��������
	* @param  None 
	* @retval None      
*/
static void DMA_Receive_Set(void)
{
	//����2��ֹDMA����
	HAL_UART_DMAStop(&huart2);
	//�建��
	Public.Memory_Clr(UART2.pucRec_Buffer,strlen((const char*)UART2.pucRec_Buffer));		
	//����2����DMA����
	HAL_UART_Receive_DMA(&huart2,UART2.pucRec_Buffer,UART2_Rec_LENGTH);
}

/*
	* @name   Error
	* @brief  ������Ϣ
	* @param  None 
	* @retval None      
*/
static void Error()
{
	Error_LED_ON;
}
/*************************************
  End Of File
*************************************/
