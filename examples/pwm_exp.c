#include "../inc/fastpwm.h"
#include "util/delay.h"

double duty_cycle = 0;
uint8_t increment_flag = 1; 

int main(void){

    uint8_t duty_cycle = 0;
    pwm_init(PWM_PIN_PD6, duty_cycle);
    
    while(1){

        _delay_ms(5000);

        if (increment_flag){
            
            if (duty_cycle == 90) 
                increment_flag = 0;

            duty_cycle += 10;
            pwm_set_duty(PWM_PIN_PD6, duty_cycle);
        } else {

            if(duty_cycle == 10) 
                increment_flag = 1;   
            
            duty_cycle -= 10;
            pwm_set_duty(PWM_PIN_PD6, duty_cycle);
        }


        
    }
}


