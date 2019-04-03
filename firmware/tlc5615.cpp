#include "tlc5615.h"

TLC5615::TLC5615(volatile SPI& spi, SPIADR adr) : spi(spi), adr(adr)
{
}

void TLC5615::setValue(uint16_t val) const volatile
{
	spi.addByte(static_cast<uint8_t>(val >> 6));
	spi.addByte(static_cast<uint8_t>(val << 2));	
	spi.transfer(adr);
}
