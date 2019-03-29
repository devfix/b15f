#include "b15f.h"

B15F* B15F::instance = nullptr;

B15F::B15F()
{
	init();
}

void B15F::init()
{
	
	std::cout << PRE << "Stelle Verbindung mit Adapter her... " << std::flush;
	usart.setBaudrate(BAUDRATE);
	usart.openDevice(SERIAL_DEVICE);	
	std::cout << "OK" << std::endl;
	
	
	delay_ms(1);

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
		delay_ms(RECONNECT_TIMEOUT);
		
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
	usart.clearOutputBuffer();
	for(uint8_t i = 0; i < 8; i++)
	{
		usart.writeByte(RQ_DISC);	// sende discard Befehl (verwerfe input)
		delay_ms((16000 / BAUDRATE) + 1); // warte mindestens eine Millisekunde, gegebenenfalls mehr
	}
	usart.clearInputBuffer();
}

bool B15F::testConnection()
{
	// erzeuge zufälliges Byte
	srand(time(NULL));
	uint8_t dummy = rand() % 256;
	
	usart.writeByte(RQ_TEST);
	usart.writeByte(dummy);
	
	uint8_t aw = usart.readByte();
	uint8_t mirror = usart.readByte();
	
	return aw == MSG_OK && mirror == dummy;
}

bool B15F::testIntConv()
{
	srand(time(NULL));
	uint16_t dummy = rand() % (0xFFFF / 3);
	
	usart.writeByte(RQ_INT);
	usart.writeInt(dummy);
	
	uint16_t aw = usart.readInt();
	return aw == dummy * 3;
}


std::vector<std::string> B15F::getBoardInfo(void)
{
	std::vector<std::string> info;
	
	usart.writeByte(RQ_INFO);
	
	uint8_t n = usart.readByte();
	while(n--)
	{
		uint8_t len = usart.readByte();			
		std::string str;
		
		while(len--)
			str += static_cast<char>(usart.readByte());
			
		info.push_back(str);
	}
	
	uint8_t aw = usart.readByte();	
	if(aw != MSG_OK)
		throw DriverException("Board Info fehlerhalft: code " + std::to_string((int) aw));
	
	return info;
}

bool B15F::digitalWrite0(uint8_t port)
{
	usart.writeByte(RQ_BA0);
	usart.writeByte(port);
	
	uint8_t aw = usart.readByte();	
	return aw == MSG_OK;
}

bool B15F::digitalWrite1(uint8_t port)
{
	usart.writeByte(RQ_BA1);
	usart.writeByte(port);
	
	uint8_t aw = usart.readByte();	
	return aw == MSG_OK;
}

uint8_t B15F::digitalRead0()
{
	usart.writeByte(RQ_BE0);
	return usart.readByte();
}

uint8_t B15F::digitalRead1()
{
	usart.writeByte(RQ_BE1);
	return usart.readByte();
}

bool B15F::analogWrite0(uint16_t value)
{
	usart.writeByte(RQ_AA0);
	usart.writeInt(value);
	
	uint8_t aw = usart.readByte();	
	return aw == MSG_OK;
}

bool B15F::analogWrite1(uint16_t value)
{
	usart.writeByte(RQ_AA1);
	usart.writeInt(value);
	
	uint8_t aw = usart.readByte();	
	return aw == MSG_OK;
}

uint16_t B15F::analogRead(uint8_t channel)
{
	usart.writeByte(RQ_ADC);
	usart.writeByte(channel);
	return usart.readInt();
}

bool B15F::analogSequence(uint8_t channel_a, uint16_t* buffer_a, uint32_t offset_a, uint8_t channel_b, uint16_t* buffer_b, uint32_t offset_b, uint16_t start, int16_t delta, uint16_t count)
{
	buffer_a += offset_a;
	buffer_b += offset_b;
	
	usart.writeByte(RQ_ADC_DAC_STROKE);
	usart.writeByte(channel_a);
	usart.writeByte(channel_b);
	usart.writeInt(start);
	usart.writeInt(static_cast<uint16_t>(delta));
	usart.writeInt(count);
	uint8_t aw = usart.readByte();
	
	if(aw != MSG_OK)
	{
		throw DriverException("Out of sync");
	}
	
	//uint8_t block[5]; // 4 Datenbyte + crc	
	for(uint16_t i = 0; i < count; i++)
	{
		/*bool crc_ok = usart.readBlock(&block[0], 0);
		
		if (!crc_ok)
		{
			std::cout << PRE <<  "bad crc" << std::endl;
			return analogSequence(channel_a, buffer_a, offset_a, channel_b, buffer_b, offset_b, start, delta, count);
		}*/
		buffer_a[i] = usart.readInt();
		buffer_b[i] = usart.readInt();
		//std::cout << buffer_a[i] << " - " << buffer_b[i] << std::endl;
		
		/*buffer_a[i] = ((uint16_t) block[0]) | (((uint16_t) block[1]) << 8);
		buffer_b[i] = ((uint16_t) block[2]) | (((uint16_t) block[3]) << 8);*/
	}
	
	aw = usart.readByte();		
	if(aw == MSG_OK)
		return aw;
	
	std::cout << PRE <<  "Da ging etwas verloren" << std::endl;
	
}

void B15F::delay_ms(uint16_t ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void B15F::delay_us(uint16_t us)
{
	std::this_thread::sleep_for(std::chrono::microseconds(us));
}
	
B15F& B15F::getInstance(void)
{
	if(!instance)
		instance = new B15F();

	return *instance;
}
