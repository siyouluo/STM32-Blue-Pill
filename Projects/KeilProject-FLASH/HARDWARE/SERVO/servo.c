#include "servo.h"
/********************************************************************************************
 * @Filename:pwm.c
 * @Author: Luo Siyou
 * @Contact: siyouluo11@gmail.com
 * @Info:输出双通道PWM信号
 * @usage:TIM1_PWM_Init(7199,0);
			PWMA=3000;
#define PWMB   TIM1->CCR4  //PA11
#define PWMA   TIM1->CCR1  //PA8
*************************************************************************/

/**
  * @brief	:定时器1初始化,配置为PWM输出模式
  * @param	arr:自动重装值
  * @param	psc:时钟预分频数
  * @usage	:TIM1_Servo_Init(199,7199);
			PWM频率=72MHz/(7199+1)/(199+1)=10KHz/(199+1) = 50Hz
  */
void TIM1_Servo_Init(u16 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_GPIOA, ENABLE);

    //设置该引脚为复用输出功能,输出TIM1 CH1 CH4的PWM脉冲波形
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11; //TIM1_CH1,TIM1_CH4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler =psc;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_Pulse = 0;                            //设置待装入捕获比较寄存器的脉冲值
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //输出极性:TIM输出比较极性高
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

    TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能

    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH4预装载使能

    TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器

    TIM_Cmd(TIM1, ENABLE);  //使能TIM1
}

