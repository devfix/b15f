#ifndef USART_H
#define USART_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

constexpr uint32_t BAUDRATE = 38400; // 38400
constexpr uint8_t  CRC7_POLY = 0x91;

class USART
{
public:
	void init(void);

	void writeByte(uint8_t);
	void writeInt(uint16_t);
	void writeLong(uint32_t);
	void writeStr(const char*, uint8_t);
	uint8_t writeBlock(uint8_t*, uint8_t);
	uint8_t readByte(void);
	uint16_t readInt(void);
	uint32_t readLong(void);

	constexpr static uint8_t MSG_OK = 0xFF;
	constexpr static uint8_t MSG_FAIL = 0xFE;
};

#endif // USART_H
