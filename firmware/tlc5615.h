#ifndef TLC5615_H
#define TLC5615_H

#include "spi.h"

class TLC5615
{
public:
	/**
	 * Erzeugt ein neues DAC Objekt mit fester Referenz
	 * zur SPI Verbindung und fester SPI-'Adresse'
	 */
	TLC5615(volatile SPI&, SPIADR adr);
	
	/**
	 * Setzt den 10 Bit Wert dieses DACs via SPI
	 */
	void setValue(uint16_t) const volatile;

private:
	// Referenz zur SPI Verbindung
	volatile SPI& spi;
	
	// SPI-'Adresse' dieses DACs
	const SPIADR adr;
};

#endif // TLC5615_H
