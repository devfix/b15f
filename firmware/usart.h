#ifndef USART_H
#define USART_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>


extern volatile uint8_t receive_buffer[32];
extern volatile uint8_t receive_pos;
extern volatile uint8_t send_buffer[32];
extern volatile uint8_t send_pos;
extern volatile uint8_t send_len;

enum BlockSequence
{
	IDLE = 0,
	LEN  = 1,
	DATA = 2,
	CRC  = 3,
	END  = 4,
};

class USART
{
public:
	void init(void);
	void clearInputBuffer(void);

	void writeByte(uint8_t);
	void writeInt(uint16_t);
	void writeLong(uint32_t);
	void writeStr(const char*, uint8_t);

	uint8_t writeBlock(uint8_t*, uint8_t);
	uint8_t readByte(void);
	uint16_t readInt(void);
	uint32_t readLong(void);
	void write(void);

	void nextByte(uint8_t byte);
	void readBlock(uint8_t*, uint8_t);

	constexpr static uint8_t MSG_OK = 0xFF;
	constexpr static uint8_t MSG_FAIL = 0xFE;

	uint8_t block_pos = 0;

	// constants
	constexpr static uint32_t BAUDRATE       = 115200; // 38400
	constexpr static uint8_t  CRC7_POLY      = 0x91;
	constexpr static uint8_t  MAX_BLOCK_SIZE = 64;
	constexpr static uint8_t  BLOCK_END      = 0x80;
private:
	uint8_t block_buffer[MAX_BLOCK_SIZE + 3]; // don't store BLOCK_END byte
	uint8_t crc;
	BlockSequence seq = BlockSequence::IDLE;
};

#endif // USART_H
