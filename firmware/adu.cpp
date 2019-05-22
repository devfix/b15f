#include "adu.h"

void ADU::init() volatile
{
	// externe Referenz an AREF
	ADMUX = _BV(REFS0);

	// ADC aktiviert, Interruptbetrieb, prescaler = 128
	ADCSRA = _BV(ADEN) | _BV(ADIE) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
}

void ADU::handleConversionComplete() volatile
{
	active = false;
}

uint16_t ADU::getValue(uint8_t channel) volatile
{
	while(active);
	active = true;
	
	// lege Kanal fest
	ADMUX = (ADMUX & 0xE0) | channel;

	// starte Konvertierung
	ADCSRA |= _BV(ADSC);
	
	// warte auf Ende der Konvertierung
	while(active);
	
	return ADCW;
}
