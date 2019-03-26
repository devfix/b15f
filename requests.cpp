#include "requests.h"

void rqTestConnection()
{
	uint8_t dummy = usart.readByte();
	usart.writeByte(USART::MSG_OK);
	usart.writeByte(dummy);
}

void rqBoardInfo()
{

}

void rqTestIntConv()
{
	usart.writeInt(usart.readInt() * 3);
}

void rqDigitalWrite0()
{
	uint8_t port = usart.readByte();
	beba0.writePortA(port);

	if(ACK_MODE)
		usart.writeByte(USART::MSG_OK);
}

void rqDigitalWrite1()
{
	uint8_t port = usart.readByte();
	beba1.writePortA(port);

	if(ACK_MODE)
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

	if(ACK_MODE)
		usart.writeByte(USART::MSG_OK);
}

void rqAnalogWrite1()
{
	uint16_t value = usart.readInt();
	dac1.setValue(value);

	if(ACK_MODE)
		usart.writeByte(USART::MSG_OK);
}

void rqAnalogRead()
{
	uint8_t channel = usart.readByte();
	uint16_t value = adu.getValue(channel);
	usart.writeInt(value);
}
