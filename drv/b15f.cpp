#include "b15f.h"

B15F* B15F::instance = nullptr;

B15F::B15F()
{
}

void B15F::init()
{
	
	std::cout << PRE << "Stelle Verbindung mit Adapter her... " << std::flush;
	int code = system(std::string("stty 38400 -F " + SERIAL_DEVICE).c_str());
	if(code)
	{
		throw DriverException("Konnte serielle Verbindung nicht initialisieren. Ist der Adapter angeschlossen?");
	}
	
	usart = open(SERIAL_DEVICE.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
	struct termios options;
	tcgetattr(usart, &options);
	options.c_cflag = baudrate | CS8 | CLOCAL | CREAD; 
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	options.c_cc[VTIME]=30;
	tcsetattr(usart, TCSANOW, &options);
	tcflush(usart, TCIFLUSH);
	
	std::cout << "OK" << std::endl;
	
	// verwerfe Daten, die µC noch hat
	discard();

	// Verbindungstest muss dreimal erfolgreich sein
	std::cout << PRE << "Teste Verbindung... " << std::flush;
	for(uint8_t i = 0; i < 3; i++)
		if(!testConnection())
			throw DriverException("Verbindungstest fehlgeschlagen. Neueste Version im Einsatz?");
	std::cout << "OK" << std::endl;


	std::cout << PRE << "Teste Integer Konvertierung... " << std::flush;
	for(uint8_t i = 0; i < 3; i++)
		if(!testIntConv())
			throw DriverException("Konvertierung fehlgeschlagen.");
	std::cout << "OK" << std::endl;
	
	while(1)
	{
		digitaleAusgabe0(0xFF);
		digitaleAusgabe0(0x00);
		//analogeEingabe(0);
		/*for(uint16_t i = 0; i < 1024; )
		{
			i = analogeEingabe(0);
			analogeAusgabe0(i);
			delay(0);
		}*/
	}
	
}

void B15F::reconnect()
{
	std::cout << PRE << "Verbindung unterbrochen, stelle Verbindung neu her: " << std::flush;
		
	uint8_t tries = RECONNECT_TRIES;		
	while(tries--)
	{
		delay(RECONNECT_TIMEOUT);
		
		discard();
		
		if(testConnection())
		{
			std::cout << "OK" << std::endl << std::flush;
			return;
		}
			
	}
	
	throw DriverException("Verbindung kann nicht repariert werden");
}

void B15F::discard(void)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		writeByte(RQ_DISC);	// sende discard Befehl (verwerfe input)
		delay(1);
		tcflush(usart, TCIFLUSH); // leere Puffer
	}
}

bool B15F::testConnection()
{
	// erzeuge zufälliges Byte
	srand(time(NULL));
	uint8_t dummy = rand() % 256;
	
	writeByte(RQ_TEST);
	writeByte(dummy);
	
	uint8_t aw = readByte();
	uint8_t mirror = readByte();
	
	return aw == MSG_OK && mirror == dummy;
}

bool B15F::testIntConv()
{
	srand(time(NULL));
	uint16_t dummy = rand() % (0xFFFF / 3);
	
	writeByte(RQ_INT);
	writeInt(dummy);
	
	uint16_t aw = readInt();
	return aw == dummy * 3;
}



bool B15F::digitaleAusgabe0(uint8_t port)
{
	try
	{
		writeByte(RQ_BA0);
		writeByte(port);
		
		uint8_t aw = readByte();	
		return aw == MSG_OK;
	}
	catch(DriverException& de)
	{
		reconnect();
		return digitaleAusgabe0(port);
	}
}

bool B15F::digitaleAusgabe1(uint8_t port)
{
	try
	{
		writeByte(RQ_BA1);
		writeByte(port);
		
		uint8_t aw = readByte();	
		return aw == MSG_OK;
	}
	catch(DriverException& de)
	{
		reconnect();
		return digitaleAusgabe1(port);
	}
}

uint8_t B15F::digitaleEingabe0()
{
	try
	{
		writeByte(RQ_BE0);
		return readByte();
	}
	catch(DriverException& de)
	{
		reconnect();
		return digitaleEingabe0();
	}
}

uint8_t B15F::digitaleEingabe1()
{
	try
	{
		writeByte(RQ_BE1);
		return readByte();
	}
	catch(DriverException& de)
	{
		reconnect();
		return digitaleEingabe1();
	}
}

bool B15F::analogeAusgabe0(uint16_t value)
{
	try
	{
		writeByte(RQ_AA0);
		writeInt(value);
		
		uint8_t aw = readByte();	
		return aw == MSG_OK;
	}
	catch(DriverException& de)
	{
		reconnect();
		return analogeAusgabe0(value);
	}
}

bool B15F::analogeAusgabe1(uint16_t value)
{
	try
	{
		writeByte(RQ_AA1);
		writeInt(value);
		
		uint8_t aw = readByte();	
		return aw == MSG_OK;
	}
	catch(DriverException& de)
	{
		reconnect();
		return analogeAusgabe1(value);
	}
}

uint16_t B15F::analogeEingabe(uint8_t channel)
{
	try
	{
		writeByte(RQ_ADC);
		writeByte(channel);
		return readInt();
	}
	catch(DriverException& de)
	{
		reconnect();
		return analogeEingabe(channel);
	}
}



void B15F::writeByte(uint8_t b)
{
	if(write(usart, &b, 1) != 1)
		throw DriverException("Fehler beim Senden. (byte)");
}

void B15F::writeInt(uint16_t v)
{
	if(write(usart, reinterpret_cast<char*>(&v), 2) != 2)
		throw DriverException("Fehler beim Senden. (int)");
}

uint8_t B15F::readByte()
{
	char b;
	auto start = std::chrono::steady_clock::now();
	auto end = start;
	uint16_t elapsed = 0;
	while(elapsed < timeout)
	{
		int n = read(usart, &b, 1);
		if (n > 0)
			return static_cast<uint8_t>(b);
			
		end = std::chrono::steady_clock::now();
		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	}
	
	if(elapsed >= timeout)
		throw DriverException("Verbindung unterbrochen. (timeout)");
}

uint16_t B15F::readInt()
{
	return readByte() | readByte() << 8;
}

void B15F::delay(uint16_t ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
	
B15F& B15F::getInstance(void)
{
	if(!instance)
		instance = new B15F();

	return *instance;
}
