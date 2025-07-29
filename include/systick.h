#ifndef __SYSTICK_H__
#define __SYSTICK_H__

#include "stm32f446xx.h"

extern volatile uint32_t msTicks;
extern volatile uint32_t cnt;
extern volatile uint32_t sec_cnt;
void SysTick_Init(void);
void SysTick_Handler(void);
void SysTick_Delay (uint32_t T);
uint32_t GetTick(void);

#endif /* __STM32L476G_DISCOVERY_SYSTICK_H */
