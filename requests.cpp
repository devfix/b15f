#include "requests.h"

void rqTestConnection()
{
	uint8_t dummy = usart.readByte();
	usart.writeByte(USART::MSG_OK);
	usart.writeByte(dummy);
}

void rqBoardInfo()
{
	usart.writeByte(3); // Anzahl an Strings
	
	usart.writeStr(DATE, sizeof(DATE));
	usart.writeStr(TIME, sizeof(TIME));
	usart.writeStr(FSRC, sizeof(FSRC));
	usart.writeByte(USART::MSG_OK);
}

void rqTestIntConv()
{
	usart.writeInt(usart.readInt() * 3);
}

void rqDigitalWrite0()
{
	uint8_t port = usart.readByte();
	beba0.writePortA(port);

	usart.writeByte(USART::MSG_OK);
}

void rqDigitalWrite1()
{
	uint8_t port = usart.readByte();
	beba1.writePortA(port);

	usart.writeByte(USART::MSG_OK);
}

void rqDigitalRead0()
{
	uint8_t port = beba0.readPortB();
	usart.writeByte(port);
}

void rqDigitalRead1()
{
	uint8_t port = beba1.readPortB();
	usart.writeByte(port);
}

void rqAnalogWrite0()
{
	uint16_t value = usart.readInt();
	dac0.setValue(value);

	usart.writeByte(USART::MSG_OK);
}

void rqAnalogWrite1()
{
	uint16_t value = usart.readInt();
	dac1.setValue(value);

	usart.writeByte(USART::MSG_OK);
}

void rqAnalogRead()
{
	uint8_t channel = usart.readByte();
	uint16_t value = adu.getValue(channel);
	usart.writeInt(value);
}

void rqAdcDacStroke()
{	
	uint8_t channel_a = usart.readByte();
	uint8_t channel_b = usart.readByte();
	
	int16_t start = static_cast<int16_t>(usart.readInt());
	int16_t delta = static_cast<int16_t>(usart.readInt());
	int16_t count = static_cast<int16_t>(usart.readInt());

	usart.writeByte(USART::MSG_OK);
	
	count *= delta;
	
	for(int16_t i = start; i < count; i += delta)
	{
		dac0.setValue(i);
		wdt_reset();

		uint16_t val_a = adu.getValue(channel_a);
		uint16_t val_b = adu.getValue(channel_b);
		usart.writeInt(val_a);
		usart.writeInt(val_b);

		/*union doubleword
		{
			uint16_t word[2];
			uint8_t  byte[4];
		};

		union doubleword dw;
		dw.word[0] = adu.getValue(channel_a);
		dw.word[1] = adu.getValue(channel_b);
		
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
