#include "selftest.h"

void testAll(void)
{
	testBEBA0();
	testBEBA1();
	testDAC0();
	testDAC1();
	testMirror();
}

void testBEBA0(void)
{
	for(uint8_t i = 0; i < 9; i++)
	{
		dio0.writePortA(_BV(i));

		if(i < 8)
			_delay_ms(200);
	}
}

void testBEBA1(void)
{
	for(uint8_t i = 0; i < 9; i++)
	{
		dio1.writePortA(_BV(i));
		
		if(i < 8)
			_delay_ms(200);
	}
}

void testDAC0(void)
{
	for(uint16_t i = 0; i < 1024; i++)
	{
		dac0.setValue(i);
		_delay_ms(1);
	}
	_delay_ms(100);
	dac0.setValue(0);
}

void testDAC1(void)
{
	for(uint16_t i = 0; i < 1024; i++)
	{
		dac1.setValue(i);
		_delay_ms(1);
	}
	_delay_ms(100);
	dac1.setValue(0);
}

void testMirror()
{
	// deaktiviere WDT
	wdt_disable();

	// Endlosschleife
	while(1)
	{
		dac0.setValue(adu.getValue(0));
		dac1.setValue(adu.getValue(1));
		dio0.writePortA(dio0.readPortB());
		dio1.writePortA(dsw.readPortB());
	}
}
