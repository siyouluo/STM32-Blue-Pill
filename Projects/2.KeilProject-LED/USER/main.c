#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

void All_Init()
{
	delay_init();	    //延时函数初始化	
	LED_Init();		  	//初始化与LED连接的硬件接口
}
int main(void)
 {	
	All_Init();
	while(1)
	{
		LED=~LED;
		delay_ms(500);	//延时300ms
	}
 }


