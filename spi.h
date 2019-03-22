#ifndef SPI_H
#define SPI_H

#include <util/delay.h>

class SPI {
public:
	SPI(void) {
		DDRB |= _BV(PB0);
		while(1) {
			PORTB ^= _BV(PB0);
			_delay_ms(1);
		}
	}

	private: int d;

};

#endif
