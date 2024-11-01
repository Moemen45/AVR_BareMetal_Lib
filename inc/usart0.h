#ifndef USART0_H
#define USART0_H

#include <avr/io.h>

#define F_CPU 16000000UL  // 16 MHz clock frequency (same as Arduino Uno)



void usart_Init(uint16_t baud, uint8_t config);

void usart_SendByte(uint8_t c);

uint8_t usart_ReceiveByte(void);

void usart_SendString(const char* string);

void usart_EnableRXInterrupt(void);

void usart_DisableRXInterrupt(void);

void usart_BufferWrite(uint8_t data);

uint8_t usart_BufferRead(void);

int usart_BufferHasData(void);



#endif