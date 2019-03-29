#ifndef USART_H
#define USART_H

#include <cstdint>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
#include "usartexception.h"

class USART
{
public:
	USART(std::string device);
	
	/*************************************************
	 * Methoden für die Verwaltung der Schnittstelle *
	 *************************************************/
	
	/**
	 * Öffnet die USART Schnittstelle
	 * \throws USARTException 
	 */
	void openDevice(void);
	
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
	
	std::string device; // Gerätepfad
	int file_desc = -1; // Linux Dateideskriptor
	uint32_t baudrate = 9600;
	uint8_t timeout = 10; // in Dezisekunden
};


#endif // USART_H
