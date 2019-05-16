#include <iostream>
#include <cmath>
#include <b15f/b15f.h>
#include <b15f/plottyfile.h>


int main()
{
	
	B15F& drv = B15F::getInstance();
	PlottyFile pf;
	
	uint16_t ba[1024];
	uint16_t bb[1024];
	
	const uint16_t sample_count = 1024;
	const uint16_t delta = 1;
	
	pf.setUnitX("V");
	pf.setUnitY("V");
	pf.setUnitPara("V");
	pf.setDescX("U_{OUT}");
	pf.setDescY("U_{IN}");
	pf.setDescPara("");
	pf.setRefX(5);
	pf.setRefY(5);
	pf.setParaFirstCurve(0);
	pf.setParaStepWidth(0);
	
	uint8_t curve = 0;
		
	
    drv.analogSequence(0, &ba[0], 0, 1, &bb[0], 0, 0, delta, sample_count);
    
    for(uint16_t x = 0; x < sample_count * delta; x += delta)
    {
		drv.analogWrite0(x);
		uint16_t y = drv.analogRead(0);
		std::cout << x << " - " << y << std::endl;
        pf.addDot(Dot(x, y, curve));
    }
    
	// speichern und plotty starten
	pf.writeToFile("test_plot");	
	pf.startPlotty("test_plot");
}
