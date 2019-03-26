#ifndef B15F_h
#define B15F_h

#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <cstdint>

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "driverexception.h"

class B15F
{
private:
	B15F(void); // privater Konstruktor
public:
	void init(void);
	void discard(void);
	bool testConnection(void);
	bool testIntConv(void);
	
	inline void writeByte(uint8_t);
	inline void writeInt(uint16_t);
	inline uint8_t readByte(void);
	inline uint16_t readInt(void);
	
	void delay(uint16_t);
	
	static B15F& getInstance(void);

private:
	int usart = -1;
	uint32_t baudrate = 38400;
	uint16_t timeout = 1000;

	static B15F* instance;

// CONSTANTS
	const std::string PRE = "[B15F] ";
	const std::string SERIAL_DEVICE = "/dev/ttyUSB0";
	constexpr static uint8_t MSG_OK = 0xFF;
	constexpr static uint8_t MSG_FAIL = 0xFE;
	
// REQUESTS
	constexpr static uint8_t RQ_DISC = 0;
	constexpr static uint8_t RQ_TEST = 1;
	constexpr static uint8_t RQ_INFO = 2;
	constexpr static uint8_t RQ_INT  = 3;
};

#endif // B15F_h
