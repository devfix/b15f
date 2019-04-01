#ifndef USART_H
#define USART_H

#include <iostream>
#include <cstdint>
#include <chrono>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "usartexception.h"
#include "timeoutexception.h"

class USART
{
public:
	
	/*************************************************
	 * Methoden für die Verwaltung der Schnittstelle *
	 *************************************************/
	
	/**
	 * Öffnet die USART Schnittstelle
	 * \param device Linux-Gerätepfad
	 * \throws USARTException 
	 */
	void openDevice(std::string device);
	
	/**
	 * Schließt die USART Schnittstelle
	 * \throws USARTException 
	 */
	void closeDevice(void);
	
	/**
	 * Verwirft Daten, die bereits im Puffer liegen, aber noch nicht gelesen wurden
	 * \throws USARTException 
	 */
	void clearInputBuffer(void);
	
	/**
	 * Verwirft Daten, die bereits im Puffer liegen, aber noch nicht gesendet wurden
	 * \throws USARTException 
	 */
	void clearOutputBuffer(void);
	
	/*************************************************/
	
	
	
	/*************************************
	 * Methoden für die Datenübertragung *
	 *************************************/
	
	/**
	 * Sendet ein Byte über die USART Schnittstelle
	 * \param b das zu sendende Byte
	 * \throws USARTException 
	 */
	void writeByte(uint8_t b);
	
	/**
	 * Sendet ein Integer über die USART Schnittstelle
	 * \param b das zu sendende Byte
	 * \throws USARTException 
	 */
	void writeInt(uint16_t d);
	
	/**
	 * Empfängt ein Byte über die USART Schnittstelle
	 * \throws USARTException 
	 */
	uint8_t readByte(void);
	
	/**
	 * Empfängt ein Integer über die USART Schnittstelle
	 * \throws USARTException 
	 */
	uint16_t readInt(void);
	
	void writeBlock(uint8_t* buffer, uint16_t offset, uint8_t len);
	bool readBlock(uint8_t* buffer, uint16_t offset);
	
	/*************************************/
	
	
	
	/***************************************
	 * Methoden für einstellbare Parameter *
	 ***************************************/
	
	/**
	 * Liefert die eingestellte Baudrate
	 * <b>Änderungen werden erst nach einem open() wirksam</b>
	 */
	uint32_t getBaudrate(void);
	
	/**
	 * Liefert den eingestellten Timeout (in Dezisekunden)
	 * <b>Änderungen werden erst nach einem open() wirksam</b>
	 */
	uint8_t getTimeout(void);
	
	/**
	 * Setzt die Baudrate
	 * <b>Änderungen werden erst nach einem open() wirksam</b>
	 */
	void setBaudrate(uint32_t baudrate);
	
	/**
	 * Setzt den Timeout (in Dezisekunden)
	 * <b>Änderungen werden erst nach einem open() wirksam</b>
	 */
	void setTimeout(uint8_t timeout);
	
	/***************************************/
	
private:
	
	int file_desc = -1; // Linux Dateideskriptor
	uint32_t baudrate = 9600;
	int TEST = 0;
	uint8_t timeout = 10; // in Dezisekunden
	
	constexpr static uint8_t CRC7_POLY = 0x91;
	constexpr static uint8_t MAX_BLOCK_SIZE = 16;
};


#endif // USART_H
