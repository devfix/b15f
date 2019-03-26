#include "spi.h"

SPI::SPI(void)
{
}

void SPI::init(void) const
{

	// Konfiguriere SPI DDRs
	DDRB |= _BV(SLSL) | _BV(MOSI) | _BV(SCLK);
	DDRB &= ~_BV(MISO);

	// Konfiguriere DMUX DDRs
	DDRD |= _BV(DMUX1) | _BV(DMUX2) | _BV(DMUX3);

	// aktiviere SPI, Master Modus, SPI Modus 0
	// F_SPI = F_CPU / 2   (prescaler 2)
	SPCR = _BV(SPE) | _BV(MSTR);
	SPSR = _BV(SPI2X);

	// waehle keinen SPI Slave aus
	setAdr(SPIADR::NONE);
}

void SPI::setAdr(uint8_t adr) const
{
	PORTD &= ~(_BV(DMUX1) | _BV(DMUX2) | _BV(DMUX3));
	PORTD |= (adr & 0x01) ? _BV(DMUX1) : 0;
	PORTD |= (adr & 0x02) ? _BV(DMUX2) : 0;
	PORTD |= (adr & 0x04) ? _BV(DMUX3) : 0;
}

uint8_t SPI::pushByte(uint8_t b) const
{
	SPDR = b;
	while(!(SPSR & _BV(SPIF)));
	return SPDR;
}
