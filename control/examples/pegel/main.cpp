#include <iostream>
#include <cmath>
#include <b15f/b15f.h>
#include <b15f/plottyfile.h>

const char PLOT_FILE[] = "plot.bin";

int main()
{
	
	B15F& drv = B15F::getInstance();
	PlottyFile pf;
	
	uint16_t buf[1024];
	
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
		
	
    drv.analogSequence(0, &buf[0], 0, 1, nullptr, 0, 0, delta, sample_count);
    
    for(uint16_t x = 0; x < sample_count * delta; x += delta)
    {
		std::cout << x << " - " << buf[x] << std::endl;
        pf.addDot(Dot(x, buf[x], curve));
    }
    
	// speichern und plotty starten
	pf.writeToFile(PLOT_FILE);	
	pf.startPlotty(PLOT_FILE);
}
