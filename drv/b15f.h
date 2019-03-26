#ifndef B15F_h
#define B15F_h

#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstdint>

/*#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>*/

#include "driverexception.h"


class B15F
{
private:
	B15F(void); // privater Konstruktor
public:
	void init(void);
	bool testConnection(void);
	void writeByte(uint8_t);
	uint8_t readByte(void);
	
	static B15F& getInstance(void);

private:
	std::fstream usart; 

	static B15F* instance;

// CONSTANTS
	const std::string SERIAL_DEVICE = "/dev/ttyUSB0";
	constexpr static uint8_t MSG_OK = 0xFF;
	constexpr static uint8_t MSG_FAIL = 0xFE;
};

#endif // B15F_h
