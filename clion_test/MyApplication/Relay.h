#ifndef __Relay_H__
#define __Relay_H__

#include "MyApplication.h"

//����ö������
typedef enum
{
	Relay_Status_ON  = (uint8_t)0x01,
	Relay_Status_OFF = (uint8_t)0x00,
}Relay_Status_t;


//����ṹ������
typedef struct
{
	Relay_Status_t  Status;   //״̬
	
	void (*Relay_ON)(void);     //��
	void (*Relay_OFF)(void);    //�ر�
	void (*Relay_Flip)(void);   //��ת
} Relay_t;

/* extern variables-----------------------------------------------------------*/
extern Relay_t  Relay;
/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
