#ifndef SPI_H
#define SPI_H

#include <util/delay.h>
#include <avr/io.h>
#include <stdint.h>

#define SLSL PB4
#define MOSI PB5
#define MISO PB6
#define SCLK PB7

#define DMUX1 PD2
#define DMUX2 PD3
#define DMUX3 PD4

enum SPIADR {
	AA0 = 0,
	AA1 = 1,
	BEBA0 = 2,
	BEBA1 = 3,
	EXT = 4,
	SWITCH = 5,
	NONE = 7,
};

class SPI
{
public:
	SPI(void);
	void init(void) const;
	void setAdr(uint8_t) const;
	uint8_t pushByte(uint8_t) const;

};

#endif // SPI_H
