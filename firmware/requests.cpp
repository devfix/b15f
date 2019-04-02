#include "requests.h"

void rqTestConnection()
{
	uint8_t dummy = ((USART*) &usart)->readByte();
	((USART*) &usart)->writeByte(USART::MSG_OK);
	((USART*) &usart)->writeByte(dummy);
}

void rqBoardInfo()
{
	((USART*) &usart)->writeByte(3); // Anzahl an Strings
	
	((USART*) &usart)->writeStr(DATE, sizeof(DATE));
	((USART*) &usart)->writeStr(TIME, sizeof(TIME));
	((USART*) &usart)->writeStr(FSRC, sizeof(FSRC));
	((USART*) &usart)->writeByte(USART::MSG_OK);
}

void rqTestIntConv()
{
	((USART*) &usart)->writeInt(((USART*) &usart)->readInt() * 3);
}

void rqDigitalWrite0()
{
	uint8_t port = ((USART*) &usart)->readByte();
	((MCP23S17*) &beba0)->writePortA(port);

	((USART*) &usart)->writeByte(USART::MSG_OK);
}

void rqDigitalWrite1()
{
	uint8_t port = ((USART*) &usart)->readByte();
	((MCP23S17*) &beba1)->writePortA(port);

	((USART*) &usart)->writeByte(USART::MSG_OK);
}

void rqDigitalRead0()
{
	uint8_t port = ((MCP23S17*) &beba0)->readPortB();
	((USART*) &usart)->writeByte(port);
}

void rqDigitalRead1()
{
	uint8_t port = ((MCP23S17*) &beba1)->readPortB();
	((USART*) &usart)->writeByte(port);
}

void rqAnalogWrite0()
{
	uint16_t value = ((USART*) &usart)->readInt();
	((TLC5615*) &dac0)->setValue(value);

	((USART*) &usart)->writeByte(USART::MSG_OK);
}

void rqAnalogWrite1()
{
	uint16_t value = ((USART*) &usart)->readInt();
	((TLC5615*) &dac1)->setValue(value);

	((USART*) &usart)->writeByte(USART::MSG_OK);
}

void rqAnalogRead()
{
	uint8_t channel = ((USART*) &usart)->readByte();
	uint16_t value = ((ADU*) &adu)->getValue(channel);
	((USART*) &usart)->writeInt(value);
}

void rqAdcDacStroke()
{	
	uint8_t channel_a = ((USART*) &usart)->readByte();
	uint8_t channel_b = ((USART*) &usart)->readByte();
	
	int16_t start = static_cast<int16_t>(((USART*) &usart)->readInt());
	int16_t delta = static_cast<int16_t>(((USART*) &usart)->readInt());
	int16_t count = static_cast<int16_t>(((USART*) &usart)->readInt());

	((USART*) &usart)->writeByte(USART::MSG_OK);
	
	count *= delta;
	
	for(int16_t i = start; i < count; i += delta)
	{
		((TLC5615*) &dac0)->setValue(i);
		wdt_reset();

		uint16_t val_a = ((ADU*) &adu)->getValue(channel_a);
		uint16_t val_b = ((ADU*) &adu)->getValue(channel_b);
		((USART*) &usart)->writeInt(val_a);
		((USART*) &usart)->writeInt(val_b);

		/*union doubleword
		{
			uint16_t word[2];
			uint8_t  byte[4];
		};

		union doubleword dw;
		dw.word[0] = ((ADU*) &adu)->getValue(channel_a);
		dw.word[1] = ((ADU*) &adu)->getValue(channel_b);
		
		uint8_t ret = 0;
		do
		{
			wdt_reset();
			ret = ((USART*) &usart)->writeBlock(&(dw.byte[0]), 4);

			if(ret == 0)
				return;
		} while(ret != USART::MSG_OK);*/
	}
	
	((USART*) &usart)->writeByte(USART::MSG_OK);
}
