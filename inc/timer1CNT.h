#ifndef TIMER1CNT_H
#define TIMER1CNT_H

#include <avr/io.h>

#define F_CPU 16000000
#define TIMER1_MODE_NORMAL_OVF 0
#define TIMER1_MODE_NORMAL_CMP 1


extern uint32_t overflow_count;
extern uint32_t compare_count;

void Timer1_start(void);

void Timer1_stop(void);

void Timer1_init(uint16_t delay_ms, uint8_t mode);

uint32_t ellapsed (uint16_t delay_ms, uint8_t mode);

void Timer1_setCallback(void (*callback)(void));


#endif
