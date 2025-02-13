#ifndef __KEY_H__
#define __KEY_H__

#include "MyApplication.h"

//����ö������
typedef enum
{
	KEYNULL = 0,
	KEY1    = 1,
	KEY2    = 2,
	KEY3    = 3,
	KEY4    = 4
}KeyCode_t;


//����ṹ������
typedef struct
{
	KeyCode_t  KeyCode;   //��������
	
	void (*GetKeyCode)(void);  //��ȡ��������
} KEY_t;

/* extern variables-----------------------------------------------------------*/
extern KEY_t  KEY;
/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
