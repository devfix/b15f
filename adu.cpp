#include "adu.h"

void ADU::init()
{
	// externe Referenz an AREF
	ADMUX = 0;

	// ADC aktiviert, prescaler = 128
	ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0);
}

uint16_t ADU::getValue(uint8_t channel)
{
	// lege Kanal fest
	ADMUX = (ADMUX & 0xE0) | channel;

	// starte Konvertierung
	ADCSRA |= _BV(ADSC);
	
	// warte Konvertierungszeit ab
	_delay_us(13 * 1000000 * 128 / F_CPU + 1);

	// warte auf Ende
	while(ADCSRA & _BV(ADSC));

	// liefere Ergebnis
	return ADCW;
}
