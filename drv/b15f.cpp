#include "b15f.h"

B15F* B15F::instance = nullptr;

B15F::B15F()
{
}

void B15F::init(void)
{
	int code = system(std::string("stty 38400 -F " + SERIAL_DEVICE).c_str());
	if(code)
	{
		throw DriverException("Konnte serielle Verbindung nicht initialisieren. Ist der Adapter angeschlossen?");
	}
	
	usart.open(SERIAL_DEVICE.c_str());
	
	if(!testConnection())
	{
		throw DriverException("Verbindungstest fehlgeschlagen. Neueste Version im Einsatz?");
	}
}

bool B15F::testConnection(void)
{
	srand (time(NULL));
	uint8_t dummy = rand() % 256;
	writeByte(0); // echo / dummy command for testing
	writeByte(dummy);
	
	uint8_t aw = readByte();
	uint8_t mirror = readByte();
	
	return aw == MSG_OK && mirror == dummy;
}

void B15F::writeByte(uint8_t b)
{
	usart.put(b);
}

uint8_t B15F::readByte()
{
	char b;
	while(1)
	{
		if (usart.get(b))
			return static_cast<uint8_t>(b);
	}
}
	
B15F& B15F::getInstance(void)
{
	if(!instance)
		instance = new B15F();

	return *instance;
}
