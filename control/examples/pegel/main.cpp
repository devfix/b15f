#include <iostream>
#include <cmath>
#include <b15f/b15f.h>
#include <b15f/plottyfile.h>

/*
 * Inkrementiert DAC 0 von 0 bis 1023 und speichert zu jeder Ausgabe den Wert von ADC 0 in einem Puffer.
 * Die Funktion ADC 0 abhängig von DAC 0 wird als Graph geplottet.
 */

const char PLOT_FILE[] = "plot.bin";

int main()
{
	
	B15F& drv = B15F::getInstance();
	PlottyFile pf;
	
	uint16_t buf[1024];
	
	const uint16_t count = 1024;
	const uint16_t delta = 1;
    const uint16_t start = 0;
	
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
	
	const uint8_t curve = 0;		
	
    drv.analogSequence(0, &buf[0], 0, 1, nullptr, 0, start, delta, count);
    
    for(uint16_t x = 0; x < count; x++)
    {
		std::cout << x << " - " << buf[x] << std::endl;
        pf.addDot(Dot(x, buf[x], curve));
    }
    
	// speichern und plotty starten
	pf.writeToFile(PLOT_FILE);
	pf.startPlotty(PLOT_FILE);
}
