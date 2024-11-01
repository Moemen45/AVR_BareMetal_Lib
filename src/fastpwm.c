#include "../inc/fastpwm.h"
#include <stddef.h> 

static pwm_callback_t PWM_PIN_PB3_CallBack = NULL;
static pwm_callback_t PWM_PIN_PD3_CallBack = NULL;
static pwm_callback_t PWM_PIN_PD5_CallBack = NULL;
static pwm_callback_t PWM_PIN_PD6_CallBack = NULL;

void pwm_init(pwm_pin_t pin, uint8_t duty){
    switch (pin)
    {
        case PWM_PIN_PB3: // Timer2, Channel A (OC2A)
            TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2A1); // Fast PWM, Non-inverting
            OCR2A = (duty / 100.0) * 255.0;
            TCCR2B = (1 << CS21);                                  // Prescaler 8
            
            DDRB |= (1 << PB3);                                    // Set PD6 as output
            
            break;

        case PWM_PIN_PD3: // Timer2, Channel B (OC2B)
            TCCR2A = (1 << WGM20) | (1 << WGM21) | (1 << COM2B1); // Fast PWM, Non-inverting
            OCR2A = (duty / 100.0) * 255.0;
            TCCR2B = (1 << CS21);                                  // Prescaler 8
            
            DDRD |= (1 << PD3);
            
            break;

        case PWM_PIN_PD5: // Timer0, Channel B (OC0B)
            TCCR0A = (1 << WGM00) | (1 << WGM01) | (1 << COM0B1); // Fast PWM, Non-inverting
            OCR0B = (duty / 100.0) * 255.0; 
            TCCR0B = (1 << CS01);                                  // Prescaler 8
            
            DDRD |= (1 << PD5);                                    // Set PD5 as output
            
            break;

        case PWM_PIN_PD6: // Timer0, Channel A (OC0A)
            
            TCCR0A = (1 << COM0A1 ) | (1 << WGM00) | (1 << WGM01);
            OCR0A = (duty / 100.0) * 255.0; 
            TCCR0B = (1 << CS01); 

            DDRD |= (1 << PD6);
            
            break;

        default:
            break;
    }
}
void pwm_set_duty(pwm_pin_t pin, uint8_t duty){

    volatile uint8_t dc;
    if((duty <= 100) & (duty >=0)) dc = (duty / 100.0) * 255.0; 
    switch (pin)
    {
        case PWM_PIN_PB3:
            OCR2A = dc;
            break;

        case PWM_PIN_PD3:
            OCR2B = dc;
            break;

        case PWM_PIN_PD5:
            OCR0B = dc;
            break;

        case PWM_PIN_PD6:
            OCR0A = dc;
            break;
    
        default:
            break;
    }
}
void pwm_enable_interrupt(pwm_pin_t pin){
    switch (pin)
    {
        case PWM_PIN_PB3:
            TIMSK2 |= (1 << OCIE2A);
            break;

        case PWM_PIN_PD3:
            TIMSK2 |= (1 << OCIE2B);
            break;

        case PWM_PIN_PD5:
            TIMSK0 |= (1 << OCIE0B);
            break;

        case PWM_PIN_PD6:
            TIMSK0 |= (1 << OCIE0A);
            break;
    
        default:
            break;
    }
}
void pwm_disable_interrupt(pwm_pin_t pin){
    switch (pin)
    {
        case PWM_PIN_PB3:
            TIMSK2 &= ~(1 << OCIE2A);
            break;

        case PWM_PIN_PD3:
            TIMSK2 &= ~(1 << OCIE2B);
            break;

        case PWM_PIN_PD5:
            TIMSK0 &= ~(1 << OCIE0B);
            break;

        case PWM_PIN_PD6:
            TIMSK0 &= ~(1 << OCIE0A);
            break;
    
        default:
            break;
    }
}

void pwm_SetCallBack(pwm_pin_t pin, void (*callback)(void)){
        switch (pin)
    {
        case PWM_PIN_PB3:
            PWM_PIN_PB3_CallBack = callback;
            break;

        case PWM_PIN_PD3:
            PWM_PIN_PD3_CallBack = callback;
            break;

        case PWM_PIN_PD5:
            PWM_PIN_PD5_CallBack = callback;
            break;

        case PWM_PIN_PD6:
            PWM_PIN_PD6_CallBack = callback;
            break;
    
        default:
            break;
    }

}

ISR(TIMER0_COMPA_vect){ // pd6
    if(PWM_PIN_PD6_CallBack) PWM_PIN_PD6_CallBack();
}    

ISR(TIMER0_COMPB_vect){ // pd5
    if(PWM_PIN_PD6_CallBack) PWM_PIN_PD6_CallBack();
}

ISR(TIMER2_COMPA_vect){ //pb3
    if(PWM_PIN_PB3_CallBack) PWM_PIN_PD6_CallBack();
}

ISR(TIMER2_COMPB_vect){ //pd3
    if(PWM_PIN_PD3_CallBack) PWM_PIN_PD6_CallBack();
}
