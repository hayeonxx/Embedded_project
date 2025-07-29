#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f446xx.h"


#define GPIO_BSRR_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_BSRR_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_BSRR_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_BSRR_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_BSRR_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_BSRR_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_BSRR_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_BSRR_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_BSRR_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_BSRR_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_BSRR_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_BSRR_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_BSRR_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_BSRR_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_BSRR_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_BSRR_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_BSRR_PIN_All               ((uint16_t)0xFFFF)  /* All pins selected */


#define GPIO_PIN_0                 0
#define GPIO_PIN_1                 1
#define GPIO_PIN_2                 2
#define GPIO_PIN_3                 3
#define GPIO_PIN_4                 4
#define GPIO_PIN_5                 5
#define GPIO_PIN_6                 6
#define GPIO_PIN_7                 7
#define GPIO_PIN_8                 8
#define GPIO_PIN_9                 9
#define GPIO_PIN_10                10
#define GPIO_PIN_11                11
#define GPIO_PIN_12                12
#define GPIO_PIN_13                13
#define GPIO_PIN_14                14
#define GPIO_PIN_15                15

// LED

#define LED0_Pin GPIO_PIN_12
#define LED0_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_13
#define LED1_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_14
#define LED2_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_15
#define LED3_GPIO_Port GPIOB

#define LED4_Pin GPIO_PIN_0
#define LED4_GPIO_Port GPIOC
#define LED5_Pin GPIO_PIN_1
#define LED5_GPIO_Port GPIOC
#define LED6_Pin GPIO_PIN_2
#define LED6_GPIO_Port GPIOC
#define LED7_Pin GPIO_PIN_3
#define LED7_GPIO_Port GPIOC

// 7-SEGMENT

#define FND0_GPIO_Port GPIOB
#define FND1_GPIO_Port GPIOB
#define FND2_GPIO_Port GPIOB
#define FND3_GPIO_Port GPIOB
#define FND4_GPIO_Port GPIOB
#define FND5_GPIO_Port GPIOB
#define FND6_GPIO_Port GPIOB
#define FND7_GPIO_Port GPIOB

#define FND_SEL0_GPIO_Port GPIOA
#define FND_SEL1_GPIO_Port GPIOA
#define FND_SEL2_GPIO_Port GPIOC
#define FND_SEL3_GPIO_Port		LED7_GPIO_Port

#define FND0_Pin GPIO_PIN_0
#define FND1_Pin GPIO_PIN_1
#define FND2_Pin GPIO_PIN_2
#define FND3_Pin GPIO_PIN_3
#define FND4_Pin GPIO_PIN_4
#define FND5_Pin GPIO_PIN_5
#define FND6_Pin GPIO_PIN_6
#define FND7_Pin GPIO_PIN_7

#define FND_SEL0_Pin GPIO_PIN_10
#define FND_SEL1_Pin GPIO_PIN_11
#define FND_SEL2_Pin GPIO_PIN_4
#define FND_SEL3_Pin			LED7_Pin

#define FND0_BSRR_Pin GPIO_BSRR_PIN_0
#define FND1_BSRR_Pin GPIO_BSRR_PIN_1
#define FND2_BSRR_Pin GPIO_BSRR_PIN_2
#define FND3_BSRR_Pin GPIO_BSRR_PIN_3
#define FND4_BSRR_Pin GPIO_BSRR_PIN_4
#define FND5_BSRR_Pin GPIO_BSRR_PIN_5
#define FND6_BSRR_Pin GPIO_BSRR_PIN_6
#define FND7_BSRR_Pin GPIO_BSRR_PIN_7

#define FND_SEL0_BSRR_Pin GPIO_BSRR_PIN_10
#define FND_SEL1_BSRR_Pin GPIO_BSRR_PIN_11
#define FND_SEL2_BSRR_Pin GPIO_BSRR_PIN_4
#define FND_SEL3_BSRR_Pin	GPIO_BSRR_PIN_3


// PUSH BUTTON

// TM75A(I2C Temp Sensor)
#define TEMP_SDA_Pin GPIO_PIN_9
#define TEMP_SDA_Port GPIOB

#define TEMP_SCL_Pin GPIO_PIN_8
#define TEMP_SCL_Port GPIOB

#define LM75A_ADDR 0x4c
#define AIN2_Pin GPIO_PIN_13
#define AIN2_GPIO_Port GPIOC

#define SPI1_NCS_Pin GPIO_PIN_1
#define SPI1_NCS_GPIO_Port GPIOA
#define USART2_TX_Pin GPIO_PIN_2
#define USART2_TX_GPIO_Port GPIOA
#define USART2_RX_Pin GPIO_PIN_3
#define USART2_RX_GPIO_Port GPIOA
#define SW2_Pin GPIO_PIN_4
#define SW2_GPIO_Port GPIOA
#define LCD4_Pin GPIO_PIN_5
#define LCD4_GPIO_Port GPIOC

#define BIN1_Pin GPIO_PIN_10
#define BIN1_GPIO_Port GPIOB

#define LCD_D5_Pin GPIO_PIN_6
#define LCD_D5_GPIO_Port GPIOC
#define LCD_D6_Pin GPIO_PIN_7
#define LCD_D6_GPIO_Port GPIOC
#define LCD_D7_Pin GPIO_PIN_8
#define LCD_D7_GPIO_Port GPIOC
#define LCD_RS_Pin GPIO_PIN_9
#define LCD_RS_GPIO_Port GPIOC
#define PWMA_Pin GPIO_PIN_8
#define PWMA_GPIO_Port GPIOA
#define PWMB_Pin GPIO_PIN_9
#define PWMB_GPIO_Port GPIOA

#define LCD_E_Pin GPIO_PIN_12
#define LCD_E_GPIO_Port GPIOA
#define AIN1_Pin GPIO_PIN_13
#define AIN1_GPIO_Port GPIOA
#define BUZZER_Pin GPIO_PIN_15
#define BUZZER_GPIO_Port GPIOA
#define BIN2_Pin GPIO_PIN_12
#define BIN2_GPIO_Port GPIOC
#define SW1_Pin GPIO_PIN_2
#define SW1_GPIO_Port GPIOD

#define BufferSize 32

#define idle    0
#define mode1		1

#define go		  4
#define stop		5
#define reset		6
#define paused		7

#define emergency_mode 9
#define idle_r  			20

extern volatile uint8_t digit3, digit2, digit1, digit0;
extern volatile uint16_t segment_counter, led_counter;
extern volatile int led;
extern volatile uint16_t stop_time;
extern volatile int i;
extern volatile int state;
extern uint8_t USART2_Buffer_Rx[BufferSize];
extern uint32_t Rx2_Counter;
extern uint8_t newline_flag;

#endif /* __MAIN_H */
