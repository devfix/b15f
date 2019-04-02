#include <iostream>
#include <cmath>
#include "drv/usart.h"
#include "drv/b15f.h"
#include "drv/plottyfile.h"


void kennlinieErsterQuadrant()
{
	B15F& drv = B15F::getInstance();
	PlottyFile pf;
	
	uint16_t ba[1024];
	uint16_t bb[1024];
	
	const uint16_t sample_count = 100;
	const uint16_t delta = 10;
	
	const uint16_t u_gs_start = 440;
	const uint16_t u_gs_delta = 20;
	const uint16_t u_gs_end = 600;
	
	pf.setUnitX("V");
	pf.setUnitY("mA");
	pf.setUnitPara("V");
	pf.setDescX("U_{DS}");
	pf.setDescY("I_D");
	pf.setDescPara("U_{GS}");
	pf.setRefX(5);
	pf.setRefY(50);
	pf.setParaFirstCurve(u_gs_start);
	pf.setParaStepWidth(u_gs_delta);
	
	uint8_t curve = 0;
	for(uint16_t u_gs = u_gs_start; u_gs <= u_gs_end; u_gs += u_gs_delta)
	{
		drv.analogWrite1(u_gs);
		
		drv.analogSequence(0, &ba[0], 0, 1, &bb[0], 0, 0, delta, sample_count);
		drv.delay_ms(10);
		drv.discard();
		drv.delay_ms(10);
		
		for(uint16_t k = 0; k < sample_count+1; k++)
		{
			uint16_t i_d = ba[k] - bb[k];
			uint16_t u_ds = bb[k];
			pf.addDot(Dot(u_ds, i_d, curve));
		}
		
		curve++;
	}
	
	// speichern und plotty starten
	pf.writeToFile("test_plot");	
	pf.startPlotty("test_plot");
}

void kennlinieZweiterQuadrant()
{
	B15F& drv = B15F::getInstance();
	PlottyFile pf;
	
	uint16_t ba[1024];
	uint16_t bb[1024];
	
	const uint16_t sample_count = 1000;
	const uint16_t delta = 1;
	
	const uint16_t u_gs_start = 300;
	const uint16_t u_gs_delta = 25;
	const uint16_t u_gs_end = 700;
	
	pf.setQuadrant(2);
	pf.setUnitX("V");
	pf.setUnitY("mA");
	pf.setUnitPara("V");
	pf.setDescX("U_{GS}");
	pf.setDescY("I_D");
	pf.setDescPara("U_{DS}");
	pf.setRefX(5);
	pf.setRefY(50);
	pf.setParaFirstCurve(u_gs_start);
	pf.setParaStepWidth(u_gs_delta);
	
	uint8_t curve = 0;
	for(uint16_t u_gs = u_gs_start; u_gs <= u_gs_end; u_gs += u_gs_delta)
	{
		drv.analogWrite1(u_gs);
		
		drv.analogSequence(0, &ba[0], 0, 1, &bb[0], 0, 0, delta, sample_count);
		
		curve = 0;
		for(uint16_t k = 0; k < sample_count + 1; k++)
		{
			if(ba[k] > bb[k] && bb[k] % 50 == 0 && bb[k] > 0)
			{
				uint16_t i_d = ba[k] - bb[k];
				pf.addDot(Dot(u_gs, i_d, bb[k] / 50));
			}
			curve++;
		}
		std::cout << "u_gs: " << u_gs << std::endl;
	}
	
	// speichern und plotty starten
	pf.writeToFile("test_plot");	
	pf.startPlotty("test_plot");
}

void testFunktionen()
{
	B15F& drv = B15F::getInstance();
	
	
	drv.digitalWrite0(0xFF);
	drv.analogWrite0(128);
	std::cout << (int) drv.digitalRead0() << std::endl;;
	std::cout << "adc: " << (int) drv.analogRead(4) << std::endl;
	
	drv.digitalWrite0(0x00);
	drv.analogWrite0(0);
	std::cout << (int) drv.digitalRead0() << std::endl;;
	std::cout << "adc: " << (int) drv.analogRead(4) << std::endl;
	
	drv.digitalWrite0(0xFF);
	drv.analogWrite0(255);
	std::cout << (int) drv.digitalRead0() << std::endl;
	std::cout << "adc: " << (int) drv.analogRead(4) << std::endl;
	
	
	std::cout << "Kennlinie..." << std::endl;
	uint16_t a[1024];
	uint16_t b[1024];	
	drv.analogSequence(0, &a[0], 0, 1, &b[0], 0, 0, 1, 1024);
	for(uint16_t i= 0; i < sizeof(a) / sizeof(uint16_t); i++)
	{
		std::cout << (int) i << " : " << a[i] << "   " << b[i] << std::endl;
	}
	
}

int main()
{
	
	testFunktionen();
	
	std::cout << "Schluss." << std::endl;
}
