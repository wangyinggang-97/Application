#ifndef __SPI_Flash_H__
#define __SPI_Flash_H__

//ͷ�ļ�
#include "MyApplication.h"

////�궨��
//CS�ܽſ���
#define  	CLR_SPI_Flash_CS	 HAL_GPIO_WritePin(SPI_Flash_CS_GPIO_Port,SPI_Flash_CS_Pin,GPIO_PIN_RESET)
#define  	SET_SPI_Flash_CS	 HAL_GPIO_WritePin(SPI_Flash_CS_GPIO_Port,SPI_Flash_CS_Pin,GPIO_PIN_SET)

//Flash����
#define  	W25X_WriteEnable		    0x06 
#define  	W25X_WriteDisable			0x04 
#define  	W25X_ReadStatusReg1  		0x05 
#define  	W25X_ReadData			  	0x03 
#define  	W25X_PageProgram		  	0x02 
#define  	W25X_SectorErase		  	0x20 
#define  	W25X_ChipErase			  	0xC7 
#define  	W25X_ReadJedecID     		0x9F 

#define  	SPI_FLASH_PageSize   		256
#define  	Flash_Status1_BUSY      BIT0  //æµ��־λ
#define  	Dummy_Byte           		0xFF  //������

//����ö������

//����ṹ������
typedef struct
{
  uint32_t  JedecID;	                                //�豸��ʶ�� -> ������+�ڴ�����+����
	
	void (*ReadJedecID)(void);                          //��ȡ�豸��ʶ��
	void (*EraseSector)(uint32_t);                      //��������(4kB)
	void (*EraseTotal)(void);                           //����ȫ��
    void (*WriteUnfixed)(uint8_t*,uint32_t,uint32_t);   //д�벻�̶���������
	void (*ReadUnfixed)(uint8_t*,uint32_t,uint32_t);    //��ȡ���̶���������
} SPI_Flash_t;

/* extern variables-----------------------------------------------------------*/
extern SPI_Flash_t  SPI_Flash ;

/* extern function prototypes-------------------------------------------------*/

#endif
/********************************************************
  End Of File
********************************************************/
