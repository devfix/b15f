#ifndef PWM_H
#define PWM_H

#include <avr/io.h>
#include <math.h>

class PWM
{
public:
    void init(void) const volatile;
    void setFrequency(uint32_t) const volatile;
    void setValue(uint8_t) const volatile;
    uint8_t getTop(void) const volatile;
    
private:
    const static uint16_t PRESCALERS[];
    const static uint8_t PRESCALER_COUNT;
};

#endif // PWM_H
