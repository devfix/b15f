#include "usart.h"

void USART::init()
{
	UCSR0A = _BV(U2X0);
	
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);

	// Einstellen des Datenformats: 8 Datenbits, 1 Stoppbit
	UCSR0C = _BV(UCSZ00) |_BV(UCSZ01);// (1<<URSEL0)|(1<<UCSZ10)|(1<<UCSZ00);

	// setze Baudrate
	UBRR0H = (((F_CPU / (8UL * BAUDRATE))-1) >> 8) & 0xFF;
	UBRR0L =  ((F_CPU / (8UL * BAUDRATE))-1) & 0xFF;

}

void USART::writeByte(uint8_t b)
{
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = b;
	
	//while(!(UCSR0A & _BV(TXC0)));
}


void USART::writeInt(uint16_t v)
{
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = v & 0xFF;
	
	v >>= 8;
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = v & 0xFF;
	
	//while(!(UCSR0A & _BV(TXC0)));
}

uint8_t USART::readByte()
{
	while (!(UCSR0A & (1<<RXC0)));
    return UDR0;
}

uint16_t USART::readInt()
{
	uint16_t v = readByte();
	v |= readByte() << 8;
	return v;
}
