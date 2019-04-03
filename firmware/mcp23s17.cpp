#include "mcp23s17.h"

MCP23S17::MCP23S17(volatile SPI& spi, uint8_t adr) : spi(spi), adr(adr)
{
}

void MCP23S17::setDirA(uint8_t dir) const volatile
{
	spi.addByte(MCP23S17_OPCODE | MCP23S17_WRITE);
	spi.addByte(MCP23S17_DIRA);
	spi.addByte(dir);
	spi.transfer(adr);
}

void MCP23S17::setDirB(uint8_t dir) const volatile
{
	spi.addByte(MCP23S17_OPCODE | MCP23S17_WRITE);
	spi.addByte(MCP23S17_DIRB);
	spi.addByte(dir);
	spi.transfer(adr);
}

void MCP23S17::writePortA(uint8_t port) const volatile
{
	spi.addByte(MCP23S17_OPCODE | MCP23S17_WRITE);
	spi.addByte(MCP23S17_PORTA);
	spi.addByte(port);
	spi.transfer(adr);
}

void MCP23S17::writePortB(uint8_t port) const volatile
{
	spi.addByte(MCP23S17_OPCODE | MCP23S17_WRITE);
	spi.addByte(MCP23S17_PORTB);
	spi.addByte(port);
	spi.transfer(adr);
}

uint8_t MCP23S17::readPortA(void) const volatile
{
	spi.addByte(MCP23S17_OPCODE | MCP23S17_READ);
	spi.addByte(MCP23S17_PORTA);
	spi.addByte(0);
	spi.addByte(0);
	spi.transfer(adr);
	spi.wait();
	return spi.buffer[3];
}

uint8_t MCP23S17::readPortB(void) const volatile
{
	spi.addByte(MCP23S17_OPCODE | MCP23S17_READ);
	spi.addByte(MCP23S17_PORTB);
	spi.addByte(0);
	spi.addByte(0);
	spi.transfer(adr);
	spi.wait();
	return spi.buffer[3];
}
