#include "timer3.h"
#include "counter.h"
uint32_t cnt=0;
uint32_t frequent=0;
uint8_t TIM3_COUNT_DONE=0;
uint16_t TIM3_COUNT_CYCLES=0;
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEKս��STM32������
//��ʱ�� ��������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//ͨ�ö�ʱ��3�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
//TIM3_Init(499,359);//72MHz/(500*360)=400Hz
void TIM3_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef TIM3_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
    TIM3_TimeBaseInitStructure.TIM_Period = arr;
    TIM3_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM3_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM3_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3,&TIM3_TimeBaseInitStructure);

    TIM_Cmd(TIM3,ENABLE);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE );


    NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}


void TIM3_IRQHandler()
{
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);   //???
    if(TIM3_COUNT_DONE==0)
    {
        if(TIM3_COUNT_CYCLES<399)
        {
            cnt += TIM1->CNT;  //ͳ�Ƽ�����1�ļ���ֵ
            TIM1->CNT=0;    //������1����
            TIM3_COUNT_CYCLES++;
        }
        else
        {
            cnt += TIM1->CNT;
            TIM1->CNT=0;
            cnt += cnt*0.0003;	//У׼
            frequent = cnt;
            TIM3_COUNT_DONE=1;
            TIM3_COUNT_CYCLES = 0;
            cnt = 0;
        }
    }
}








