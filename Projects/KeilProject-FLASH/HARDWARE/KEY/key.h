#ifndef __KEY_H
#define __KEY_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//按键驱动代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////


//#define SW4 PEin(4)   	//PE4
//#define SW5 PEin(3)	//PE3
//#define KEY2 PEin(2)	//PE2
//#define WK_UP PAin(0)	//PA0  WK_UP

#define SW4  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//读取按键4
#define SW5  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)//读取按键5



#define SW4_PRES 	1	//SW4按下
#define SW5_PRES	2	//SW5按下


void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8);  	//按键扫描函数
#endif
