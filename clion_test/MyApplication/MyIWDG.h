#ifndef __MyIWDG_H__
#define __MyIWDG_H__

#include "MyApplication.h"

//����ö������

//����ṹ������
typedef struct
{
	uint8_t FeedDog_Flag;  //ι����־λ
	
	void (*FeedDog)(void); //ι��
} MyIWDG_t;

/* extern variables-----------------------------------------------------------*/
extern  MyIWDG_t  MyIWDG;
/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
