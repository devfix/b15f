#include "usart.h"

void USART::openDevice(std::string device)
{
	file_desc = open(device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
	if(file_desc <= 0)
		throw USARTException("Fehler beim Öffnen des Gerätes");
	
	struct termios options;
	int code = tcgetattr(file_desc, &options);
	if(code)
		throw USARTException("Fehler beim Lesen der Geräteparameter");
	
	options.c_cflag = CS8 | CLOCAL | CREAD; 
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	options.c_cc[VTIME] = timeout;	
    code = cfsetspeed(&options, baudrate);
	if(code)
		throw USARTException("Fehler beim Setzen der Baudrate");
    
	code = tcsetattr(file_desc, TCSANOW, &options);
	if(code)
		throw USARTException("Fehler beim Setzen der Geräteparameter");
	
	clearOutputBuffer();
	clearInputBuffer();
}
	
void USART::closeDevice()
{
	int code = close(file_desc);
	if(code)
		throw USARTException("Fehler beim Schließen des Gerätes");
}
	
void USART::clearInputBuffer()
{
	int code = tcflush(file_desc, TCIFLUSH);
	if(code)
		throw USARTException("Fehler beim Leeren des Eingangspuffers");
}
	
void USART::clearOutputBuffer()
{
	int code = tcflush(file_desc, TCOFLUSH);
	if(code)
		throw USARTException("Fehler beim Leeren des Ausgangspuffers");
}

void USART::writeByte(uint8_t b)
{
	if(write(file_desc, &b, 1) != 1)
		throw USARTException("Fehler beim Senden: writeByte()");
}
	
void USART::writeInt(uint16_t d)
{
	if(write(file_desc, reinterpret_cast<char*>(&d), 2) != 2)
		throw USARTException("Fehler beim Senden: writeInt()");
}
	
uint8_t USART::readByte(void)
{
	char b;
	auto start = std::chrono::steady_clock::now();
	auto end = start;
	uint16_t elapsed = 0;
	while(elapsed < timeout * 100)
	{
		int n_ready;
		int code = ioctl(file_desc, FIONREAD, &n_ready);
		if(code != 0)
				std::cout << "n_ready code: " << code << std::endl;
		
		if(n_ready > 0)
		{				
			//std::cout << code << " \tready: " << n_ready << std::endl;
			
			code = read(file_desc, &b, 1);
			if (code > 0)
				return static_cast<uint8_t>(b);
			if (code < 0)
				std::cout << "usart code: " << code << std::endl;
		}
		
		end = std::chrono::steady_clock::now();
		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	}
	
	if(elapsed >= timeout)
		throw USARTException("Verbindung unterbrochen. (timeout)");
}

uint16_t USART::readInt(void)
{
	return readByte() | readByte() << 8;
}

bool USART::readBlock(uint8_t* buffer, uint16_t offset)
{
	uint8_t len = readByte();
	uint8_t crc = 0;
	buffer += offset;
	
	uint32_t block_timeout = timeout / 10;
	
	// wait for block
	int n_ready;
	uint16_t elapsed = 0;
	auto start = std::chrono::steady_clock::now();
	auto end = start;
	while(elapsed < block_timeout)
	{
		int code = ioctl(file_desc, FIONREAD, &n_ready);
		if(code != 0)
		{
			std::cout <<  "n_ready code: " << code << std::endl;
			return false;
		}
		
		if(n_ready >= len + 1)
			break;
			
		end = std::chrono::steady_clock::now();
		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	}
	if(elapsed >= timeout)
	{
		std::cout  << "block timeout: " << std::endl;
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
		writeByte(0xFF);
		return true;
	}
	else
	{
		writeByte(0xFE);
		return false;
	}
}

uint32_t USART::getBaudrate()
{
	return baudrate;
}

uint8_t USART::getTimeout()
{
	return timeout;
}
	
void USART::setBaudrate(uint32_t baudrate)
{
	this->baudrate = baudrate;
}

void USART::setTimeout(uint8_t timeout)
{
	this->timeout = timeout;
}
