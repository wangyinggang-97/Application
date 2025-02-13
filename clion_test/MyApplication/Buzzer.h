#ifndef __Buzzer_H__
#define __Buzzer_H__

#include "MyApplication.h"

//����ö������
typedef enum
{
	Buzzer_Status_ON  = (uint8_t)0x01,
	Buzzer_Status_OFF = (uint8_t)0x00,
}Buzzer_Status_t;

//����ṹ������
typedef struct
{
	Buzzer_Status_t  Status;   //״̬

	void (*ON)(void);     //��
	void (*OFF)(void);    //�ر�
} Buzzer_t;

/* extern variables-----------------------------------------------------------*/
extern Buzzer_t  Buzzer;
/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
