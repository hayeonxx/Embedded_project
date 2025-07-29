#include "led.h"
#include "main.h"

void Led_Initialize(void)
{
	//////////////////////////////////////
	// GPIO Configure
  //////////////////////////////////////
	
  // Enable the clock to GPIO Port B	
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
		
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	GPIOB->MODER &= ~( 3UL<<(2*LED0_PIN) | 3UL<<(2*LED1_PIN) | 3UL<<(2*LED2_PIN) |3UL<<(2*LED3_PIN) );  
	GPIOB->MODER |=  ( 1UL<<(2*LED0_PIN)) | (1UL<<(2*LED1_PIN)) | (1UL<<(2*LED2_PIN)) | (1UL<<(2*LED3_PIN));      // Output(01)
	
	//// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	GPIOB->OTYPER &= ~( 1<<LED0_PIN | 1<<LED1_PIN | 1<<LED2_PIN | 1<<LED3_PIN);      // Push-pull
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	GPIOB->OSPEEDR &= ~( 3UL<<(2*LED0_PIN) | 3UL<<(2*LED1_PIN) | 3UL<<(2*LED2_PIN) | 3UL<<(2*LED3_PIN) );
	GPIOB->OSPEEDR |=    2UL<<(2*LED0_PIN) | 2UL<<(2*LED1_PIN) | 2UL<<(2*LED2_PIN) | 2UL<<(2*LED3_PIN);  // Fast speed
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIOB->PUPDR  &= ~( 3UL<<(2*LED0_PIN) | 3UL<<(2*LED1_PIN) | 3UL<<(2*LED2_PIN) | 3UL<<(2*LED3_PIN));  // No pull-up, no pull-down
	
	// Enable the clock to GPIO Port C
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
		
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	GPIOC->MODER &= ~( 3UL<<(2*LED4_PIN) | 3UL<<(2*LED5_PIN) | 3UL<<(2*LED6_PIN) | 3UL<<(2*LED7_PIN) );  
	GPIOC->MODER |=   (1UL<<(2*LED4_PIN) | 1UL<<(2*LED5_PIN) | 1UL<<(2*LED6_PIN) | 1UL<<(2*LED7_PIN) ) ;      // Output(01)
	
	//// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	GPIOC->OTYPER &= ~( 1<<LED4_PIN | 1<<LED5_PIN | 1<<LED6_PIN | 1<<LED7_PIN);      // Push-pull
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	GPIOC->OSPEEDR &= ~( 3UL<<(2*LED4_PIN) | 3UL<<(2*LED5_PIN) | 3UL<<(2*LED6_PIN) | 3UL<<(2*LED7_PIN) );
	GPIOC->OSPEEDR |=    (2UL<<(2*LED4_PIN)| 2UL<<(2*LED5_PIN) | 2UL<<(2*LED6_PIN) | 2UL<<(2*LED7_PIN)) ;  // Fast speed
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIOC->PUPDR  &= ~( 3UL<<(2*LED4_PIN) | 3UL<<(2*LED5_PIN) | 3UL<<(2*LED6_PIN) | 3UL<<(2*LED7_PIN));  // No pull-up, no pull-down
}

void Led_display(int value)
{
	if((value & 0x01) == 0x01)
			GPIOB->ODR |= (1 << LED0_PIN);	//set
	else	
			GPIOB->ODR &= ~(1 << LED0_PIN);	//clear

	if((value & 0x02) == 0x02)
			GPIOB->ODR |= (1 << LED1_PIN);	//set
	else	
			GPIOB->ODR &= ~(1 << LED1_PIN);	//clear
	
	if((value & 0x04) == 0x04)
			GPIOB->ODR |= (1 << LED2_PIN);	//set
	else	
			GPIOB->ODR &= ~(1 << LED2_PIN);	//clear

	if((value & 0x08) == 0x08)
			GPIOB->ODR |= (1 << LED3_PIN);	//set
	else	
			GPIOB->ODR &= ~(1 << LED3_PIN);	//clear

	if((value & 0x10) == 0x10)
			GPIOC->ODR |= (1 << LED4_PIN);	//set
	else	
			GPIOC->ODR &= ~(1 << LED4_PIN);	//clear

	if((value & 0x20) == 0x20)
			GPIOC->ODR |= (1 << LED5_PIN);	//set
	else	
			GPIOC->ODR &= ~(1 << LED5_PIN);	//clear
	
	if((value & 0x40) == 0x40)
			GPIOC->ODR |= (1 << LED6_PIN);	//set
	else	
			GPIOC->ODR &= ~(1 << LED6_PIN);	//clear

	if((value & 0x80) == 0x80)
			GPIOC->ODR |= (1 << LED7_PIN);	//set
	else	
			GPIOC->ODR &= ~(1 << LED7_PIN);	//clear
}
