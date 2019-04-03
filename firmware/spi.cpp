#include "spi.h"

void SPI::init() const volatile
{
	// Konfiguriere SPI DDRs
	DDRB |= _BV(SLSL) | _BV(MOSI) | _BV(SCLK);
	DDRB &= ~_BV(MISO);

	// Konfiguriere DMUX DDRs
	DDRD |= _BV(DMUX1) | _BV(DMUX2) | _BV(DMUX3);

	// aktiviere SPI, Master Modus, SPI Modus 0
	// F_SPI = F_CPU / 2   (prescaler 2)
	SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPIE);
	SPSR = _BV(SPI2X) | _BV(SPIF);

	// waehle keinen SPI Slave aus
	setAdr(SPIADR::NONE);
}

void SPI::handleTransfer() volatile
{
	if(!active)
	{
		setAdr(SPIADR::NONE);
		return;
	}
	
	uint8_t next = buffer[index];
	buffer[index++] = SPDR;
	
	if(index >= length)
	{
		index = 0;
		active = false;
	}
	
	SPDR = next;
}

void SPI::addByte(uint8_t b) volatile
{
	wait();
	buffer[index++] = b;
}

void SPI::transfer(SPIADR adr) volatile
{
	if(!index)
		return;
	
	wait();
	active = true;
	
	setAdr(adr);
	
	this->length = index;
	this->index = 0;
	
	handleTransfer();
}

void SPI::wait() volatile
{
	while(active);
}

void SPI::setAdr(SPIADR adr) const volatile
{
	PORTD &= ~(_BV(DMUX1) | _BV(DMUX2) | _BV(DMUX3));
	PORTD |= (adr & 0x01) ? _BV(DMUX1) : 0;
	PORTD |= (adr & 0x02) ? _BV(DMUX2) : 0;
	PORTD |= (adr & 0x04) ? _BV(DMUX3) : 0;
}
