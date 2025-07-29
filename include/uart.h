/*----------------------------------------------------------------------------
 * Name:    Serial.h
 * Purpose: Low level serial definitions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2014 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#ifndef __UART_H__
#define __UART_H__

#include "main.h"

void UART_Initialize (USART_TypeDef * USARTx);
int UART_PutChar (USART_TypeDef * USARTx, int ch);
int UART_GetChar (USART_TypeDef * USARTx);
int UART_xGetChar (void);
int UART_xPutChar (int ch);
	
uint8_t USART_atoh(uint8_t ch);
void USART_putstring(USART_TypeDef * USARTx, uint8_t *str);
void USART_puthex_byte(USART_TypeDef * USARTx, uint8_t ch);
void USART_puthex_halfword(USART_TypeDef * USARTx, uint16_t ch);
void USART_puthex_word(USART_TypeDef * USARTx, uint32_t ch);

uint8_t USART_getch_echo(USART_TypeDef * USARTx);
uint8_t USART_gethex_byte(USART_TypeDef * USARTx);
uint8_t USART_gethex_byte_echo(USART_TypeDef * USARTx);
uint16_t USART_gethex_halfword_echo(USART_TypeDef * USARTx);
uint32_t USART_gethex_word_echo(USART_TypeDef * USARTx);

void USART_IRQHandler(uint8_t *buffer, uint32_t *pRx_counter);
void xmemset(void *dest, int value, int count);

#endif
