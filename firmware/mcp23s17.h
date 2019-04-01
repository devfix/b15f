#ifndef MCP23S17_H
#define MCP23S17_H

#include "spi.h"

constexpr uint8_t MCP23S17_DIRA = 0x00;
constexpr uint8_t MCP23S17_DIRB = 0x01;
constexpr uint8_t MCP23S17_PORTA = 0x12;
constexpr uint8_t MCP23S17_PORTB = 0x13;
constexpr uint8_t MCP23S17_READ = 0x01;
constexpr uint8_t MCP23S17_WRITE = 0x00;
constexpr uint8_t MCP23S17_OPCODE = 0x40;

class MCP23S17
{
public:
	MCP23S17(SPI&, uint8_t);
	void setDirA(uint8_t dir) const;
	void setDirB(uint8_t dir) const;
	void writePortA(uint8_t) const;
	void writePortB(uint8_t) const;
	uint8_t readPortA(void) const;
	uint8_t readPortB(void) const;

private:
	SPI& spi; 
	const uint8_t adr;
};

#endif // MCP23S17_H
