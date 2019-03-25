#include "selftest.h"

void testAll(void)
{
	testBEBA0();
	testBEBA1();
	testDAC0();
	testDAC1();
}

void testBEBA0(void)
{
	for(uint8_t i = 0; i < 9; i++)
	{
		beba0.writePortA(_BV(i));

		if(i < 8)
			_delay_ms(200);
	}
}

void testBEBA1(void)
{
	for(uint8_t i = 0; i < 9; i++)
	{
		beba1.writePortA(_BV(i));
		
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
}

void testDAC1(void)
{
	for(uint16_t i = 0; i < 1024; i++)
	{
		dac1.setValue(i);
		_delay_ms(1);
	}
}
