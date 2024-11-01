#include <avr/io.h>
#include "../inc/timer1CNT.h"

void toggleLED(void) {
    TCNT1 = 0;
    PORTC ^= (1 << PC0);  // Toggle the LED connected to PB0
}

int main(void) {
    // Set PB0 as output for the LED
    DDRC |= (1 << PC0);

    // Initialize Timer1 for a 1 second delay in normal mode (1000ms)
    Timer1_init(1000, TIMER1_MODE_NORMAL_CMP);
    
    // Set the callback function for the timer interrupt
    Timer1_setCallback(toggleLED);
    
    // Start Timer1
    Timer1_start();

    // Main loop
    while (compare_count < 10);


    PORTC &= ~(1 << 0);
    Timer1_stop(); 

        // Main loop does nothing, LED is toggled in the interrupt
    return 0;
}
