#include "../inc/usart0.h"
#include <avr/interrupt.h>

// parity modes and data bits
#define USART_8N1 0x06 //8 data bits, no parity, 1 stop bit

// buffer manip param
#define BUFFER_SIZE 64

volatile uint8_t usart_buffer[BUFFER_SIZE];
volatile uint8_t buffer_write_index = 0;
volatile uint8_t buffer_read_index = 0;

void usart_Init(uint16_t baud, uint8_t config){

    //set baud rate
    uint16_t ubrr_val = F_CPU/16/baud - 1;
    UBRR0H = (unsigned char)(ubrr_val>>8);
    UBRR0L = (unsigned char)ubrr_val;

    //set configurarion : data_size, parity ect .. 
    UCSR0C = config;

    //enable tx & rx 
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0); 

}

void usart_SendByte(uint8_t c){
    
    while (!((1 << UDRE0) & UCSR0A)); // WAIT TILL BUFFER READY && DATA REG EMPTY
    UDR0 = c;

}

uint8_t usart_ReceiveByte(void){
    
    while (!(UCSR0A & (1 << RXC0))); // WAIT TILL BUFF READY && DATA AVAILABLE
    return UDR0;

}

void usart_SendString(const char* string){
    while (*string != '\0')
    {
        usart_SendByte(*string++);
    }
    
}

void usart_EnableRXInterrupt(void){

    UCSR0B |= (1 << RXCIE0);

}

void usart_DisableRXInterrupt(void){

    UCSR0B &= ~(1 << RXCIE0);

}


// this function writes from uart data register into a buffer
void usart_BufferWrite(uint8_t data){
    
    usart_buffer[buffer_write_index] = data;
    buffer_write_index++; 
    
    if(buffer_write_index >= BUFFER_SIZE){
        buffer_write_index = 0;
    }
    

}

// this function reades from buffer and returns it 
uint8_t usart_BufferRead(void){
    
    uint8_t data = '\0';
    if(buffer_read_index != buffer_write_index){
    
        data = usart_buffer[buffer_read_index];
        buffer_read_index++;

        if (buffer_read_index >= BUFFER_SIZE){
            buffer_read_index = 0;
        }
    }
    
    return data;

}

int usart_BufferHasData(void) {
    return buffer_read_index != buffer_write_index ? 1 : 0;
}

ISR(USART_RX_vect) {
    uint8_t received_data = UDR0; // Read the received byte from the data register
    usart_BufferWrite(received_data); // Store it in the buffer
}

