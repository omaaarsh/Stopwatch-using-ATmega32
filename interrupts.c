/*interrupts.c*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "interrupts.h"
#include "time_management.h"
#include "timer.h"

void external_interrupts_init(void) {
    // Configure PD2 (INT0), PD3 (INT1), and PB2 (INT2) as input pins
    DDRD &= ~(1 << PD2) & ~(1 << PD3);
    DDRB &= 0X00;

    // Enable internal pull-up resistors
    PORTB =0XFF;

    sei();

    // Configure INT0 for falling edge
    MCUCR |= (1 << ISC01);  // Falling edge on INT0
    MCUCR &= ~(1 << ISC00); // Falling edge on INT0
    GICR |= (1 << INT0);    // Enable INT0

    // Configure INT1 for rising edge
    MCUCR |= (1 << ISC11) | (1 << ISC10); // Rising edge on INT1
    GICR |= (1 << INT1);                  // Enable INT1

    // Configure INT2 for falling edge
    MCUCSR &= ~(1 << ISC2); // Falling edge on INT2
    GICR |= (1 << INT2);    // Enable INT2

    // Enable pull-up resistor for INT0 (PD2) and INT2 (PB2)
    PORTD |= (1 << PD2); // Pull-up for INT0
    PORTB |= (1 << PB2); // Pull-up for INT2
}
ISR(TIMER1_COMPA_vect) {
    if (mode == 0) {
        // Increment mode
    	PORTD &= ~(1 << PD0);
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
    } else {
        // Countdown mode
        if (seconds == 0 && minutes == 0 && hours == 0) {
            // Activate buzzer when countdown reaches zero
            PORTD |= (1 << PD0);  // Activate buzzer
        } else {
            if (seconds == 0) {
                seconds = 59;
                if (minutes == 0) {
                    minutes = 59;
                    hours--;
                } else {
                    minutes--;
                }
            } else {
                seconds--;
            }
        }
    }
}

ISR(INT0_vect) {
    seconds = 0;
    minutes = 0;
    hours = 0;
    PORTD &= ~(1 << PD0);  // Deactivate buzzer if it's active
}

ISR(INT1_vect) {
    timer1_stop();
}

ISR(INT2_vect) {
    timer1_resume();
}
