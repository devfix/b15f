#include <iostream>
#include <cmath>
#include <iomanip>
#include <b15f/b15f.h>
#include <b15f/plottyfile.h>

const char PLOT_FILE[] = "plot.bin";

void printProgress(double p)
{
    constexpr double precision = 1e1;
    constexpr int width = 20;
    const int n = round(width * p);
    p = round(1e2 * precision * p) / precision;
    std::cout << "\033[1K\r";
    std::cout << "[" << std::string(n, '#') << std::string(width - n, '-') << "] ";
    std::cout << std::setfill(' ') << std::setw(5) << std::fixed << std::showpoint << std::setprecision(1) << p << "%" << std::flush;
}

void kennlinieErsterQuadrant()
{
    // Puffer für Messwerte
	uint16_t u_out[1024];
	uint16_t u_drain[1024];
	
    // Ansteuerung der U_GS, Anzahl der Werte für U_GS muss kleiner 64 sein,
    // da sonst zu großer Kurvenindex entsteht
	const uint16_t u_gs_start = 200;
	const uint16_t u_gs_delta = 50;
	const uint16_t u_gs_end = 600;
	
    // Ansteuerung durch u_out (ruft Drainstrom i_drain hervor)
	const uint16_t seq_start = 0;
	const uint16_t seq_delta = 1;
	const uint16_t seq_sample_count = 1024;
	
	B15F& drv = B15F::getInstance();
	PlottyFile pf;
	
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
		
	std::cout << "Erfasse Kennlinie erster Quadrant..." << std::endl;
	
	for(uint16_t u_gs = u_gs_start; u_gs <= u_gs_end; u_gs += u_gs_delta)
	{
		drv.analogWrite1(u_gs);
		
        // Erfasse u_out und u_drain und variiere dabei u_out, die aktuelle U_GS bleibt solange konstant
		drv.analogSequence(0, &u_out[0], 0, 1, &u_drain[0], 0, seq_start, seq_delta, seq_sample_count);
		
		for(uint16_t k = 0; k < seq_sample_count; k++)
		{
			uint16_t i_drain = u_out[k] - u_drain[k];
			pf.addDot(Dot(u_drain[k], i_drain, curve));
		}
		
		curve++;
        
        // Fortschrittsanzeige
		printProgress(double(u_gs - u_gs_start) / double(u_gs_end - u_gs_start));
	}
	
	std::cout << std::endl << std::flush;
	
	// speichern und plotty starten
	pf.writeToFile(PLOT_FILE);	
	pf.startPlotty(PLOT_FILE);
}

void kennlinieZweiterQuadrant()
{	
    constexpr uint8_t resolution = 50;
    
    // Puffer für Messwerte
	uint16_t u_out[1024];
    uint16_t u_drain[1024];
	
    // Ansteuerung der U_GS
	const uint16_t u_gs_start = 128;
	const uint16_t u_gs_delta = 32;
	const uint16_t u_gs_end = 512;
	
    // Ansteuerung druch u_out (ruft Drainstrom i_drain hervor)
	const uint16_t seq_start = 0;
	const uint16_t seq_delta = 1;
	const uint16_t seq_sample_count = 1024;
    
	B15F& drv = B15F::getInstance();
	PlottyFile pf;
	
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
	
	uint8_t curve;
	
	std::cout << "Erfasse Kennlinie zweiter Quadrant..." << std::endl;
	
	for(uint16_t u_gs = u_gs_start; u_gs <= u_gs_end; u_gs += u_gs_delta)
	{
		drv.analogWrite1(u_gs);
		
        // Erfasse u_out und u_drain und variiere dabei u_out, die aktuelle U_GS bleibt solange konstant
		drv.analogSequence(0, &u_out[0], 0, 1, &u_drain[0], 0, seq_start, seq_delta, seq_sample_count);
		
		curve = 0;
		for(uint16_t k = 0; k < seq_sample_count; k++)
		{
            // Speichere nur Werte für i_drain, wo u_drain ein Vielfaches der Auflösung ist
			if(u_out[k] > u_drain[k] && u_drain[k] % resolution == 0 && u_drain[k] != 0)
			{
                uint16_t i_drain = u_out[k] - u_drain[k];
				pf.addDot(Dot(u_gs, i_drain, u_drain[k] / resolution));
			}
			curve++;
		}
		
		// Fortschrittsanzeige
		printProgress(double(u_gs - u_gs_start) / double(u_gs_end - u_gs_start));
	}
	
	std::cout << std::endl << std::flush;
	
	// speichern und plotty starten
	pf.writeToFile(PLOT_FILE);	
	pf.startPlotty(PLOT_FILE);
}

int main()
{
    kennlinieErsterQuadrant();
	kennlinieZweiterQuadrant();
}
