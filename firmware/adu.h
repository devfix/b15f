#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

class ADU
{
public:
	void init(void) volatile;
	uint16_t getValue(uint8_t) volatile;
};

#endif // ADC_H
