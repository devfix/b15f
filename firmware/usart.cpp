#include "usart.h"

handler_t USART::receive_handler = nullptr;

void USART::init(handler_t handler) volatile
{
	UCSR0A = _BV(U2X0);
	
	UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0) | _BV(TXCIE0);

	// Einstellen des Datenformats: 8 Datenbits, 1 Stoppbit
	UCSR0C = _BV(UCSZ00) |_BV(UCSZ01);// (1<<URSEL0)|(1<<UCSZ10)|(1<<UCSZ00);

	// setze Baudrate
	UBRR0H = (((F_CPU / (8UL * BAUDRATE))-1) >> 8) & 0xFF;
	UBRR0L =  ((F_CPU / (8UL * BAUDRATE))-1) & 0xFF;

	receive_handler = handler;
	send_active = false;
}

void USART::clearInputBuffer() volatile
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

void USART::handleRX(void) volatile
{
	receive_buffer[receive_pos] = UDR0;
	receive_pos++;

	if(receive_pos >= rq_len[receive_buffer[0]]) // last byte
	{
		receive_pos = 0;
		receive_handler();
	}
}

void USART::handleTX(void) volatile
{
	((MCP23S17*) &beba0)->writePortA(send_pos);
	if(send_pos < send_len)
	{
		while (!(UCSR0A & (1<<UDRE0)));
		UDR0 = send_buffer[send_pos++];
	}
	else
	{
		send_active = false;
	}
}

void USART::initRX(void) volatile
{
	receive_pos = 0;
}
	
void USART::initTX(void) volatile
{
	while(send_active);
		
	send_pos = 0;
}

void USART::flush(void) volatile
{
	if(send_pos == 0)
		return;
		
	send_len = send_pos;
	send_pos = 0;	
	send_active = true;
	
	handleTX();
}

void USART::writeByte(uint8_t b) volatile
{
	send_buffer[send_pos++] = b;
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

uint8_t USART::writeBlock(uint8_t* ptr, uint8_t len) volatile
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

void USART::nextByte(uint8_t byte) volatile
{
	switch(seq)
	{
		case IDLE:
		{
			if(byte > MAX_BLOCK_SIZE)
			{
				clearInputBuffer();
				writeByte(MSG_FAIL);
				seq = BlockSequence::IDLE;
			}
			else
			{
				block_buffer[0] = byte;
				crc = 0;
				block_pos = 0;
				seq = BlockSequence::LEN;
			}
			break;
		}
		case LEN:
		{
			block_buffer[block_pos] = byte;
			seq = BlockSequence::DATA;
			break;
		}
		case DATA:
		{
			block_buffer[block_pos] = byte;
			crc ^= byte;
			for (uint8_t i = 0; i < 8; i++)
			{
				if (crc & 1)
					crc ^= CRC7_POLY;
				crc >>= 1;
			}
			if(block_pos == block_buffer[0])
				seq = BlockSequence::CRC;
			else if(block_pos >= block_buffer[0])
			{
				clearInputBuffer();
				writeByte(MSG_FAIL);
				seq = BlockSequence::IDLE;				
			}
			break;
		}
		case CRC:
		{
			block_buffer[block_pos] = byte;
			crc ^= byte;
			for (uint8_t i = 0; i < 8; i++)
			{
				if (crc & 1)
					crc ^= CRC7_POLY;
				crc >>= 1;
			}
			seq = BlockSequence::END;
			break;
		}
		case END:
		{
			clearInputBuffer();
			writeByte(crc == 0 ? MSG_OK : MSG_FAIL);
			seq = BlockSequence::IDLE;
			break;
		}


	}
	block_pos++;
}

void USART::readBlock(uint8_t* ptr, uint8_t offset) volatile
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

		
		clearInputBuffer(); // leere Eingangspuffer
		
		writeByte(crc == 0 ? MSG_OK : MSG_FAIL);
	}
	while(crc != 0);
}
