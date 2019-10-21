#ifndef _SERVO_H
#define _SERVO_H

#include "sys.h"

extern void TIM1_Servo_Init(u16 arr,u16 psc);

#endif


/*
		TIM1_Servo_Init(199,7199);
		delay_ms(1000);
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
*/
