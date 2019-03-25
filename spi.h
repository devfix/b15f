#ifndef SPI_H
#define SPI_H

#include <util/delay.h>
#include <stdint.h>
#include "pio.h"

#define SLSL B4
#define MOSI B5
#define MISO B6
#define SCLK B7

#define DMUX1 D2
#define DMUX2 D3
#define DMUX3 D4

enum SPIADR {
	BEBA0 = 2,
	BEBA1 = 3,
	NONE = 7,
};

class SPI
{
public:
	SPI(void);
	void init(void) const;
	//void setFreq(uint32_t) const;
	void setAdr(uint8_t) const;
	uint8_t pushByte(uint8_t) const;

};

#endif // SPI_H
