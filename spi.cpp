#include "spi.h"

SPI::SPI(void)
{
}

void SPI::init(void) const
{
	dMode(MOSI, OUT);
	dMode(MISO, IN);
	dMode(SCLK, OUT);
}
