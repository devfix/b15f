#ifndef USART_H
#define USART_H

#include <avr/io.h>
#include <stdint.h>

constexpr uint16_t BAUDRATE = 38400UL; //9600UL//9600

class USART
{
public:
	void init(void);
	void writeByte(uint8_t);
	uint8_t readByte(void);

	constexpr static uint8_t MSG_OK = 0xFF;
	constexpr static uint8_t MSG_FAIL = 0xFE;
};

#endif // USART_H
