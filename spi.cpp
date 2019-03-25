#include "spi.h"

SPI::SPI(void)
{
}

void SPI::init(void) const
{

	// Konfiguriere SPI DDRs
	dMode(SLSL, OUT);
	dMode(MOSI, OUT);
	dMode(MISO, IN);
	dMode(SCLK, OUT);

	// Konfiguriere DMUX DDRs
	dMode(DMUX1, OUT);
	dMode(DMUX2, OUT);
	dMode(DMUX3, OUT);


	// aktiviere SPI, Master Modus, SPI Modus 0
	// F_SPI = F_CPU / 2   (prescaler 2)
	SPCR = _BV(SPE) | _BV(MSTR);
	SPSR = _BV(SPI2X);

	// waehle keinen SPI Slave aus
	setAdr(SPIADR::NONE);
}

/*void SPI::setFreq(uint32_t freq) const
{

}*/

void SPI::setAdr(uint8_t adr) const
{
	dWrite(DMUX1, 0);
	dWrite(DMUX2, 0);
	dWrite(DMUX3, 0);

	if(adr & 0x01)
		dWrite(DMUX1, 1);
	if(adr & 0x02)
		dWrite(DMUX2, 1);
	if(adr & 0x04)
		dWrite(DMUX3, 1);
}

uint8_t SPI::pushByte(uint8_t b) const
{
	SPDR = b;
	while(!(SPSR & _BV(SPIF)));
	return SPDR;
}
