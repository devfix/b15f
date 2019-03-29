#include "usart.h"

USART::USART(std::string device) : device(device)
{
}

void USART::openDevice()
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
