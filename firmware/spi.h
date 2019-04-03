#ifndef SPI_H
#define SPI_H

#include <avr/io.h>

enum SPIADR {
	AA0    = 0,
	AA1    = 1,
	BEBA0  = 2,
	BEBA1  = 3,
	EXT    = 4,
	SWITCH = 5,
	NONE   = 7,
};

class SPI
{
public:
	
	/**
	 * Initialisiert die SPI Register
	 */
	void init(void) const volatile;
	
	/**
	 * Behandlungsroutine für SPI_STC interrupt
	 */
	void handleTransfer(void) volatile;
	
	/**
	 * Fügt ein Byte dem SPI Puffer an
	 */
	void addByte(uint8_t b) volatile;
	
	/**
	 * Startet die Übertragung SPI Puffers
	 * Die Werte im Puffer werden mit den empfangen Werten überschrieben
	 * \param adr Adressierung des Empfängers (Slave Device)
	 */
	void transfer(SPIADR adr) volatile;
	
	/**
	 * Blockiert, bis laufende SPI Vorgänge beendet sind
	 * Ist SPI gerade inaktiv, wird die Methode sofort beendet
	 */
	void wait(void) volatile;
	
	/**
	 * SPI Puffer Größe
	 * Maximale Anzahl an Bytes, die auf einmal an ein Gerät
	 * gesendet & empfangen werden können
	 */
	constexpr static uint8_t BUFFER_SIZE = 8;
	
	/**
	 * SPI Puffer
	 * Vor Zugriff unbedingt wait() aufrufen
	 * Es sollte nur lesend zugegriffen werden, für schreiben siehe addByte()
	 */
	volatile uint8_t buffer[BUFFER_SIZE];

private:
	/**
	 * Setzt die CS Leitung für den gewünschten Slave
	 */
	void setAdr(SPIADR adr) const volatile;
	
	// Variablen für die Pufferverwaltung
	volatile uint8_t index = 0;
	volatile uint8_t length = 0;
	volatile bool active = false;
	
	// Constants
	constexpr static uint8_t SLSL  = PB4;
	constexpr static uint8_t MOSI  = PB5;
	constexpr static uint8_t MISO  = PB6;
	constexpr static uint8_t SCLK  = PB7;	
	constexpr static uint8_t DMUX1 = PD2;
	constexpr static uint8_t DMUX2 = PD3;
	constexpr static uint8_t DMUX3 = PD4;
};

#endif // SPI_H
