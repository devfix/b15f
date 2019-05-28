#include "usart.h"

void USART::init() volatile
{
	UCSR0A = _BV(U2X0);
	
	UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0) | _BV(TXCIE0);

	// Einstellen des Datenformats: 8 Datenbits, 1 Stoppbit
	UCSR0C = _BV(UCSZ00) |_BV(UCSZ01);// (1<<URSEL0)|(1<<UCSZ10)|(1<<UCSZ00);

	// setze Baudrate
	UBRR0H = (((F_CPU / (8UL * BAUDRATE))-1) >> 8) & 0xFF;
	UBRR0L =  ((F_CPU / (8UL * BAUDRATE))-1) & 0xFF;
}

void USART::clearInputBuffer() volatile
{
	uint8_t dummy;
	do
	{
		dummy = UDR0;
		_delay_us(US_PER_BIT * 16); // Warte Übertragungszeit von 16 Bit ab
	}
	while (UCSR0A & (1<<RXC0));

	if(dummy) // taeusche dummy Verwendung vor
		return;
}


void USART::initRX(void) volatile
{
	receive_pos = 0;
}
	
void USART::initTX(void) volatile
{
	while(active);
	send_pos = 0;
	send_crc = 0;
}

void USART::handleRX(void) volatile
{
	receive_buffer[receive_pos++] = UDR0;

	if(receive_pos == 1)
	{
		// starte WDT, da neue Request angekommen ist
		wdt_enable(WDT_TIMEOUT);
		wdt_reset();
	}

	if(receive_pos >= rq_len[receive_buffer[0]]) // last byte of request
	{
		receive_pos = 0;
		nextRequest = true;
	}
}

void USART::handleTX(void) volatile
{
	if(send_pos < send_len)
	{
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = send_buffer[send_pos++];
	}
	else
	{
		active = false;
	}
}

void USART::flush(void) volatile
{
	if(send_pos == 0)
		return;
		
	send_len = send_pos;
	send_pos = 0;	
	active = true;
	
	handleTX();
}


void USART::writeByte(uint8_t b) volatile
{
	send_buffer[send_pos++] = b;
	
	// calc crc
	send_crc ^= b;
	for (uint8_t i = 0; i < 8; i++)
	{
		if (send_crc & 1)
			send_crc ^= CRC7_POLY;
		send_crc >>= 1;
	}
}


void USART::writeInt(uint16_t v) volatile
{
	writeByte(v & 0xFF);
	v >>= 8;
	writeByte(v & 0xFF);
}

void USART::writeStr(const char* str, uint8_t len) volatile
{
	writeByte(len);
	while(len--)
		writeByte(*str++);
}

void USART::writeCRC(void) volatile
{
	writeByte(send_crc);
}

uint8_t USART::readByte() volatile
{
	return receive_buffer[receive_pos++];
}

uint16_t USART::readInt() volatile
{
	uint16_t v = readByte();
	v |= readByte() << 8;
	return v;
}

uint32_t USART::readU32() volatile
{
	uint32_t v = readInt();
	v |= ((uint32_t) readInt()) << 16;
	return v;
}
