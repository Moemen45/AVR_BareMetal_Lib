#include <avr/interrupt.h>
#include "../inc/timer1CNT.h"

uint32_t overflow_count = 0;
uint32_t compare_count = 0;

static void (*Timer1_callback)(void) = 0;  // Callback function pointer

void Timer1_start(void) {   
    sei();      // Enable global interrupts
}

void Timer1_stop(void) {
    TCCR1B = 0;  // Stop the timer by clearing the clock bits
    TIMSK1 = 0;  // Disable interrupts
}

void Timer1_init(uint16_t delay_ms, uint8_t mode) {
    
    uint16_t ticks; 
    Timer1_stop();
    uint16_t prescaler = 1024;
    if(mode == TIMER1_MODE_NORMAL_OVF){
        ticks = (F_CPU/1024) * delay_ms/1000; // number of ticks  < (65535:max_val 16 bit timer) // (F_CPU/1024) nub of ticks per second
        TCNT1 = 65535 - ticks;
    }
    if(mode == TIMER1_MODE_NORMAL_CMP){ 
        TCNT1 = 0;
        OCR1A = (F_CPU/1024);
    }
    TCCR1B = (1 << CS10 ) | (1 << CS12);
    if(mode == TIMER1_MODE_NORMAL_OVF) TIMSK1 = (1 << TOIE1);
    if(mode == TIMER1_MODE_NORMAL_CMP) TIMSK1 |= (1 << OCIE1A);
}

uint32_t ellapsed (uint16_t delay_ms, uint8_t mode){
    uint16_t current_tick = TCNT1;
    uint32_t total_ticks;
    if(mode == TIMER1_MODE_NORMAL_OVF)
        total_ticks = (overflow_count * (65355 - (F_CPU/1024) * delay_ms/1000)) + (current_tick - ((F_CPU/1024) * delay_ms/1000));
    
    if(mode == TIMER1_MODE_NORMAL_CMP)
        total_ticks = (overflow_count * (F_CPU/1024) * delay_ms/1000) + current_tick;
    return (total_ticks * (1024 * 1000UL)) / F_CPU ;
}

void Timer1_setCallback(void (*callback)(void)) {
    Timer1_callback = callback;
}

ISR(TIMER1_OVF_vect) {
    overflow_count++ ;
    if (Timer1_callback) {
        Timer1_callback();
    }
}

ISR(TIMER1_COMPA_vect) {
    compare_count++ ;
    if (Timer1_callback) {
        Timer1_callback();
    }
}