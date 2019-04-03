#ifndef USART_H
#define USART_H

#include <avr/io.h>
#include <util/delay.h>

class USART;
#include "global_vars.h"
#include "requests.h"

class USART
{
public: 
	
	/*******************************
	 * Steuerung der Schnittstelle *
	 *******************************/
	
	/**
	 * Initialisiert die SPI Register
	 */
	void init(void) volatile;
	
	/**
	 * Verwirft Daten im Hardware-Eingangspuffer
	 */
	void clearInputBuffer(void) volatile;
	
	/**
	 * Bereitet Empfang der nächsten Request vor
	 */	
	void initRX(void) volatile;
	
	/**
	 * Bereitet Ausgangspuffer für nächste Übertragung vor
	 */	
	void initTX(void) volatile;
	
	/**
	 * Behandlungsroutine für USART0_RX interrupt
	 */
	void handleRX(void) volatile;
	
	/**
	 * Behandlungsroutine für USART0_TX interrupt
	 */
	void handleTX(void) volatile;
	
	/**
	 * Startet Senden des Ausgangspuffers
	 */
	void flush(void) volatile;
	
	/*******************************/



	/******************
	 * Sendfunktionen *
	 ******************/
	
	/**
	 * Fügt ein Byte dem Ausgangspuffer hinzu
	 * \param b das Byte
	 */
	void writeByte(uint8_t b) volatile;
	
	/**
	 * Fügt ein Integer dem Ausgangspuffer hinzu
	 * \param v das Integer
	 */
	void writeInt(uint16_t v) volatile;
	
	/**
	 * Fügt ein String dem Ausgangspuffer hinzu
	 * \param str der String
	 * \param len Anzahl zu sendender Character 
	 */
	void writeStr(const char* str, uint8_t len) volatile;
	
	/**
	 * Fügt den aktuellen CRC Wert dem Ausgangspuffer hinzu
	 */
	void writeCRC(void) volatile;
	
	/******************/
	
	
	
	/**********************
	 * Empfangsfunktionen *
	 **********************/

	/**
	 * Liest ein Byte aus dem Eingangspuffer
	 * \return gelesenes Byte
	 */
	uint8_t readByte(void) volatile;

	/**
	 * Liest ein Integer aus dem Eingangspuffer
	 * \return gelesenes Integer
	 */
	uint16_t readInt(void) volatile;
	
	/**********************/
	
	// public constants
	constexpr static uint8_t  MSG_OK         = 0xFF;
	constexpr static uint8_t  MSG_FAIL 	     = 0xFE;
	
private:
	// Eingangspuffer
	volatile uint8_t receive_buffer[128];
	volatile uint8_t receive_pos;
	
	// Ausgangspuffer
	volatile uint8_t send_buffer[128];
	volatile uint8_t send_pos;
	volatile uint8_t send_len;
	volatile uint8_t send_crc;
	
	// semaphore
	volatile bool active = false;

	// constants
	constexpr static uint32_t BAUDRATE       = 115200; // 38400
	constexpr static uint8_t  CRC7_POLY      = 0x91;
	constexpr static uint8_t  MAX_BLOCK_SIZE = 64;
	constexpr static uint8_t  BLOCK_END      = 0x80;
	constexpr static uint16_t US_PER_BIT     = 1000000 / BAUDRATE;
};

#endif // USART_H
