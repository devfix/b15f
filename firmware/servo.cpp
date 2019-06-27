#include "servo.h"

void Servo::enable() volatile
{
    DDRB |= _BV(PB2);
    
    // configure impulse timer 1
    TCCR1A = 0;
    TCCR1B = _BV(WGM12);
    TCCR1C = 0;
    TIMSK1 = _BV(OCIE1A);
    
    // configure repeatition timer 2
    TCCR2A = _BV(WGM21);
    TCCR2B = _BV(CS22) | _BV(CS21); // prescaler 256
    TIMSK2 = _BV(OCIE2A);
    OCR2A = 124;
    repetition_counter = 0;
    
    OCR1A = 1500; // 1,5 ms init value
}
    
void Servo::disable() const volatile
{
    PORTB &= _BV(PB2);
    DDRB &= _BV(PB2);
    TCCR1B &= ~PRESCALER_IMPULSE; // stop timer 1
    TCCR2B = 0; // stop timer 2
}
    
void Servo::setPosition(uint16_t pos) const volatile
{
    OCR1A = pos;
}

void Servo::handleTimer1(void) const volatile
{
    PORTB &= ~_BV(PB2); // end pulse (set pin low)
    TCCR1B &= ~PRESCALER_IMPULSE; // stop timer 1
}

void Servo::handleTimer2(void) volatile
{
    repetition_counter++;
    if(repetition_counter >= 5)
    {
        repetition_counter = 0;
        TCCR1B |= PRESCALER_IMPULSE; // start timer 1
        PORTB |= _BV(PB2); // start impuls (set pin high)
    }
}
