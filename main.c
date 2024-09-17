/*main.c*/
#include <avr/io.h>
#include <util/delay.h>
#include "timer.h"
#include "interrupts.h"
#include "time_management.h"
void display_time(void) {
    // Display seconds
    PORTA = (1 << 5);  // Select seconds_ones digit
    PORTC = (PORTC & 0xF0) | ((seconds % 10) & 0x0F);  // Output seconds_ones value
    _delay_ms(1);  // Delay for multiplexing

    PORTA = (1 << 4);  // Select seconds_tens digit
    PORTC = (PORTC & 0xF0) | ((seconds / 10) & 0x0F);  // Output seconds_tens value
    _delay_ms(1);  // Delay for multiplexing

    // Display minutes
    PORTA = (1 << 3);  // Select minutes_ones digit
    PORTC = (PORTC & 0xF0) | ((minutes % 10) & 0x0F);  // Output minutes_ones value
    _delay_ms(1);  // Delay for multiplexing

    PORTA = (1 << 2);  // Select minutes_tens digit
    PORTC = (PORTC & 0xF0) | ((minutes / 10) & 0x0F);  // Output minutes_tens value
    _delay_ms(1);  // Delay for multiplexing

    // Display hours
    PORTA = (1 << 1);  // Select hours_ones digit
    PORTC = (PORTC & 0xF0) | ((hours % 10) & 0x0F);  // Output hours_ones value
    _delay_ms(1);  // Delay for multiplexing

    PORTA = (1 << 0);  // Select hours_tens digit
    PORTC = (PORTC & 0xF0) | ((hours / 10) & 0x0F);  // Output hours_tens value
    _delay_ms(1);  // Delay for multiplexing
}
int main(void) {
    // Configure PORTC lower 4 bits (PC0-PC3) as output for 7-segment display
    DDRC = 0x0F;

    // Configure PORTA as output for selecting 7-segment display digits
    DDRA = 0xFF;

    // Configure PD0 as output for buzzer
    DDRD |= (1 << PD0);

    // Configure PD4 and PD5 as output for mode LEDs
    DDRD |= (1 << PD4) | (1 << PD5);

    // Initialize Timer1 and external interrupts
    timer1_init();
    external_interrupts_init();
    PORTD |= (1 << PD4);  // Red LED on
    PORTD &= ~(1 << PD5);

    // Main loop
    while (1) {
        display_time();  // Continuously display the current time

        check_mode_toggle();       // Check for mode toggle button press
        check_time_adjustment();   // Check for time adjustment button presses
    }

    return 0;
}
