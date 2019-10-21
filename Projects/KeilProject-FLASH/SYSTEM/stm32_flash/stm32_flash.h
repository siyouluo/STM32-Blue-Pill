#ifndef _stm32_flash_H
#define _stm32_flash_H

#include "sys.h"


//用户根据自己的需要设置
#define STM32_FLASH_SIZE 64 	 //所选STM32的FLASH容量大小(单位为K)

//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH的起始地址
#define STM32_FLASH_SAVE_ADDR  0X0800F000		
//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)

vu16 STM32_FLASH_ReadHalfWord(u32 faddr); 
void STM32_FLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);		//从指定地址开始写入指定长度的数据
void STM32_FLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);   		//从指定地址开始读出指定长度的数据
					   


#endif

/*
const u8 text_buf[]="www.prechin.net";
#define TEXTLEN sizeof(text_buf)
u8 read_buf[TEXTLEN];

        STM32_FLASH_Write(STM32_FLASH_SAVE_ADDR,(u16*)text_buf,TEXTLEN);
        printf("write : %s\r\n",text_buf);

        delay_ms(100);
        STM32_FLASH_Read(STM32_FLASH_SAVE_ADDR,(u16 *)read_buf,TEXTLEN);
        printf("read  : %s\r\n",read_buf);
        delay_ms(100);
*/



