#include "pwm.h"

void pwmSetFrequency(uint32_t freq)
{
    TCCR0A = _BV(COM0B1) | _BV(WGM00) | _BV(WGM01);
    DDRB |= _BV(PB4);
    
    uint16_t p_ideal = ceil(float(F_CPU) / (freq * 0x100));
    for(int8_t i = PWM_PRESCALER_COUNT - 1; i >= 0 && PWM_PRESCALERS[i] >= p_ideal; i--)
        TCCR0B = _BV(WGM02) | i; // set prescaler
    if(p_ideal)
        OCR0A = (uint8_t) (float(F_CPU) / (freq * PWM_PRESCALERS[TCCR0B & 0x07]));
}

void pwmSetValue(uint8_t value)
{
    OCR0B = value;
}
