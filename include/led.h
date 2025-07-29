#ifndef __LED_H__
#define __LED_H__

#define LED0_PIN 12 // PB12
#define LED1_PIN 13 // PB13
#define LED2_PIN 14 // PB14
#define LED3_PIN 15 // PB15
#define LED4_PIN 0 // PC0
#define LED5_PIN 1 // PC1
#define LED6_PIN 2 // PC2
#define LED7_PIN 3 // PC3

void Led_Initialize(void);
void Led_display(int value);
#endif
