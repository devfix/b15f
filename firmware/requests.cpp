#include "requests.h"

void rqTestConnection()
{
	usart.initTX();
	uint8_t dummy = usart.readByte();
	usart.writeByte(USART::MSG_OK);
	usart.writeByte(dummy);
	usart.flush();
}

void rqBoardInfo()
{
	usart.initTX();
	usart.writeByte(3); // Anzahl an Strings
	usart.writeStr(DATE, sizeof(DATE));
	usart.writeStr(TIME, sizeof(TIME));
	usart.writeStr(FSRC, sizeof(FSRC));
	usart.writeByte(USART::MSG_OK);
	usart.flush();
}

void rqTestIntConv()
{
	usart.initTX();
	uint16_t d = usart.readInt();
	usart.writeInt(d * 3);
	usart.flush();
}

void rqDigitalWrite0()
{
	usart.initTX();
	uint8_t port = usart.readByte();
	((MCP23S17*) &beba0)->writePortA(port);

	usart.writeByte(USART::MSG_OK);
	usart.flush();
}

void rqDigitalWrite1()
{
	usart.initTX();
	uint8_t port = usart.readByte();
	((MCP23S17*) &beba1)->writePortA(port);

	usart.writeByte(USART::MSG_OK);
	usart.flush();
}

void rqDigitalRead0()
{
	usart.initTX();
	uint8_t port = ((MCP23S17*) &beba0)->readPortB();
	usart.writeByte(port);
	usart.flush();
}

void rqDigitalRead1()
{
	usart.initTX();
	uint8_t port = ((MCP23S17*) &beba1)->readPortB();
	usart.writeByte(port);
	usart.flush();
}

void rqAnalogWrite0()
{
	usart.initTX();
	uint16_t value = usart.readInt();
	((TLC5615*) &dac0)->setValue(value);

	usart.writeByte(USART::MSG_OK);
	usart.flush();
}

void rqAnalogWrite1()
{
	usart.initTX();
	uint16_t value = usart.readInt();
	((TLC5615*) &dac1)->setValue(value);

	usart.writeByte(USART::MSG_OK);
	usart.flush();
}

void rqAnalogRead()
{
	usart.initTX();
	uint8_t channel = usart.readByte();
	uint16_t value = ((ADU*) &adu)->getValue(channel);
	usart.writeInt(value);
	usart.flush();
}

void rqAdcDacStroke()
{	
	uint8_t channel_a = usart.readByte();
	uint8_t channel_b = usart.readByte();
	
	int16_t start = static_cast<int16_t>(usart.readInt());
	int16_t delta = static_cast<int16_t>(usart.readInt());
	int16_t count = static_cast<int16_t>(usart.readInt());

	//usart.writeByte(USART::MSG_OK);
	
	count *= delta;
	((MCP23S17*) &beba1)->writePortA(0xFF);
	
	for(int16_t i = start; i < count; i += delta)
	{
		((TLC5615*) &dac0)->setValue(i);
		wdt_reset();

		uint16_t val_a = ((ADU*) &adu)->getValue(channel_a);
		uint16_t val_b = ((ADU*) &adu)->getValue(channel_b);
		usart.writeInt(val_a);
		usart.writeInt(val_b);

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
			ret = usart.writeBlock(&(dw.byte[0]), 4);

			if(ret == 0)
				return;
		} while(ret != USART::MSG_OK);*/
	}
	
	usart.writeByte(USART::MSG_OK);
}
