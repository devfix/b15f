#include "mcp23s17.h"

MCP23S17::MCP23S17(SPI& spi, uint8_t adr) : spi(spi), adr(adr)
{

}


void MCP23S17::setPort(uint8_t port) const
{
	
	spi.pushByte(0x40);
	/*

	spi.setAdr(0);
	_delay_ms(1);
	spi.setAdr(adr);
	spi.pushByte(0x40); // 
	spi.pushByte(0x00); // DIR A
	spi.pushByte(0x00); // alle ausgang
	
	spi.setAdr(0);
	_delay_ms(1);
	spi.setAdr(adr);
	spi.pushByte(0x40);
	spi.pushByte(0x12);
	spi.pushByte(0xF0);
	spi.setAdr(0);

	/*while(1) {
		PORTB ^= _BV(PB7);
		_delay_ms(1);
	}*/
}
