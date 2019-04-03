#ifndef TLC5615_H
#define TLC5615_H

#include "spi.h"

class TLC5615
{
public:
	TLC5615(volatile SPI&, uint8_t);
	void setValue(uint16_t) const volatile;


private:
	volatile SPI& spi;
	const uint8_t adr;
};

#endif // TLC5615_H
