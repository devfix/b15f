#include "tlc5615.h"

TLC5615::TLC5615(SPI& spi, uint8_t adr) : spi(spi), adr(adr)
{
}

void TLC5615::setValue(uint16_t val) const
{
	spi.setAdr(adr);
	spi.pushByte(val >> 6);
	spi.pushByte(val << 2);
	spi.setAdr(SPIADR::NONE);
}
