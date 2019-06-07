#include "pwm.h"
const uint16_t PWM::PRESCALERS[] = {0, 1, 8, 64, 256, 1024};
const uint8_t PWM::PRESCALER_COUNT = sizeof(PRESCALERS) / sizeof(uint16_t);

void PWM::init() const volatile
{
    // fast pwm mode, top = OCR0A, non inverting mode
    TCCR0A = _BV(COM0B1) | _BV(WGM00) | _BV(WGM01);
    TCCR0B =  _BV(WGM02);
    
    // output signal on PB4
    DDRB |= _BV(PB4);
}

void PWM::setFrequency(uint32_t freq) const volatile
{
    uint16_t p_ideal = ceil(float(F_CPU) / (freq * 0x100));
    for(int8_t i = PRESCALER_COUNT - 1; i >= 0 && PRESCALERS[i] >= p_ideal; i--)
        TCCR0B = (TCCR0B & 0xF8) | i; // set prescaler
    if(p_ideal)
        OCR0A = (uint8_t) (float(F_CPU) / (freq * PRESCALERS[TCCR0B & 0x07]));
}

void PWM::setValue(uint8_t value) const volatile
{
    OCR0B = value;
}

uint8_t PWM::getTop() const volatile
{
    return OCR0A;
}
