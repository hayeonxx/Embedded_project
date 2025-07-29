/*----------------------------------------------------------------------------
 * Name:    Serial.c
 * Purpose: Low Level Serial Routines
 * Note(s): possible defines select the used communication interface:
 *            __DBG_ITM   - ITM SWO interface
 *                        - USART2 interface  (default)
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

#include "stm32f446xx.h"                 // Device header
#include "main.h"
#include "uart.h"
#include "xprintf.h"
#include "fnd.h"

uint8_t hexcode[] = {"0123456789ABCDEF"};

#define USART2_INTERRUPT_EN

#ifdef __DBG_ITM
volatile int ITM_RxBuffer;              /*  CMSIS Debug Input                 */
#endif

/*----------------------------------------------------------------------------
 Define  USART
 *----------------------------------------------------------------------------*/
// #define USARTx  USART2


/*----------------------------------------------------------------------------
 Define  Baudrate setting (BRR) for USART
 *----------------------------------------------------------------------------*/
#define UART_DIV_SAMPLING16(_PCLK_, _BAUD_)            ((uint32_t)((((uint64_t)(_PCLK_))*25U)/(4U*((uint64_t)(_BAUD_)))))
#define UART_DIVMANT_SAMPLING16(_PCLK_, _BAUD_)        (UART_DIV_SAMPLING16((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING16(_PCLK_, _BAUD_)        ((((UART_DIV_SAMPLING16((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) * 100U)) * 16U)\
                                                         + 50U) / 100U)
/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + (UART DIVFRAQ & 0xF0) + (UART DIVFRAQ & 0x0FU) */
#define UART_BRR_SAMPLING16(_PCLK_, _BAUD_)            ((UART_DIVMANT_SAMPLING16((_PCLK_), (_BAUD_)) << 4U) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0xF0U) + \
                                                        (UART_DIVFRAQ_SAMPLING16((_PCLK_), (_BAUD_)) & 0x0FU))

#define UART_DIV_SAMPLING8(_PCLK_, _BAUD_)             ((uint32_t)((((uint64_t)(_PCLK_))*25U)/(2U*((uint64_t)(_BAUD_)))))
#define UART_DIVMANT_SAMPLING8(_PCLK_, _BAUD_)         (UART_DIV_SAMPLING8((_PCLK_), (_BAUD_))/100U)
#define UART_DIVFRAQ_SAMPLING8(_PCLK_, _BAUD_)         ((((UART_DIV_SAMPLING8((_PCLK_), (_BAUD_)) - (UART_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) * 100U)) * 8U)\
                                                         + 50U) / 100U)
/* UART BRR = mantissa + overflow + fraction
            = (UART DIVMANT << 4) + ((UART DIVFRAQ & 0xF8) << 1) + (UART DIVFRAQ & 0x07U) */
#define UART_BRR_SAMPLING8(_PCLK_, _BAUD_)             ((UART_DIVMANT_SAMPLING8((_PCLK_), (_BAUD_)) << 4U) + \
                                                        ((UART_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0xF8U) << 1U) + \
                                                        (UART_DIVFRAQ_SAMPLING8((_PCLK_), (_BAUD_)) & 0x07U))


/*----------------------------------------------------------------------------
  Initialize UART pins, Baudrate
 *----------------------------------------------------------------------------*/
void UART_Initialize (USART_TypeDef * USARTx) {

#ifdef __DBG_ITM
  ITM_RxBuffer = ITM_RXBUFFER_EMPTY;       /*  CMSIS Debug Input              */
#else
  RCC->AHB1ENR  |=   ( 1ul <<  0);        /* Enable GPIOA clock               */
  RCC->APB1ENR  |=   ( 1ul << 17);        /* Enable USART#2 clock             */

  /* Configure PA3 to USART2_RX, PA2 to USART2_TX */
  GPIOA->AFR[0] &= ~((15ul << 4* 3) | (15ul << 4* 2) );
  GPIOA->AFR[0] |=  (( 7ul << 4* 3) | ( 7ul << 4* 2) );
  GPIOA->MODER  &= ~(( 3ul << 2* 3) | ( 3ul << 2* 2) );
  GPIOA->MODER  |=  (( 2ul << 2* 3) | ( 2ul << 2* 2) );

  //USARTx->BRR  = __USART_BRR(12000000ul, 115200ul);  /* 115200 baud @ 12MHz   */
   //USARTx->BRR  = __USART_BRR(90000000ul, 115200ul);  /* 115200 baud @ 45MHz   */
   // CSet Baudrate to 9600 using APB frequency (80,000,000 Hz)
   // If oversampling by 16, Tx/Rx baud = f_CK / USARTDIV,  
   // If oversampling by 8,  Tx/Rx baud = 2*f_CK / USARTDIV
  // When OVER8 = 0, BRR = USARTDIV
   // USARTDIV = 180MHz/115,200/16 = 24.4140625 : Mantisa (24), Frac (0.414625*16) = 6.625
   // USARTDIV = 45MHz/115,200/16 = 24.4140625 : Mantisa (24), Frac (0.414625*16) = 6.625 <- actual : 38,400
   
   USARTx->BRR  = UART_BRR_SAMPLING16(45000000ul, 115200);
   
  USARTx->CR3    = 0x0000;                 /* no flow control                 */
  USARTx->CR2    = 0x0000;                 /* 1 stop bit                      */
  USARTx->CR1    = ((   0ul << 15) | 
                              (   1ul <<  2) |       /* enable RX                       */
                    (   1ul <<  3) |       /* enable TX                       */
                    (   0ul << 12) |       /* 1 start bit, 8 data bits        */
                    (   1ul << 13) );      /* enable USART                    */
                              
#ifdef USART2_INTERRUPT_EN
   USARTx->CR1    |= (   1ul << 5);         /* RXNE interrupt enable */
   NVIC_EnableIRQ(USART2_IRQn);

#endif


#endif
}


/*----------------------------------------------------------------------------
  Write character to Serial Port
 *----------------------------------------------------------------------------*/
int UART_PutChar (USART_TypeDef * USARTx, int ch) {

#ifdef __DBG_ITM
  ITM_SendChar (ch & 0xFF);
#else
  while (!(USARTx->SR & 0x0080));
  USARTx->DR = (ch & 0xFF);
#endif

  return (ch);
}

int UART_xPutChar (int ch) {

#ifdef __DBG_ITM
  ITM_SendChar (ch & 0xFF);
#else
  while (!(USART2->SR & 0x0080));
  USART2->DR = (ch & 0xFF);
#endif

  return (ch);
}

/*----------------------------------------------------------------------------
  Read character from Serial Port
 *----------------------------------------------------------------------------*/
int UART_GetChar (USART_TypeDef * USARTx) {

#ifdef __DBG_ITM
  if (ITM_CheckChar())
    return ITM_ReceiveChar();
#else
  while (!(USARTx->SR & 0x0020)){}
 // if (USARTx->SR & 0x0020)
    return (USARTx->DR);
   
#endif

//  return (-1);
}


int UART_xGetChar (void) {

#ifdef __DBG_ITM
  if (ITM_CheckChar())
    return ITM_ReceiveChar();
#else
  while (!(USART2->SR & 0x0020)){}
 // if (USARTx->SR & 0x0020)
    return (USART2->DR);
   
#endif

//  return (-1);
}

/////////////////////////////// UART Function ///////////////////////////////
void USART_putstring(USART_TypeDef * USARTx, uint8_t *str) {
   while(*str){
      if(*str == '\n')   {
         UART_PutChar(USARTx, 0x0D);
      }
    
      UART_PutChar(USARTx, *str);        
    str++;
  }
}

void USART_puthex_byte(USART_TypeDef * USARTx, uint8_t ch) {
   UART_PutChar(USARTx, hexcode[(ch >> 4)]);
   UART_PutChar(USARTx, hexcode[(ch & 0x0f)]); 
}

void USART_puthex_halfword(USART_TypeDef * USARTx, uint16_t ch) {
   USART_puthex_byte(USARTx, ch >> 8);
   USART_puthex_byte(USARTx, (uint8_t) ch);
}

void USART_puthex_word(USART_TypeDef * USARTx, uint32_t ch) {
   USART_puthex_byte(USARTx, ch >> 24);
   USART_puthex_byte(USARTx, ch >> 16);
   USART_puthex_byte(USARTx, ch >> 8);
   USART_puthex_byte(USARTx, (uint8_t) ch );
}

uint8_t USART_getch_echo(USART_TypeDef * USARTx) {
   uint8_t ch;
   
   ch = UART_GetChar(USARTx);
   UART_PutChar(USARTx, ch);

   return ch;
}
uint8_t USART_gethex_byte(USART_TypeDef * USARTx) {
   uint8_t ch;
   uint8_t value = 0;

   ch = UART_GetChar(USARTx);
   ch = USART_atoh(ch);
   value = ch<<4;

   ch = UART_GetChar(USARTx);
   ch = USART_atoh(ch);
   value |= ch;

   return value;
}

uint8_t USART_gethex_byte_echo(USART_TypeDef * USARTx) {
   uint8_t ch;
   uint8_t value = 0;

   ch = USART_getch_echo(USARTx);
   ch = USART_atoh(ch);
   value = ch<<4;

   ch = USART_getch_echo(USARTx);
   ch = USART_atoh(ch);
   value |= ch;

   return value;
}
uint16_t USART_gethex_halfword_echo(USART_TypeDef * USARTx) {
   uint8_t ch;
   uint16_t value = 0;

   ch = (uint16_t)USART_gethex_byte_echo(USARTx);
   value = (ch<<8);

   ch = (uint16_t)USART_gethex_byte_echo(USARTx);
   value |= ch;

   return value;
}

uint32_t USART_gethex_word_echo(USART_TypeDef * USARTx) {
   uint8_t ch;
   uint32_t value = 0;
   
   ch = (uint8_t)USART_gethex_byte_echo(USARTx);
   value = (ch<<24);
   
   ch = (uint8_t)USART_gethex_byte_echo(USARTx);
   value |= (ch<<16);

   ch = (uint8_t)USART_gethex_byte_echo(USARTx);
   value |= (ch<<8);

   ch = (uint8_t)USART_gethex_byte_echo(USARTx);
   value |= ch;
   
   return value;
}

uint8_t USART_atoh(uint8_t ch)
{
   if     ( ch>='0' && ch<='9' )   ch = (ch-'0');
   else if( ch>='a' && ch<='f' )   ch = (ch-'a'+0x0a);
   else if( ch>='A' && ch<='F' )   ch = (ch-'A'+0x0a);

   return ch;
}

void USART2_IRQHandler(void)
{
   USART_IRQHandler(USART2_Buffer_Rx, &Rx2_Counter);
}

void USART_IRQHandler(uint8_t *buffer, uint32_t * pRx_counter)
{
   if(USART2->SR & USART_SR_RXNE) {                  // Received data                         
      buffer[*pRx_counter] = USART2->DR;         // Reading USART_DR automatically clears the RXNE flag 
      
      xprintf("%c", buffer[*pRx_counter]);
      
      if (buffer[*pRx_counter] == 0x0d) {   // 0x0d = CR
         buffer[*pRx_counter] = 0x00;
         newline_flag = 1;
         return ;
      }
      
      (*pRx_counter)++;
      
      if((*pRx_counter) >= BufferSize )  {
         (*pRx_counter) = 0;
      }   
   } else if(USART2->SR & USART_SR_TXE) {
       //USARTx->ISR &= ~USART_ISR_TXE;            // clear interrupt 
      //Tx1_Counter++;
   } else if(USART2->SR & USART_SR_ORE) {         // Overrun Error
      while(1);
   } else if(USART2->SR & USART_SR_PE) {            // Parity Error
      while(1);
   } else if(USART2->SR & USART_SR_PE) {            // USART_ISR_FE   
      while(1);
   } else if (USART2->SR & USART_SR_NE){          // Noise Error Flag
      while(1);     
   }   
}

void xmemset(void *dest, int value, int count)
{
   int i;
   unsigned char *temp;
   
   temp = (unsigned char *)dest;
   
   i = 0;
   while (i < count) 
      temp[i++] = (unsigned char)value;
}
