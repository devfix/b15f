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
