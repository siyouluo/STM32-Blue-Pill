#include "counter.h"
uint32_t freq_measure[MAX_N_PAPER]={\
	282582,309218,331398,347827,363314,378067,391188,405209,415437,422652,\
	433577,440966,449574,456685,464869,471651,478954,484517,490586,496236,\
	500026,506312,509279,513236,518024,521293,525342,528175,531460,534542,\
	565374
};//Hz


uint8_t Get_Num_Paper(uint32_t freq)
{
	uint8_t i;
	uint32_t meddian=0;
	if(freq<freq_measure[0]-10000)	return 0;
	for(i=0;i<MAX_N_PAPER-1;i++)
	{
		meddian = (freq_measure[i]+freq_measure[i+1])/2;
		if(freq<meddian)	return i+1;
	}
	return 31;
}
void TIM1_Counter_Init()
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM1_TimeBaseInitStructure;	 
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);//??TIM1?????
	TIM1_TimeBaseInitStructure.TIM_Period = 0xFFFF;//????????
	TIM1_TimeBaseInitStructure.TIM_Prescaler = 0;//????
	TIM1_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM1_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//????
	TIM_TimeBaseInit(TIM1,&TIM1_TimeBaseInitStructure);	
	  
	TIM_ETRClockMode1Config(TIM1, TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted, 0x00);  //???????????,?????????????
	
	TIM_Cmd(TIM1,ENABLE); 
	
}

