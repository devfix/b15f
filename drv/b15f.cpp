#include "b15f.h"

B15F* B15F::instance = nullptr;

B15F::B15F()
{
}

void B15F::init()
{
	
	std::cout << PRE << "Stelle Verbindung mit Adapter her... " << std::flush;
	int code = system(std::string("stty " + std::to_string(BAUDRATE) + " -F " + SERIAL_DEVICE).c_str());
	if(code)
	{
		throw DriverException("Konnte serielle Verbindung nicht initialisieren. Ist der Adapter angeschlossen?");
	}
	
	usart = open(SERIAL_DEVICE.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
	struct termios options;
	tcgetattr(usart, &options);
	options.c_cflag = CS8 | CLOCAL | CREAD; 
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	options.c_cc[VTIME]=100; // timeout in Dezisekunden
    cfsetspeed(&options, BAUDRATE);	
	tcsetattr(usart, TCSANOW, &options);
	tcflush(usart, TCIOFLUSH); // leere Puffer in beiden Richtungen
	
	std::cout << "OK" << std::endl;
	
	delay(1);

	std::cout << PRE << "Teste Verbindung... " << std::flush;	
	uint8_t tries = 3;
	while(tries--)
	{
		// verwerfe Daten, die µC noch hat
		discard();
		
		if(!testConnection())
			continue;
		
		if(!testIntConv())
			continue;
			
		break;
	}
	if(tries == 0)
			throw DriverException("Verbindungstest fehlgeschlagen. Neueste Version im Einsatz?");
	std::cout << "OK" << std::endl;
	
	// Gib board info aus
	std::vector<std::string> info = getBoardInfo();
	std::cout << PRE << "AVR Firmware Version: " << info[0] << " um " << info[1] << " Uhr (" << info[2] << ")" << std::endl;

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
	tcflush(usart, TCOFLUSH); // leere Ausgangspuffer
	for(uint8_t i = 0; i < 8; i++)
	{
		writeByte(RQ_DISC);	// sende discard Befehl (verwerfe input)
		delay((16000 / BAUDRATE) + 1); // warte mindestens eine Millisekunde, gegebenenfalls mehr
	}
	tcflush(usart, TCIFLUSH); // leere Eingangspuffer
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


std::vector<std::string> B15F::getBoardInfo(void)
{
	try
	{
		std::vector<std::string> info;
		
		writeByte(RQ_INFO);
		uint8_t n = readByte();
		while(n--)
		{
			uint8_t len = readByte();			
			std::string str;
			
			while(len--)
				str += static_cast<char>(readByte());
				
			info.push_back(str);
		}
		
		uint8_t aw = readByte();
		
		if(aw != MSG_OK)
			throw DriverException("Board Info fehlerhalft");
		
		return info;
	}
	catch(DriverException& de)
	{
		reconnect();
		return getBoardInfo();
	}
}

bool B15F::digitalWrite0(uint8_t port)
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
		return digitalWrite0(port);
	}
}

bool B15F::digitalWrite1(uint8_t port)
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
		return digitalWrite1(port);
	}
}

uint8_t B15F::digitalRead0()
{
	try
	{
		writeByte(RQ_BE0);
		return readByte();
	}
	catch(DriverException& de)
	{
		reconnect();
		return digitalRead0();
	}
}

uint8_t B15F::digitalRead1()
{
	try
	{
		writeByte(RQ_BE1);
		return readByte();
	}
	catch(DriverException& de)
	{
		reconnect();
		return digitalRead1();
	}
}

bool B15F::analogWrite0(uint16_t value)
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
		return analogWrite0(value);
	}
}

bool B15F::analogWrite1(uint16_t value)
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
		return analogWrite1(value);
	}
}

uint16_t B15F::analogRead(uint8_t channel)
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
		return analogRead(channel);
	}
}

bool B15F::analogEingabeSequenz(uint8_t channel_a, uint16_t* buffer_a, uint32_t offset_a, uint8_t channel_b, uint16_t* buffer_b, uint32_t offset_b, uint16_t start, int16_t delta, uint16_t count)
{
	
	discard();
	
	try
	{
		writeByte(RQ_ADC_DAC_STROKE);
		writeByte(channel_a);
		writeByte(channel_b);
		writeInt(start);
		writeInt(static_cast<uint16_t>(delta));
		writeInt(count);
		uint8_t aw = readByte();
		
		if(aw != MSG_OK)
		{
			std::cout << PRE << "Out of sync" << std::endl;
			return analogEingabeSequenz(channel_a, buffer_a, offset_a, channel_b, buffer_b, offset_b, start, delta, count);
		}
		
		uint8_t block[4];	
		for(uint16_t i = 0; i < count; i++)
		{
			bool crc_ok = readBlock(&block[0], 0);
			
			if (!crc_ok)
			{
				std::cout << PRE <<  "bad crc" << std::endl;
				return analogEingabeSequenz(channel_a, buffer_a, offset_a, channel_b, buffer_b, offset_b, start, delta, count);
			}
			
			
			buffer_a[offset_a + i] = ((uint16_t) block[0]) | (((uint16_t) block[1]) << 8);
			buffer_b[offset_b + i] = ((uint16_t) block[2]) | (((uint16_t) block[3]) << 8);
		}
		
		aw = readByte();		
		if(aw == MSG_OK)
			return aw;
		
		std::cout << PRE <<  "Da ging etwas verloren" << std::endl;
		return analogEingabeSequenz(channel_a, buffer_a, offset_a, channel_b, buffer_b, offset_b, start, delta, count);
	}
	catch(DriverException& de)
	{
		reconnect();
		return analogEingabeSequenz(channel_a, buffer_a, offset_a, channel_b, buffer_b, offset_b, start, delta, count);
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
		int n_ready;
		int code = ioctl(usart, FIONREAD, &n_ready);
		if(code != 0)
				std::cout << PRE << "n_ready code: " << code << std::endl;
		
		if(n_ready > 0)
		{				
			//std::cout << code << " \tready: " << n_ready << std::endl;
			
			code = read(usart, &b, 1);
			if (code > 0)
				return static_cast<uint8_t>(b);
			if (code < 0)
				std::cout << PRE << "usart code: " << code << std::endl;
		}
		
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

bool B15F::readBlock(uint8_t* buffer, uint16_t offset)
{
	uint8_t len = readByte();
	uint8_t crc = 0;
	buffer += offset;
	
	// wait for block
	int n_ready;
	uint16_t elapsed = 0;
	auto start = std::chrono::steady_clock::now();
	auto end = start;
	while(elapsed < block_timeout)
	{
		int code = ioctl(usart, FIONREAD, &n_ready);
		if(code != 0)
		{
			std::cout << PRE << "n_ready code: " << code << std::endl;
			return false;
		}
		
		if(n_ready >= len + 1)
			break;
			
		end = std::chrono::steady_clock::now();
		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	}
	if(elapsed >= timeout)
	{
		std::cout << PRE << "block timeout: " << std::endl;
		return false;
	}
	
	while(len--)
	{
		*buffer = readByte();
		
		crc ^= *buffer++;
		for (uint8_t i = 0; i < 8; i++)
		{
			if (crc & 1)
				crc ^= CRC7_POLY;
			crc >>= 1;
		}
	}
	
	crc ^= readByte();
	for (uint8_t i = 0; i < 8; i++)
	{
		if (crc & 1)
			crc ^= CRC7_POLY;
		crc >>= 1;
	}
	
	if(TEST == 1)
		crc = 1;
	if(TEST > 100)
		TEST = 0;
	
	if (crc == 0)
	{
		writeByte(MSG_OK);
		return true;
	}
	else
	{
		writeByte(MSG_FAIL);
		return false;
	}
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
