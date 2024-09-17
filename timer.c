/*timer.c*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"

void timer1_init(void) {
    // Set Timer1 in CTC mode
    TCCR1B |= (1 << WGM12);  // CTC mode

    // Set the prescaler to 1024 (Clock / 1024)
    TCCR1B |= (1 << CS12) | (1 << CS10);  // Prescaler 1024

    // Set the Output Compare Register value for 1Hz interrupt rate
    OCR1A = 15625;

    // Enable Timer1 Compare Match A interrupt
    TIMSK |= (1 << OCIE1A);

    // Enable global interrupts
    sei();
}

void timer1_stop(void) {
    TCCR1B &= ~((1 << CS12) | (1 << CS11) | (1 << CS10));  // Stop Timer1
}

void timer1_resume(void) {
    TCCR1B |= (1 << CS12) | (1 << CS10);  // Resume Timer1 (prescaler 1024)
}
