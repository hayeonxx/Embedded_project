/*
 * fnd.c
 *
 *  Created on: 2020. 2. 26.
 *      Author: isjeon
 */

#include "main.h"
#include "util.h"
#include "led.h"
#include "systick.h"

int8_t number[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x27, 0x7f, 0x6f};
int8_t number_dp[] = {0xbf, 0x86, 0xdb, 0xcf, 0xe6, 0xed, 0xfd, 0xa7, 0xff, 0xef};

void Fnd_Initialize(void)
{
	// Enable the clock to GPIO Port B	
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN;
	
	// FND0
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	FND0_GPIO_Port->MODER &= ~( 3UL<<(2*FND0_Pin) );
	FND0_GPIO_Port->MODER |=  ( 1UL<<(2*FND0_Pin) );
	
	//// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	FND0_GPIO_Port->OTYPER &= ~( 1<<FND0_Pin );
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	FND0_GPIO_Port->OSPEEDR &= ~( 3UL<<(2*FND0_Pin) );
	FND0_GPIO_Port->OSPEEDR |=    2UL<<(2*FND0_Pin)  ;  // Fast speed
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	FND0_GPIO_Port->PUPDR  &= ~ ( 3UL<<(2*FND0_Pin) );  // No pull-up, no pull-down
	
	// FND1
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	FND1_GPIO_Port->MODER &= ~( 3UL<<(2*FND1_Pin) );
	FND1_GPIO_Port->MODER |=  ( 1UL<<(2*FND1_Pin) );
	
	//// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	FND1_GPIO_Port->OTYPER &= ~( 1<<FND1_Pin );
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	FND1_GPIO_Port->OSPEEDR &= ~( 3UL<<(2*FND1_Pin) );
	FND1_GPIO_Port->OSPEEDR |=    2UL<<(2*FND1_Pin)  ;  // Fast speed
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	FND1_GPIO_Port->PUPDR  &= ~ ( 3UL<<(2*FND1_Pin) );  // No pull-up, no pull-down
	

	// FND2
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	FND2_GPIO_Port->MODER &= ~( 3UL<<(2*FND2_Pin) );
	FND2_GPIO_Port->MODER |=  ( 1UL<<(2*FND2_Pin) );
	
	//// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	FND2_GPIO_Port->OTYPER &= ~( 1<<FND2_Pin );
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	FND2_GPIO_Port->OSPEEDR &= ~( 3UL<<(2*FND2_Pin) );
	FND2_GPIO_Port->OSPEEDR |=    2UL<<(2*FND2_Pin)  ;  // Fast speed
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	FND2_GPIO_Port->PUPDR  &= ~ ( 3UL<<(2*FND2_Pin) );  // No pull-up, no pull-down

	// FND3
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	FND3_GPIO_Port->MODER &= ~( 3UL<<(2*FND3_Pin) );
	FND3_GPIO_Port->MODER |=  ( 1UL<<(2*FND3_Pin) );
	
	//// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	FND3_GPIO_Port->OTYPER &= ~( 1<<FND3_Pin );
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	FND3_GPIO_Port->OSPEEDR &= ~( 3UL<<(2*FND3_Pin) );
	FND3_GPIO_Port->OSPEEDR |=    2UL<<(2*FND3_Pin)  ;  // Fast speed
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	FND3_GPIO_Port->PUPDR  &= ~ ( 3UL<<(2*FND3_Pin) );  // No pull-up, no pull-down

	// FND4
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	FND4_GPIO_Port->MODER &= ~( 3UL<<(2*FND4_Pin) );
	FND4_GPIO_Port->MODER |=  ( 1UL<<(2*FND4_Pin) );
	
	//// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	FND4_GPIO_Port->OTYPER &= ~( 1<<FND4_Pin );
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	FND4_GPIO_Port->OSPEEDR &= ~( 3UL<<(2*FND4_Pin) );
	FND4_GPIO_Port->OSPEEDR |=    2UL<<(2*FND4_Pin)  ;  // Fast speed
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	FND4_GPIO_Port->PUPDR  &= ~ ( 3UL<<(2*FND4_Pin) );  // No pull-up, no pull-down


	// FND5
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	FND5_GPIO_Port->MODER &= ~( 3UL<<(2*FND5_Pin) );
	FND5_GPIO_Port->MODER |=  ( 1UL<<(2*FND5_Pin) );
	
	//// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	FND5_GPIO_Port->OTYPER &= ~( 1<<FND5_Pin );
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	FND5_GPIO_Port->OSPEEDR &= ~( 3UL<<(2*FND5_Pin) );
	FND5_GPIO_Port->OSPEEDR |=    2UL<<(2*FND5_Pin)  ;  // Fast speed
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	FND5_GPIO_Port->PUPDR  &= ~ ( 3UL<<(2*FND5_Pin) );  // No pull-up, no pull-down
	
	// FND6
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	FND6_GPIO_Port->MODER &= ~( 3UL<<(2*FND6_Pin) );
	FND6_GPIO_Port->MODER |=  ( 1UL<<(2*FND6_Pin) );
	
	//// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	FND6_GPIO_Port->OTYPER &= ~( 1<<FND6_Pin );
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	FND6_GPIO_Port->OSPEEDR &= ~( 3UL<<(2*FND6_Pin) );
	FND6_GPIO_Port->OSPEEDR |=    2UL<<(2*FND6_Pin)  ;  // Fast speed
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	FND6_GPIO_Port->PUPDR  &= ~ ( 3UL<<(2*FND6_Pin) );  // No pull-up, no pull-down	

	// FND7
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	FND7_GPIO_Port->MODER &= ~( 3UL<<(2*FND7_Pin) );
	FND7_GPIO_Port->MODER |=  ( 1UL<<(2*FND7_Pin) );
	
	//// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	FND7_GPIO_Port->OTYPER &= ~( 1<<FND7_Pin );
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	FND7_GPIO_Port->OSPEEDR &= ~( 3UL<<(2*FND7_Pin) );
	FND7_GPIO_Port->OSPEEDR |=    2UL<<(2*FND7_Pin)  ;  // Fast speed
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	FND7_GPIO_Port->PUPDR  &= ~ ( 3UL<<(2*FND7_Pin) );  // No pull-up, no pull-down	

	// FND_SEL0
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	FND_SEL0_GPIO_Port->MODER &= ~( 3UL<<(2*FND_SEL0_Pin) );
	FND_SEL0_GPIO_Port->MODER |=  ( 1UL<<(2*FND_SEL0_Pin) );
	
	//// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	FND_SEL0_GPIO_Port->OTYPER &= ~( 1<<FND_SEL0_Pin );
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	FND_SEL0_GPIO_Port->OSPEEDR &= ~( 3UL<<(2*FND_SEL0_Pin) );
	FND_SEL0_GPIO_Port->OSPEEDR |=    2UL<<(2*FND_SEL0_Pin)  ;  // Fast speed
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	FND_SEL0_GPIO_Port->PUPDR  &= ~ ( 3UL<<(2*FND_SEL0_Pin) );  // No pull-up, no pull-down	


	// FND_SEL1
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	FND_SEL1_GPIO_Port->MODER &= ~( 3UL<<(2*FND_SEL1_Pin) );
	FND_SEL1_GPIO_Port->MODER |=  ( 1UL<<(2*FND_SEL1_Pin) );
	
	//// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	FND_SEL1_GPIO_Port->OTYPER &= ~( 1<<FND_SEL1_Pin );
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	FND_SEL1_GPIO_Port->OSPEEDR &= ~( 3UL<<(2*FND_SEL1_Pin) );
	FND_SEL1_GPIO_Port->OSPEEDR |=    2UL<<(2*FND_SEL1_Pin)  ;  // Fast speed
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	FND_SEL1_GPIO_Port->PUPDR  &= ~ ( 3UL<<(2*FND_SEL1_Pin) );  // No pull-up, no pull-down	


	// FND_SEL2
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	FND_SEL2_GPIO_Port->MODER &= ~( 3UL<<(2*FND_SEL2_Pin) );
	FND_SEL2_GPIO_Port->MODER |=  ( 1UL<<(2*FND_SEL2_Pin) );
	
	//// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	FND_SEL2_GPIO_Port->OTYPER &= ~( 1<<FND_SEL2_Pin );
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	FND_SEL2_GPIO_Port->OSPEEDR &= ~( 3UL<<(2*FND_SEL2_Pin) );
	FND_SEL2_GPIO_Port->OSPEEDR |=    2UL<<(2*FND_SEL2_Pin)  ;  // Fast speed
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	FND_SEL2_GPIO_Port->PUPDR  &= ~ ( 3UL<<(2*FND_SEL2_Pin) );  // No pull-up, no pull-down	


	// FND_SEL3
	// GPIO Mode: Input(00), Output(01), AlterFunc(10), Analog(11, reset)
	FND_SEL3_GPIO_Port->MODER &= ~( 3UL<<(2*FND_SEL3_Pin) );
	FND_SEL3_GPIO_Port->MODER |=  ( 1UL<<(2*FND_SEL3_Pin) );
	
	//// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	FND_SEL3_GPIO_Port->OTYPER &= ~( 1<<FND_SEL3_Pin );
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	FND_SEL3_GPIO_Port->OSPEEDR &= ~( 3UL<<(2*FND_SEL3_Pin) );
	FND_SEL3_GPIO_Port->OSPEEDR |=    2UL<<(2*FND_SEL3_Pin)  ;  // Fast speed
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	FND_SEL3_GPIO_Port->PUPDR  &= ~ ( 3UL<<(2*FND_SEL3_Pin) );  // No pull-up, no pull-down	
}

void Fnd_Self_Test(void)
{
	 static int fnd_sel = 0;
		int i;

		for(fnd_sel = 0 ; fnd_sel < 4 ; fnd_sel ++)
		{
			switch(fnd_sel)
			{
				case 0 :
						FND_SEL0_GPIO_Port->BSRR = FND_SEL0_BSRR_Pin;
						FND_SEL1_GPIO_Port->BSRR  = FND_SEL1_BSRR_Pin << 16;
						FND_SEL2_GPIO_Port->BSRR  = FND_SEL2_BSRR_Pin << 16;
						FND_SEL3_GPIO_Port->BSRR  = FND_SEL3_BSRR_Pin << 16;
						break;
				case 1 :
						FND_SEL0_GPIO_Port->BSRR  = FND_SEL0_BSRR_Pin << 16;
						FND_SEL1_GPIO_Port->BSRR  = FND_SEL1_BSRR_Pin;
						FND_SEL2_GPIO_Port->BSRR  = FND_SEL2_BSRR_Pin << 16;
						FND_SEL3_GPIO_Port->BSRR  = FND_SEL3_BSRR_Pin << 16;
						break;
				case 2 :
						FND_SEL0_GPIO_Port->BSRR  = FND_SEL0_BSRR_Pin << 16;
						FND_SEL1_GPIO_Port->BSRR  = FND_SEL1_BSRR_Pin << 16;
						FND_SEL2_GPIO_Port->BSRR  = FND_SEL2_BSRR_Pin;
						FND_SEL3_GPIO_Port->BSRR  = FND_SEL3_BSRR_Pin << 16;
						break;
				case 3 :
						FND_SEL0_GPIO_Port->BSRR  = FND_SEL0_BSRR_Pin << 16;
						FND_SEL1_GPIO_Port->BSRR  = FND_SEL1_BSRR_Pin << 16;
						FND_SEL2_GPIO_Port->BSRR  = FND_SEL2_BSRR_Pin << 16;
						FND_SEL3_GPIO_Port->BSRR  = FND_SEL3_BSRR_Pin;
						break;
				}
				for( i = 0 ; i < 8 ; i ++)
				{
						GPIOB->ODR = (1 << i); // PB0~PB7
						// HAL_Delay(100);  // 100ms
						SysTick_Delay(10);
				}
		}
		FND_SEL0_GPIO_Port->BSRR  = FND_SEL0_BSRR_Pin<< 16;
		FND_SEL1_GPIO_Port->BSRR  = FND_SEL1_BSRR_Pin<< 16;
		FND_SEL2_GPIO_Port->BSRR  = FND_SEL2_BSRR_Pin<< 16;
		FND_SEL3_GPIO_Port->BSRR  = FND_SEL3_BSRR_Pin<< 16;
}

void Fnd_Display(int8_t num, int8_t position, uint32_t time_ms)
{
	int32_t i;
	
	switch (position)
	{
				case 0 :
						FND_SEL0_GPIO_Port->BSRR = FND_SEL0_BSRR_Pin;
						FND_SEL1_GPIO_Port->BSRR  = FND_SEL1_BSRR_Pin << 16;
						FND_SEL2_GPIO_Port->BSRR  = FND_SEL2_BSRR_Pin << 16;
						FND_SEL3_GPIO_Port->BSRR  = FND_SEL3_BSRR_Pin << 16;
						break;
				case 1 :
						FND_SEL0_GPIO_Port->BSRR  = FND_SEL0_BSRR_Pin << 16;
						FND_SEL1_GPIO_Port->BSRR  = FND_SEL1_BSRR_Pin;
						FND_SEL2_GPIO_Port->BSRR  = FND_SEL2_BSRR_Pin << 16;
						FND_SEL3_GPIO_Port->BSRR  = FND_SEL3_BSRR_Pin << 16;
						break;
				case 2 :
						FND_SEL0_GPIO_Port->BSRR  = FND_SEL0_BSRR_Pin << 16;
						FND_SEL1_GPIO_Port->BSRR  = FND_SEL1_BSRR_Pin << 16;
						FND_SEL2_GPIO_Port->BSRR  = FND_SEL2_BSRR_Pin;
						FND_SEL3_GPIO_Port->BSRR  = FND_SEL3_BSRR_Pin << 16;
						break;
				case 3 :
						FND_SEL0_GPIO_Port->BSRR  = FND_SEL0_BSRR_Pin << 16;
						FND_SEL1_GPIO_Port->BSRR  = FND_SEL1_BSRR_Pin << 16;
						FND_SEL2_GPIO_Port->BSRR  = FND_SEL2_BSRR_Pin << 16;
						FND_SEL3_GPIO_Port->BSRR  = FND_SEL3_BSRR_Pin;
						break;
	}
	
	for (i=0;i<8;i++) {
		if ((number[num] & (1<<i)) != 0) {
			switch (i)
			{
				case 0: FND0_GPIO_Port->BSRR = FND0_BSRR_Pin; break;
				case 1: FND1_GPIO_Port->BSRR = FND1_BSRR_Pin; break;
				case 2: FND2_GPIO_Port->BSRR = FND2_BSRR_Pin; break;
				case 3: FND3_GPIO_Port->BSRR = FND3_BSRR_Pin; break;
				case 4: FND4_GPIO_Port->BSRR = FND4_BSRR_Pin; break;
				case 5: FND5_GPIO_Port->BSRR = FND5_BSRR_Pin; break;
				case 6: FND6_GPIO_Port->BSRR = FND6_BSRR_Pin; break;
				case 7: FND7_GPIO_Port->BSRR = FND7_BSRR_Pin; break;
			}
		}
		else {
			switch (i)
			{
				case 0: FND0_GPIO_Port->BSRR = FND0_BSRR_Pin << 16; break;
				case 1: FND1_GPIO_Port->BSRR = FND1_BSRR_Pin << 16; break;
				case 2: FND2_GPIO_Port->BSRR = FND2_BSRR_Pin << 16; break;
				case 3: FND3_GPIO_Port->BSRR = FND3_BSRR_Pin << 16; break;
				case 4: FND4_GPIO_Port->BSRR = FND4_BSRR_Pin << 16; break;
				case 5: FND5_GPIO_Port->BSRR = FND5_BSRR_Pin << 16; break;
				case 6: FND6_GPIO_Port->BSRR = FND6_BSRR_Pin << 16; break;
				case 7: FND7_GPIO_Port->BSRR = FND7_BSRR_Pin << 16; break;
			}
		}
	}
	
	if(time_ms !=0)
		SysTick_Delay(time_ms);
}

void Fnd_Display_dp(int8_t num, int8_t position, uint32_t time_ms)
{
	int32_t i;
	
	switch (position)
	{
				case 0 :
						FND_SEL0_GPIO_Port->BSRR = FND_SEL0_BSRR_Pin;
						FND_SEL1_GPIO_Port->BSRR  = FND_SEL1_BSRR_Pin << 16;
						FND_SEL2_GPIO_Port->BSRR  = FND_SEL2_BSRR_Pin << 16;
						FND_SEL3_GPIO_Port->BSRR  = FND_SEL3_BSRR_Pin << 16;
						break;
				case 1 :
						FND_SEL0_GPIO_Port->BSRR  = FND_SEL0_BSRR_Pin << 16;
						FND_SEL1_GPIO_Port->BSRR  = FND_SEL1_BSRR_Pin;
						FND_SEL2_GPIO_Port->BSRR  = FND_SEL2_BSRR_Pin << 16;
						FND_SEL3_GPIO_Port->BSRR  = FND_SEL3_BSRR_Pin << 16;
						break;
				case 2 :
						FND_SEL0_GPIO_Port->BSRR  = FND_SEL0_BSRR_Pin << 16;
						FND_SEL1_GPIO_Port->BSRR  = FND_SEL1_BSRR_Pin << 16;
						FND_SEL2_GPIO_Port->BSRR  = FND_SEL2_BSRR_Pin;
						FND_SEL3_GPIO_Port->BSRR  = FND_SEL3_BSRR_Pin << 16;
						break;
				case 3 :
						FND_SEL0_GPIO_Port->BSRR  = FND_SEL0_BSRR_Pin << 16;
						FND_SEL1_GPIO_Port->BSRR  = FND_SEL1_BSRR_Pin << 16;
						FND_SEL2_GPIO_Port->BSRR  = FND_SEL2_BSRR_Pin << 16;
						FND_SEL3_GPIO_Port->BSRR  = FND_SEL3_BSRR_Pin;
						break;
	}
	
	for (i=0;i<8;i++) {
		if ((number_dp[num] & (1<<i)) != 0) {
			switch (i)
			{
				case 0: FND0_GPIO_Port->BSRR = FND0_BSRR_Pin; break;
				case 1: FND1_GPIO_Port->BSRR = FND1_BSRR_Pin; break;
				case 2: FND2_GPIO_Port->BSRR = FND2_BSRR_Pin; break;
				case 3: FND3_GPIO_Port->BSRR = FND3_BSRR_Pin; break;
				case 4: FND4_GPIO_Port->BSRR = FND4_BSRR_Pin; break;
				case 5: FND5_GPIO_Port->BSRR = FND5_BSRR_Pin; break;
				case 6: FND6_GPIO_Port->BSRR = FND6_BSRR_Pin; break;
				case 7: FND7_GPIO_Port->BSRR = FND7_BSRR_Pin; break;
			}
		}
		else {
			switch (i)
			{
				case 0: FND0_GPIO_Port->BSRR = FND0_BSRR_Pin << 16; break;
				case 1: FND1_GPIO_Port->BSRR = FND1_BSRR_Pin << 16; break;
				case 2: FND2_GPIO_Port->BSRR = FND2_BSRR_Pin << 16; break;
				case 3: FND3_GPIO_Port->BSRR = FND3_BSRR_Pin << 16; break;
				case 4: FND4_GPIO_Port->BSRR = FND4_BSRR_Pin << 16; break;
				case 5: FND5_GPIO_Port->BSRR = FND5_BSRR_Pin << 16; break;
				case 6: FND6_GPIO_Port->BSRR = FND6_BSRR_Pin << 16; break;
				case 7: FND7_GPIO_Port->BSRR = FND7_BSRR_Pin << 16; break;
			}
		}
	}
	
	if(time_ms !=0)
		SysTick_Delay(time_ms);
}

void Fnd_Zero(void)
{
	digit3 = 0;
	digit2 = 0;
	digit1 = 0;
	digit0 = 0;
}

void fnd_look(int count)
{
	digit3 = count / 1000;
	digit2 = (count % 1000) / 100;
	digit1 = (count % 100) / 10;
	digit0 = count % 10;
}




void fnd_second(int T)
{
	digit3 = segment_counter / 1000;
	digit2 = (segment_counter % 1000) / 100;
	digit1 = (segment_counter % 100) / 10;
	digit0 = segment_counter % 10;
	SysTick_Delay(T);
}







