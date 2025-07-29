#include "stm32f446xx.h"
#include "main.h"
#include "buzzer.h"
#include "util.h"

#define BUZZER_PIN 15         // BUZZER? ??? ? ??: PA15
#define BUZZER_GPIO GPIOA     // BUZZER? ??? GPIO ??: GPIOA

void Buzzer_Init(void) {
    
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

 
    BUZZER_GPIO->MODER &= ~(3UL << (2 * BUZZER_PIN)); 
    BUZZER_GPIO->MODER |= (2UL << (2 * BUZZER_PIN));  
    BUZZER_GPIO->OTYPER &= ~(1UL << BUZZER_PIN);      // Push-pull
    BUZZER_GPIO->PUPDR &= ~(3UL << (2 * BUZZER_PIN)); // Pull-up, Pull-down 
		
	  BUZZER_GPIO->AFR[1] &=  ~((uint32_t)0xF << (4 * (BUZZER_PIN - 8))); // Clear existing alternate function bits
		BUZZER_GPIO->AFR[1] |= ((uint32_t)0x1 << (4 * (BUZZER_PIN - 8))); 
	/*  
	if (BUZZER_PIN >= 8 && BUZZER_PIN <= 15) {
      
        uint32_t shift_amount = (BUZZER_PIN - 8) * 4;
        if (shift_amount < 32) { 
            BUZZER_GPIO->AFR[1] &= ~(0xF << shift_amount); 
            BUZZER_GPIO->AFR[1] |= (0x1 << shift_amount);  
        }
    } else if (BUZZER_PIN < 8) {
        
        uint32_t shift_amount = BUZZER_PIN * 4;
        if (shift_amount < 32) { 
            BUZZER_GPIO->AFR[0] &= ~(0xF << shift_amount); 
            BUZZER_GPIO->AFR[0] |= (0x1 << shift_amount);  
        }
			}
  */
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

   
    TIM2->PSC = 90 - 1;         
    TIM2->ARR = 1000 - 1;        
    TIM2->CCR1 = 500;            
    TIM2->CCMR1 &= ~(TIM_CCMR1_OC1M); 
		TIM2->CCMR1 |= (6UL << TIM_CCMR1_OC1M_Pos);
    TIM2->CCMR1 |= TIM_CCMR1_OC1PE; 
    TIM2->CCER |= TIM_CCER_CC1E;  

    Buzzer_Off(); 
   // TIM2->CR1 |= TIM_CR1_CEN;
}
		
void Buzzer_SetFrequency(uint32_t frequency) {
   
    uint32_t timerClock = 180000000 / 90; 
    uint32_t period = timerClock / frequency;

    TIM2->ARR = period - 1; 
    TIM2->CCR1 = period / 2; 
}


void Buzzer_On(void) {
     TIM2->CR1 |= TIM_CR1_CEN; 
}

void Buzzer_Off(void) {
			
			TIM2->CR1 &= ~TIM_CR1_CEN; 
			
		
}

