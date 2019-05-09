#include "b15f.h"

B15F* B15F::instance = nullptr;
errorhandler_t B15F::errorhandler = nullptr;

B15F::B15F()
{
	init();
}

void B15F::init()
{
	
	std::string device = exec("bash -c 'ls /dev/ttyUSB*'");
	while(device.find(' ') != std::string::npos || device.find('\n') != std::string::npos || device.find('\t') != std::string::npos)
		device.pop_back();
			
	if(device.length() == 0)
		throw DriverException("Adapter nicht gefunden");
		
	std::cout << PRE << "Verwende Adapter: " << device << std::endl;
	
	
	
	std::cout << PRE << "Stelle Verbindung mit Adapter her... " << std::flush;
	usart.setBaudrate(BAUDRATE);
	usart.openDevice(device);	
	std::cout << "OK" << std::endl;
	
	

	std::cout << PRE << "Teste Verbindung... " << std::flush;	
	uint8_t tries = 3;
	while(tries--)
	{
		// verwerfe Daten, die µC noch hat
		//discard();
		
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
	uint8_t tries = RECONNECT_TRIES;		
	while(tries-- && false)
	{
		delay_ms(RECONNECT_TIMEOUT);
		
		discard();
		
		if(testConnection())
			return;
			
	}
	
	throw DriverException("Verbindung kann nicht repariert werden");
}

void B15F::discard(void)
{
	usart.clearOutputBuffer();
	for(uint8_t i = 0; i < 16; i++)
	{
		usart.writeByte(RQ_DISC);	// sende discard Befehl (verwerfe input)
		delay_ms(4);
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
				
		while(len--) {
			str += static_cast<char>(usart.readByte());
		}
		
		info.push_back(str);
	}
	
	uint8_t aw = usart.readByte();	
	if(aw != MSG_OK)
		throw DriverException("Board Info fehlerhalft: code " + std::to_string((int) aw));
	
	return info;
}

bool B15F::activateSelfTestMode()
{
	usart.writeByte(RQ_ST);
	
	uint8_t aw = usart.readByte();	
	return aw == MSG_OK;
}

bool B15F::digitalWrite0(uint8_t port)
{
	usart.writeByte(RQ_BA0);
	usart.writeByte(port);
	
	uint8_t aw = usart.readByte();
	delay_us(10);
	return aw == MSG_OK;
}

bool B15F::digitalWrite1(uint8_t port)
{
	usart.writeByte(RQ_BA1);
	usart.writeByte(port);
	
	uint8_t aw = usart.readByte();
	delay_us(10);
	return aw == MSG_OK;
}

uint8_t B15F::digitalRead0()
{
	usart.clearInputBuffer();
	usart.writeByte(RQ_BE0);
	uint8_t byte = usart.readByte();
	delay_us(10);
	return byte;
}

uint8_t B15F::digitalRead1()
{
	usart.clearInputBuffer();
	usart.writeByte(RQ_BE1);
	uint8_t byte = usart.readByte();
	delay_us(10);
	return byte;
}

uint8_t B15F::readDipSwitch()
{
	usart.clearInputBuffer();
	usart.writeByte(RQ_DSW);
	uint8_t byte = usart.readByte();
	delay_us(10);
	return byte;
}

bool B15F::analogWrite0(uint16_t value)
{
	usart.writeByte(RQ_AA0);
	usart.writeInt(value);
	
	uint8_t aw = usart.readByte();
	delay_us(10);
	return aw == MSG_OK;
}

bool B15F::analogWrite1(uint16_t value)
{
	usart.writeByte(RQ_AA1);
	usart.writeInt(value);
	
	uint8_t aw = usart.readByte();
	delay_us(10);
	return aw == MSG_OK;
}

uint16_t B15F::analogRead(uint8_t channel)
{
	usart.clearInputBuffer();
	if(channel > 7)
		throw DriverException("Bad ADC channel: " + std::to_string(channel));
	
	uint8_t rq[] = {
		RQ_ADC,
		channel
	};
	
	int n_sent = usart.write_timeout(&rq[0], 0, sizeof(rq), 1000);
	if(n_sent != sizeof(rq))
		throw DriverException("Sent failed");
	
	uint16_t adc = usart.readInt();
	
	if(adc > 1023)
		throw DriverException("Bad ADC data detected (1)");
	return adc;
}

void B15F::analogSequence(uint8_t channel_a, uint16_t* buffer_a, uint32_t offset_a, uint8_t channel_b, uint16_t* buffer_b, uint32_t offset_b, uint16_t start, int16_t delta, uint16_t count)
{
	buffer_a += offset_a;
	buffer_b += offset_b;
	
	usart.clearInputBuffer();
	usart.writeByte(RQ_ADC_DAC_STROKE);
	usart.writeByte(channel_a);
	usart.writeByte(channel_b);
	usart.writeInt(start);
	usart.writeInt(static_cast<uint16_t>(delta));
	usart.writeInt(count);
	
	
	for(uint16_t i = 0; i < count; i++)
	{
		buffer_a[i] = usart.readInt();
		buffer_b[i] = usart.readInt();
		if(buffer_a[i] > 1023 || buffer_b[i] > 1023)
			throw DriverException("Bad ADC data detected (2)");
	}
	
	uint8_t aw = usart.readByte();		
	if(aw != MSG_OK)		
		throw DriverException("Sequenz unterbrochen");
	
	delay_us(10);
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

// https://stackoverflow.com/a/478960
std::string B15F::exec(std::string cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


void B15F::abort(std::string msg)
{
	DriverException ex(msg);
	abort(ex);
}

void B15F::abort(std::exception& ex)
{
	if(errorhandler)
		errorhandler(ex);
	else
	{
		std::cerr << "NOTICE: B15F::errorhandler not set" << std::endl;
		throw ex;
	}
}

void B15F::setAbortHandler(errorhandler_t func)
{
	errorhandler = func;
}
