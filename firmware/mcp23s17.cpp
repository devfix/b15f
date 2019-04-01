#include "mcp23s17.h"

MCP23S17::MCP23S17(SPI& spi, uint8_t adr) : spi(spi), adr(adr)
{
}

void MCP23S17::setDirA(uint8_t dir) const
{
	spi.setAdr(adr);
	spi.pushByte(MCP23S17_OPCODE | MCP23S17_WRITE);
	spi.pushByte(MCP23S17_DIRA);
	spi.pushByte(dir);
	spi.setAdr(SPIADR::NONE);
}

void MCP23S17::setDirB(uint8_t dir) const
{
	spi.setAdr(adr);
	spi.pushByte(MCP23S17_OPCODE | MCP23S17_WRITE);
	spi.pushByte(MCP23S17_DIRB);
	spi.pushByte(dir);
	spi.setAdr(SPIADR::NONE);
}

void MCP23S17::writePortA(uint8_t port) const
{
	spi.setAdr(adr);
	spi.pushByte(MCP23S17_OPCODE | MCP23S17_WRITE);
	spi.pushByte(MCP23S17_PORTA);
	spi.pushByte(port);
	spi.setAdr(SPIADR::NONE);
}

void MCP23S17::writePortB(uint8_t port) const
{
	spi.setAdr(adr);
	spi.pushByte(MCP23S17_OPCODE | MCP23S17_WRITE);
	spi.pushByte(MCP23S17_PORTB);
	spi.pushByte(port);
	spi.setAdr(SPIADR::NONE);
}

uint8_t MCP23S17::readPortA(void) const
{
	spi.setAdr(adr);
	spi.pushByte(MCP23S17_OPCODE | MCP23S17_READ);
	spi.pushByte(MCP23S17_PORTA);
	uint8_t port = spi.pushByte(0);
	spi.setAdr(SPIADR::NONE);
	return port;
}

uint8_t MCP23S17::readPortB(void) const
{
	spi.setAdr(adr);
	spi.pushByte(MCP23S17_OPCODE | MCP23S17_READ);
	spi.pushByte(MCP23S17_PORTB);
	uint8_t port = spi.pushByte(0);
	spi.setAdr(SPIADR::NONE);
	return port;
}
