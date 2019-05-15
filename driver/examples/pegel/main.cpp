#include <iostream>
#include <cmath>
#include <b15f/b15f.h>
#include <b15f/plottyfile.h>


void kennlinieErsterQuadrant()
{
	
	B15F& drv = B15F::getInstance();
	PlottyFile pf;
	
	uint16_t ba[1024];
	uint16_t bb[1024];
	
	const uint16_t sample_count = 1024;
	const uint16_t delta = 1;
	
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
		
	std::cout << "Erfasse Kennlinie erster Quadrant..." << std::endl << std::flush;
	
	for(uint16_t u_gs = u_gs_start; u_gs <= u_gs_end; u_gs += u_gs_delta)
	{
		drv.analogWrite1(u_gs);
		
		drv.analogSequence(0, &ba[0], 0, 1, &bb[0], 0, 0, delta, sample_count);
		
		for(uint16_t k = 0; k < sample_count; k++)
		{
			uint16_t i_d = ba[k] - bb[k];
			uint16_t u_ds = bb[k];
			pf.addDot(Dot(u_ds, i_d, curve));
		}
		
		std::cout << "\033[1K\r" << 1e2 * (u_gs - u_gs_start) / (u_gs_end - u_gs_start) << "%" << std::flush;
		
		curve++;
	}
	
	std::cout << "\033[1K\r" << std::flush;
	
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
	
	const uint16_t sample_count = 1024;
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
	
	std::cout << "Erfasse Kennlinie zweiter Quadrant..." << std::endl << std::flush;
	
	for(uint16_t u_gs = u_gs_start; u_gs <= u_gs_end; u_gs += u_gs_delta)
	{
		drv.analogWrite1(u_gs);
		
		drv.analogSequence(0, &ba[0], 0, 1, &bb[0], 0, 0, delta, sample_count);
		
		curve = 0;
		for(uint16_t k = 0; k < sample_count; k++)
		{
			if(ba[k] > bb[k] && bb[k] % 50 == 0 && bb[k] != 0)
			{
				uint16_t i_d = ba[k] - bb[k];
				pf.addDot(Dot(u_gs, i_d, bb[k] / 50));
			}
			curve++;
		}
		
		std::cout << "\033[1K\r" << 1e2 * (u_gs - u_gs_start) / (u_gs_end - u_gs_start) << "%" << std::flush;
	}
	
	std::cout << "\033[1K\r" << std::flush;
	
	// speichern und plotty starten
	pf.writeToFile("test_plot");	
	pf.startPlotty("test_plot");
}

void testFunktionen()
{
	B15F& drv = B15F::getInstance();
	
	std::cout << "DIP-Switch: " << (int) drv.readDipSwitch() << std::endl;
	
	
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
	
	/*for(uint16_t i= 0; i < sizeof(a) / sizeof(uint16_t); i++)
	{
		std::cout << (int) i << " : " << a[i] << "   " << b[i] << std::endl;
	}*/
	
}

int main()
{
	//testFunktionen();
	//kennlinieZweiterQuadrant();

	B15F& drv = B15F::getInstance();
	while(1)
	{
			//uint8_t be0 = drv.digitalRead0();
			//uint8_t be1 = drv.digitalRead1();
			//uint8_t dsw = drv.readDipSwitch();
			drv.analogRead(0);
			drv.analogRead(1);
			drv.analogRead(2);
			drv.analogRead(3);
			drv.analogRead(4);
			drv.analogRead(5);
			drv.analogRead(6);
			drv.analogRead(7);
	}
	
	std::cout << "Schluss." << std::endl;
}
