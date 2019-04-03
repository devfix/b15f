#ifndef MCP23S17_H
#define MCP23S17_H

#include "spi.h"



class MCP23S17
{
public:
	MCP23S17(volatile SPI&, SPIADR adr);
	void setDirA(uint8_t dir) const volatile;
	void setDirB(uint8_t dir) const volatile;
	void writePortA(uint8_t) const volatile;
	void writePortB(uint8_t) const volatile;
	uint8_t readPortA(void) const volatile;
	uint8_t readPortB(void) const volatile;

private:
	volatile SPI& spi; 
	const SPIADR adr;

	// constants
	constexpr static uint8_t MCP23S17_DIRA = 0x00;
	constexpr static uint8_t MCP23S17_DIRB = 0x01;
	constexpr static uint8_t MCP23S17_PORTA = 0x12;
	constexpr static uint8_t MCP23S17_PORTB = 0x13;
	constexpr static uint8_t MCP23S17_READ = 0x01;
	constexpr static uint8_t MCP23S17_WRITE = 0x00;
	constexpr static uint8_t MCP23S17_OPCODE = 0x40;
};

#endif // MCP23S17_H
