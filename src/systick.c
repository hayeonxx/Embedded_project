
#include "systick.h"
#include "main.h"
#include "fnd.h"
#include "led.h"

volatile uint32_t msTicks;
volatile uint32_t cnt;
volatile uint32_t sec_cnt;
//******************************************************************************************
// Initialize SysTick	
//******************************************************************************************	
void SysTick_Init(void){
	// The RCC feeds the Cortex System Timer (SysTick) external clock with the AHB clock
	// (HCLK) divided by 8. The SysTick can work either with this clock or with the Cortex clock
	// (HCLK), configurable in the SysTick Control and Status Register.
	
	//  SysTick Control and Status Register
	SysTick->CTRL = 0;										// Disable SysTick IRQ and SysTick Counter
	
	// SysTick Reload Value Register
	SysTick->LOAD = (180000000)/1000 - 1;    // 1ms, Default clock
	//SysTick->LOAD = (180000000/8)/1000 - 1;    // 1ms, Default clock
	
	// SysTick Current Value Register
	SysTick->VAL = 0;

	NVIC_SetPriority(SysTick_IRQn, 1);		// Set Priority to 1
	NVIC_EnableIRQ(SysTick_IRQn);					// Enable EXTI0_1 interrupt in NVIC

	// Enables SysTick exception request
	// 1 = counting down to zero asserts the SysTick exception request
	// 0 = counting down to zero does not assert the SysTick exception request
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
	
	// Select processor clock
	// 1 = HCLK;  0 = HCLK/8
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;		
	//SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;		
	
	// Enable SysTick IRQ and SysTick Timer
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

//******************************************************************************************
// SysTick Interrupt Handler
//******************************************************************************************


// void SysTick_Handler(void){
// 	msTicks++;
// }
void SysTick_Handler(void){

	if(state == mode1 || state == go || state == stop || state == reset || state == paused || state == emergency_mode)
	{
	msTicks++;
	switch (msTicks % 4) {
		case 0: {
			Fnd_Display(digit3, 3, 0); break;
		}
		case 1: {
			Fnd_Display(digit2, 2, 0); break;
		}
		case 2: {
			Fnd_Display_dp(digit1, 1, 0); break;
		}
		case 3: {
			Fnd_Display(digit0, 0, 0); break;
		}
		default: ;
	}
	}
	
	
	else{
	msTicks++;
	switch (msTicks % 4) {
		case 0: {
			Fnd_Display(digit3, 3, 0); break;
		}
		case 1: {
			Fnd_Display(digit2, 2, 0); break;
		}
		case 2: {
			Fnd_Display(digit1, 1, 0); break;
		}
		case 3: {
			Fnd_Display(digit0, 0, 0); break;
		}
		default: ;
	}
	}

}	
//******************************************************************************************
// Delay in ms
//******************************************************************************************
void SysTick_Delay (uint32_t T)
{
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < T);
	
	msTicks = 0;
}

uint32_t GetTick(void)
{
	return msTicks;
}
