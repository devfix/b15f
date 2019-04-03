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

void rqSelfTest()
{
	usart.initTX();
	usart.writeByte(USART::MSG_OK);
	usart.flush();
	
	wdt_disable();
	
	while(1)
	{
		testAll();
	}
}

void rqDigitalWrite0()
{
	usart.initTX();
	uint8_t port = usart.readByte();
	dio0.writePortA(port);

	usart.writeByte(USART::MSG_OK);
	usart.flush();
}

void rqDigitalWrite1()
{
	usart.initTX();
	uint8_t port = usart.readByte();
	dio1.writePortA(port);

	usart.writeByte(USART::MSG_OK);
	usart.flush();
}

void rqDigitalRead0()
{
	usart.initTX();
	uint8_t port = dio0.readPortB();
	usart.writeByte(port);
	usart.flush();
}

void rqDigitalRead1()
{
	usart.initTX();
	uint8_t port = dio1.readPortB();
	usart.writeByte(port);
	usart.flush();
}

void rqReadDipSwitch()
{
	usart.initTX();
	uint8_t port = dsw.readPortB();
	usart.writeByte(port);
	usart.flush();
}

void rqAnalogWrite0()
{
	usart.initTX();
	uint16_t value = usart.readInt();
	dac0.setValue(value);

	usart.writeByte(USART::MSG_OK);
	usart.flush();
}

void rqAnalogWrite1()
{
	usart.initTX();
	uint16_t value = usart.readInt();
	dac1.setValue(value);

	usart.writeByte(USART::MSG_OK);
	usart.flush();
}

void rqAnalogRead()
{
	usart.initTX();
	uint8_t channel = usart.readByte();
	uint16_t value = adu.getValue(channel);
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
	
	count *= delta;
	dio1.writePortA(0xFF);
	
	for(int16_t i = start; i < count; i += delta)
	{
		dac0.setValue(i);
		wdt_reset();

		uint16_t val_a = adu.getValue(channel_a);
		uint16_t val_b = adu.getValue(channel_b);
		
		usart.initTX();
		usart.writeInt(val_a);
		usart.writeInt(val_b);
		usart.flush();
	}
	
	usart.initTX();
	usart.writeByte(USART::MSG_OK);
	usart.flush();
}
