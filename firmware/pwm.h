#ifndef PWM_H
#define PWM_H

#include <avr/io.h>
#include <math.h>

const uint16_t PWM_PRESCALERS[] = {0, 1, 8, 64, 256, 1024};
const uint8_t PWM_PRESCALER_COUNT = sizeof(PWM_PRESCALERS) / sizeof(uint16_t);

void pwmSetFrequency(uint32_t);
void pwmSetValue(uint8_t);

#endif // PWM_H
