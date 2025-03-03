#ifndef __System_H__
#define __System_H__

#define PROJECT_NAME             "LVGL Project"     //�ֱ�����
#define PROJECT_HARDWARE_VERSION  1.0      //Ӳ���汾
#define PROJECT_SOFTWARE_VERSION  1.0       //����汾


//����ṹ������
typedef struct
{
	void (*Run)(void);
	void (*Error_Handler)(void);
	void (*Assert_Failed)(void);
} System_t;

/* extern variables-----------------------------------------------------------*/
extern System_t  System;

/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
