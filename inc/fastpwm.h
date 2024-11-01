/************************************************************************* */
//              PWM uses only tim0 && tim2 (8 bit timers)
//                              max value 255
/************************************************************************* */

#ifndef FASTPWM_H
#define FASTPWM_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define PWM_MAX 255

typedef enum{
    PWM_PIN_PD6,
    PWM_PIN_PD5,
    PWM_PIN_PD3,
    PWM_PIN_PB3
} pwm_pin_t;

typedef void (*pwm_callback_t)(void);

void pwm_init(pwm_pin_t pin, uint8_t duty);
void pwm_set_duty(pwm_pin_t pin, uint8_t duty);
void pwm_enable_interrupt(pwm_pin_t pin);
void pwm_disable_interrupt(pwm_pin_t pin);

void pwm_SetCallBack(pwm_pin_t pin, void (*callback)(void));




#endif