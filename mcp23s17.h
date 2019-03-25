#ifndef MCP23S17_H
#define MCP23S17_H

#include "spi.h"

class MCP23S17
{
public:
	MCP23S17(SPI&, uint8_t);
	void setPort(uint8_t) const;

private:
	SPI& spi; 
	const uint8_t adr;
};

#endif // MCP23S17_H
