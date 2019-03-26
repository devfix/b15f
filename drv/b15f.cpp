#include "b15f.h"

B15F* B15F::instance = nullptr;

B15F::B15F()
{
}

void B15F::init(void)
{
	
	std::cout << PRE << "Stelle Verbindung mit Adapter her... ";
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
	

	// Verbindungstest muss dreimal erfolgreich sein
	std::cout << PRE << "Teste Verbindung... ";
	for(uint8_t i = 0; i < 3; i++)
	{
		if(!testConnection())
		{
			throw DriverException("Verbindungstest fehlgeschlagen. Neueste Version im Einsatz?");
		}
	}
	std::cout << "OK" << std::endl;
	
	writeByte(0xFF);
	writeByte(0x01);
	writeByte(0x02);
	std::cout << readByte() << std::endl;
	std::cout << readByte() << std::endl;
}

bool B15F::testConnection(void)
{
	// erzeuge zufälliges Byte
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
	if(write(usart, &b, 1) != 1)
		throw DriverException("Fehler beim Senden.");
}

void B15F::writeInt(uint16_t v)
{
	// static_cast<char*>(static_cast<void*>(&x));
	writeByte((v >> 8) & 0xFF);
	writeByte((v >> 0) & 0xFF);
}

void B15F::writeLong(uint32_t v)
{
	writeByte((v >> 24) & 0xFF);
	writeByte((v >> 16) & 0xFF);
	writeByte((v >> 8) & 0xFF);
	writeByte((v >> 0) & 0xFF);
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
		/*else if(n < -1)
		{
			std::string msg = "Fehler bei der seriellen Verbindung. (Code: ";
			msg += std::to_string(n);
			msg += ")";
			throw DriverException(msg);
		}*/
			
		end = std::chrono::steady_clock::now();
		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	}
	
	if(elapsed >= timeout)
		throw DriverException("Verbindung unterbrochen. (timeout)");
}

uint16_t B15F::readInt()
{
	return readByte() << 8 | readByte();
}

uint32_t B15F::readLong()
{
	return readByte() << 24 | readByte() << 16 | readByte() << 8 | readByte();
}

void B15F::sleep(uint16_t ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
	
B15F& B15F::getInstance(void)
{
	if(!instance)
		instance = new B15F();

	return *instance;
}
