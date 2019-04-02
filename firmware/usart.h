#ifndef USART_H
#define USART_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

class USART;
#include "global_vars.h"
#include "requests.h"


typedef void (*handler_t)(void);

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
	
	void init(handler_t handler) volatile;
	void clearInputBuffer(void) volatile;

	void writeByte(uint8_t) volatile;
	void writeInt(uint16_t) volatile;
	void writeStr(const char*, uint8_t) volatile;

	uint8_t readByte(void) volatile;
	uint16_t readInt(void) volatile;
	
	// NEU
	void handleRX(void) volatile;
	void handleTX(void) volatile;
	
	void initRX(void) volatile;
	void initTX(void) volatile;
	void flush(void) volatile;

	// Blockgedöns
	void nextByte(uint8_t byte) volatile;	
	uint8_t writeBlock(uint8_t*, uint8_t) volatile;
	void readBlock(uint8_t*, uint8_t) volatile;

	constexpr static uint8_t MSG_OK = 0xFF;
	constexpr static uint8_t MSG_FAIL = 0xFE;

	uint8_t block_pos = 0;
	
	

	// constants
	constexpr static uint32_t BAUDRATE       = 115200; // 38400
	constexpr static uint8_t  CRC7_POLY      = 0x91;
	constexpr static uint8_t  MAX_BLOCK_SIZE = 64;
	constexpr static uint8_t  BLOCK_END      = 0x80;
	
	volatile uint8_t send_buffer[128];
private:
	static handler_t receive_handler;
	uint8_t block_buffer[MAX_BLOCK_SIZE + 3]; // don't store BLOCK_END byte
	uint8_t crc;
	
	BlockSequence seq = BlockSequence::IDLE;
	
	volatile uint8_t receive_buffer[32];
	volatile uint8_t receive_pos;
	volatile uint8_t send_pos;
	volatile uint8_t send_len;
	volatile bool send_active;
};

#endif // USART_H
