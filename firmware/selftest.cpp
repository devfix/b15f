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
		((MCP23S17*) &beba0)->writePortA(_BV(i));

		if(i < 8)
			_delay_ms(200);
	}
}

void testBEBA1(void)
{
	for(uint8_t i = 0; i < 9; i++)
	{
		((MCP23S17*) &beba1)->writePortA(_BV(i));
		
		if(i < 8)
			_delay_ms(200);
	}
}

void testDAC0(void)
{
	for(uint16_t i = 0; i < 1024; i++)
	{
		((TLC5615*) &dac0)->setValue(i);
		_delay_ms(1);
	}
	_delay_ms(100);
	((TLC5615*) &dac0)->setValue(0);
}

void testDAC1(void)
{
	for(uint16_t i = 0; i < 1024; i++)
	{
		((TLC5615*) &dac1)->setValue(i);
		_delay_ms(1);
	}
	_delay_ms(100);
	((TLC5615*) &dac1)->setValue(0);
}

void testMirror()
{
	// deaktiviere WDT
	wdt_disable();

	// Endlosschleife
	while(1)
	{
		((TLC5615*) &dac0)->setValue(((ADU*) &adu)->getValue(0));
		((TLC5615*) &dac1)->setValue(((ADU*) &adu)->getValue(1));
		((MCP23S17*) &beba0)->writePortA(((MCP23S17*) &beba0)->readPortB());
		((MCP23S17*) &beba1)->writePortA(((MCP23S17*) &sw)->readPortB());
	}
}
