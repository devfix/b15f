#ifndef ADC_H
#define ADC_H

#include <avr/io.h>

class ADU
{
public:

	/**
	 * Konfiguriert die ADC Register
	 */
	void init(void) volatile;
	
	/**
	 * Behandlungsroutine für ADC interrupt
	 */
	void handleConversionComplete(void) volatile;
	
	/**
	 * Startet eine AD Konvertierung, wartet auf Abschluss und liefert Ergebnis
	 * \param channel Auswahl des ADC Kanals (0-7), Kanal 6 und 7 sind Poti R36 und R37 
	 */
	uint16_t getValue(uint8_t channel) volatile;
	
private:
	volatile bool active = false;
};

#endif // ADC_H
