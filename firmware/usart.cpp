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

void USART::flush()
{
	uint8_t dummy;
	do
	{
		dummy = UDR0;
		_delay_us((1000000 / BAUDRATE) * 16); // Warte Übertragungszeit von 16 Bit ab
	}
	while (UCSR0A & (1<<RXC0));

	if(dummy) // taeusche dummy Verwendung vor
		return;
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

void USART::writeStr(const char* str, uint8_t len)
{
	writeByte(len);
	while(len--)
		writeByte(*str++);
}

uint8_t USART::writeBlock(uint8_t* ptr, uint8_t len)
{
	writeByte(len);

	uint8_t crc = 0;
	while(len--)
    {
		writeByte(*ptr);
		crc ^= *ptr++;
		for (uint8_t i = 0; i < 8; i++)
		{
			if (crc & 1)
				crc ^= CRC7_POLY;
			crc >>= 1;
		}
	}

	writeByte(crc);

	return readByte();
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

void USART::readBlock(uint8_t* ptr, uint8_t offset)
{
	ptr += offset;
	uint8_t crc = 0x7F;
	do
	{
		uint8_t len = readByte();

		if(len == 0x80) // out of sync, war bereits stoppbyte
		{
			writeByte(MSG_FAIL);
			continue;
		}
		else if(len > MAX_BLOCK_SIZE)
			len = 0;

		crc = 0;

		for(uint8_t k = 0; k <= len; k++) // len + 1 Durchgänge (+ crc)
		{
			uint8_t next = readByte();

			crc ^= next;
			for (uint8_t i = 0; i < 8; i++)
			{
				if (crc & 1)
					crc ^= CRC7_POLY;
				crc >>= 1;
			}

			if(k < len)
				ptr[k] = next;
		}

		
		flush(); // leere Eingangspuffer
		
		writeByte(crc == 0 ? MSG_OK : MSG_FAIL);
	}
	while(crc != 0);
}
