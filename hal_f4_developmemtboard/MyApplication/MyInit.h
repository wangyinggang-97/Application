#ifndef __MyInit_H__
#define __MyInit_H__
#include "MyApplication.h"
//����ṹ������
typedef struct
{
    uint8_t addr;
	void (*Peripheral_Set)(void);
} MyInit_t;

/* extern variables-----------------------------------------------------------*/
extern MyInit_t  MyInit;
/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
