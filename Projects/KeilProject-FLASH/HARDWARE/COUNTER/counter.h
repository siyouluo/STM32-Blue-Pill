#ifndef __ENCODER_H
#define __ENCODER_H
#include "sys.h"	 
#define MAX_N_PAPER 31
extern void TIM1_Counter_Init(void);
extern uint8_t Get_Num_Paper(uint32_t freq);
extern uint32_t freq_measure[MAX_N_PAPER];

#endif
