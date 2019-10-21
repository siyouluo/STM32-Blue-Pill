#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
extern uint32_t cnt;
extern uint32_t frequent;
extern void TIM3_Init(u16 arr,u16 psc);
extern uint8_t TIM3_COUNT_DONE;
extern uint16_t TIM3_COUNT_CYCLES;
#endif
