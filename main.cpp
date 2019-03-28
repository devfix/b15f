#include <iostream>
#include "drv/b15f.h"
#include "drv/plottyfile.h"

PlottyFile pf;

void kennlinieErsterQuadrant()
{
	B15F& drv = B15F::getInstance();
	
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
		drv.analogeAusgabe1(u_gs);
		
		drv.analogEingabeSequenz(0, &ba[0], 0, 1, &bb[0], 0, 0, delta, sample_count);
		drv.delay(10);
		drv.discard();
		drv.delay(10);
		
		for(uint16_t k = 0; k < sample_count+1; k++)
		{
			uint16_t i_d = ba[k] - bb[k];
			uint16_t u_ds = bb[k];
			pf.addDot(Dot(u_ds, i_d, curve));
		}
		
		curve++;
	}
}

void kennlinieZweiterQuadrant()
{
	B15F& drv = B15F::getInstance();
	
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
		drv.analogeAusgabe1(u_gs);
		
		drv.analogEingabeSequenz(0, &ba[0], 0, 1, &bb[0], 0, 0, delta, sample_count);
		drv.delay(10);
		drv.discard();
		drv.delay(10);
		
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
}

int main()
{
	B15F& drv = B15F::getInstance();
	drv.init();
	
	kennlinieZweiterQuadrant();
	
	// speichern und plotty starten
	pf.writeToFile("test_plot");	
	int code = system("./plotty --in test_plot");
	if(code)
		std::cout << "Fehler beim  plotty Aufruf" << std::endl;
	
	std::cout << "Schluss." << std::endl;
}
