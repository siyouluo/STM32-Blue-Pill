#include "sys.h"
#include "delay.h"
#include "usart1.h"
#include "usart3.h"
#include "iic.h"
#include "stm32_flash.h"
#include "servo.h"
#include "fingerprint.h"
#include "led.h"
#include "oled.h"



void All_Init()
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();	    //延时函数初始化
    LED_Init();		  	//初始化与LED连接的硬件接口
    USART1_Init(57600);
	USART3_Init(115200);
    IIC_Init();
    OLED_Init();
	TIM1_Servo_Init(199,7199);
}
int main(void)
{
    All_Init();
    while(1)
    {

        LED = ~LED;
		TIM_SetCompare1(TIM1, 195);//0 deg
		delay_ms(1000);
		TIM_SetCompare1(TIM1, 190);//45 deg
		delay_ms(1000);
		TIM_SetCompare1(TIM1, 185);//90 deg
		delay_ms(1000);
		TIM_SetCompare1(TIM1, 180);//135 deg
		delay_ms(1000);
		TIM_SetCompare1(TIM1, 175);//180 deg
		delay_ms(1000);

    }
}


