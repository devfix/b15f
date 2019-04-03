#ifndef MCP23S17_H
#define MCP23S17_H

#include "spi.h"

class MCP23S17
{
public:
	/**
	 * Erzeugt ein neues Expander Objekt mit fester Referenz
	 * zur SPI Verbindung und fester SPI-'Adresse'
	 */
	MCP23S17(volatile SPI&, SPIADR adr);
	
	/**
	 * Setzt die Richtung (In/Out) aller Pins von Port A
	 * Bit gesetzt: Pin ist Eingang, sonst Ausgang
	 * \param dir Richtungen für gesamten Port A
	 */
	void setDirA(uint8_t dir) const volatile;
	
	/**
	 * Setzt die Richtung (In/Out) aller Pins von Port B
	 * Bit gesetzt: Pin ist Eingang, sonst Ausgang
	 * \param dir Richtungen für gesamten Port B
	 */
	void setDirB(uint8_t dir) const volatile;
	
	/**
	 * Setzt den Zustand (High/Low) aller Pins von Port A
	 * Bit gesetzt: Pin ist High, sonst Low
	 * \param port Zustände für gesamten Port A
	 */
	void writePortA(uint8_t port) const volatile;
	
	/**
	 * Setzt den Zustand (High/Low) aller Pins von Port B
	 * Bit gesetzt: Pin ist High, sonst Low
	 * \param port Zustände für gesamten Port B
	 */
	void writePortB(uint8_t port) const volatile;
	
	/**
	 * Liest den Zustand (High/Low) aller Pins von Port A
	 * \return Zustände für gesamten Port A
	 */
	uint8_t readPortA(void) const volatile;
	
	/**
	 * Liest den Zustand (High/Low) aller Pins von Port B
	 * \return Zustände für gesamten Port B
	 */
	uint8_t readPortB(void) const volatile;

private:
	// Referenz zur SPI Verbindung
	volatile SPI& spi;
	
	// SPI-'Adresse' dieses Expanders
	const SPIADR adr;

	// constants
	constexpr static uint8_t MCP23S17_DIRA   = 0x00;
	constexpr static uint8_t MCP23S17_DIRB   = 0x01;
	constexpr static uint8_t MCP23S17_PORTA  = 0x12;
	constexpr static uint8_t MCP23S17_PORTB  = 0x13;
	constexpr static uint8_t MCP23S17_READ   = 0x01;
	constexpr static uint8_t MCP23S17_WRITE  = 0x00;
	constexpr static uint8_t MCP23S17_OPCODE = 0x40;
};

#endif // MCP23S17_H
