/*time_management.c*/
#include <avr/io.h>
#include <util/delay.h>
#include "time_management.h"
#include "display.h"
unsigned char seconds = 0;
unsigned char minutes = 0;
unsigned char hours = 0;
unsigned char mode = 0;

void check_mode_toggle(void) {
    if (!(PINB & (1 << PB7))) {  // Check if PB7 (mode toggle button) is pressed
        _delay_ms(1);  // Debouncing delay
        if (!(PINB & (1 << PB7))) {  // Confirm button press after debounce
            mode = !mode;  // Toggle mode

            // Update LED indicators based on the mode
            if (mode == 0) {
                // Increment mode
                PORTD |= (1 << PD4);  // Red LED on
                PORTD &= ~(1 << PD5);  // Yellow LED off
            } else {
                // Countdown mode
                PORTD |= (1 << PD5);  // Yellow LED on
                PORTD &= ~(1 << PD4);  // Red LED off
            }

            while (!(PINB & (1 << PB7))) {
                display_time();
            }  // Wait until button is released
        }
    }
}

// Function to adjust time
void check_time_adjustment(void) {
    // Increment hours (PB1)
    if (!(PINB & (1 << PB1))) {
        _delay_ms(1);
        if (!(PINB & (1 << PB1))) {
            hours++;
            if (hours > 23) {
                hours = 0;
            }
            while (!(PINB & (1 << PB1))) {
                display_time();
            }
        }
    }

    // Decrement hours (PB0)
    if (!(PINB & (1 << PB0))) {
        _delay_ms(1);
        if (!(PINB & (1 << PB0))) {
            switch (hours) {
                case 0:
                    // If hours are 0, reset everything to 0
                    hours = 0;
                    minutes = 0;
                    seconds = 0;
                    break;
                default:
                    // Regular decrement of hours
                    hours--;
                    break;
            }
            while (!(PINB & (1 << PB0))) {
                display_time();
            }
        }
    }

    // Increment minutes (PB4)
    if (!(PINB & (1 << PB4))) {
        _delay_ms(1);
        if (!(PINB & (1 << PB4))) {
            minutes++;
            if (minutes > 59) {
                minutes = 0;
                hours++;
                if (hours > 23) {
                    hours = 0;
                }
            }
            while (!(PINB & (1 << PB4))) {
                display_time();
            }
        }
    }

    // Decrement minutes (PB3)
    if (!(PINB & (1 << PB3))) {
        _delay_ms(1);
        if (!(PINB & (1 << PB3))) {
            switch (minutes) {
                case 0:
                    if (hours == 0) {
                        // Case: Both minutes and hours are 0, set seconds to 0
                        seconds = 0;
                    } else {
                        // Case: minutes are 0, but hours are not 0
                        hours--;
                        minutes = 59;
                        seconds = 59;
                    }
                    break;
                default:
                    // Regular decrement of minutes
                    minutes--;
                    break;
            }
            while (!(PINB & (1 << PB3))) {
                display_time();
            }
        }
    }

    // Increment seconds (PB6)
    if (!(PINB & (1 << PB6))) {
        _delay_ms(1);
        if (!(PINB & (1 << PB6))) {
            seconds++;
            if (seconds > 59) {
                seconds = 0;
                minutes++;
                if (minutes > 59) {
                    minutes = 0;
                    hours++;
                    if (hours > 23) {
                        hours = 0;
                    }
                }
            }
            while (!(PINB & (1 << PB6))) {
                display_time();
            }
        }
    }

    // Decrement seconds (PB5)
    if (!(PINB & (1 << PB5))) {
        _delay_ms(1);
        if (!(PINB & (1 << PB5))) {
            switch (seconds) {
                case 0:
                    seconds = 59;
                    if (minutes == 0) {
                        minutes = 59;
                        if (hours == 0) {
                            hours = 23;
                        } else {
                            hours--;
                        }
                    } else {
                        minutes--;
                    }
                    break;
                default:
                    // Regular decrement of seconds
                    seconds--;
                    break;
            }
            while (!(PINB & (1 << PB5))) {
                display_time();
            }
        }
    }
}
