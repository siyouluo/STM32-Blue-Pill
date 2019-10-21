#include "fingerprint.h"

/*
权限管理：
所有用户权限分为如下类型：
					修改模块参数		添加其他用户		修改其他用户权限		开锁操作
超级用户：root		允许				允许				可修改为任意权限		允许
普通用户：normal	禁止				允许(除root用户)	禁止					允许
临时用户：temporary	禁止				禁止				禁止					(R/N用户)指定的N次或无限次

*/

uint8_t FPM_Test_Connection()
{
	uint8_t i;
	uint8_t array[26]={0x55,0xAA,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	USART3_CLEAR_QUEUE();
	USART3_WriteBytes(26, array);
	USART3_RECIEVE_BYTES(26);
	if(USART3_RECEIEVE_QUEUE_BUF[8]==0&&USART3_RECEIEVE_QUEUE_BUF[9]==0)
	{
		return 1;//测试成功
	}
	else
	{
		return 0;//测试失败
	}
}