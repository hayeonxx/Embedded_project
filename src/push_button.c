#include "main.h"
#include "push_button.h"

void pb_initialize(void)
{
	//////////////////////////////////////
	// GPIO Configure
  //////////////////////////////////////
	
  // Enable the clock to GPIO Port A & D
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIODEN;

	SW1_GPIO_Port->MODER &= ~(3UL << (2*SW1_Pin));  
	SW1_GPIO_Port->PUPDR &= ~(3UL << (2*SW1_Pin)); 
	
	SW2_GPIO_Port->MODER &= ~(3UL << (2*SW2_Pin));  
	SW2_GPIO_Port->PUPDR &= ~(3UL << (2*SW2_Pin)); 
}

void pb_interrupt_init(void)
{
	// for PC13
	// GPIOC->PUPDR |= 2U << (2*13);    	
	/*
  NVIC_EnableIRQ(EXTI15_10_IRQn); // Enable Interrupt
	// Connect External Line to the GPI
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13; 
  SYSCFG->EXTICR[3] |=  SYSCFG_EXTICR4_EXTI13_PC; 
  // Falling trigger selection
  // 0 = trigger disabled, 1 = trigger enabled
  EXTI->FTSR |= EXTI_FTSR_TR13;  

  // Interrupt Mask Register
  // 0 = marked, 1 = not masked (enabled)
  EXTI->IMR  |= EXTI_IMR_IM13;
	*/
	
	
	// for PD2
	NVIC_EnableIRQ(EXTI2_IRQn); // Enable Interrupt
  // Connect External Line to the GPI
  	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI2; 
  	SYSCFG->EXTICR[0] |=  SYSCFG_EXTICR1_EXTI2_PD; 
	EXTI->FTSR |= EXTI_FTSR_TR2;
	EXTI->IMR  |= EXTI_IMR_IM2;  
	
	
	// for PA4
	NVIC_EnableIRQ(EXTI4_IRQn); // Enable Interrupt
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI4; 
  	SYSCFG->EXTICR[1] |=  SYSCFG_EXTICR2_EXTI4_PA; 
	EXTI->FTSR |= EXTI_FTSR_TR4;
	EXTI->IMR  |= EXTI_IMR_IM4;  
	
}
