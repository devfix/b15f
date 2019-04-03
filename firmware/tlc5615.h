#ifndef TLC5615_H
#define TLC5615_H

#include "spi.h"

class TLC5615
{
public:
	TLC5615(volatile SPI&, SPIADR adr);
	void setValue(uint16_t) const volatile;


private:
	volatile SPI& spi;
	const SPIADR adr;
};

#endif // TLC5615_H
