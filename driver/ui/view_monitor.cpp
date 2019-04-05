#include "view_monitor.h"

ViewMonitor::ViewMonitor() : t_worker(&ViewMonitor::worker, this)
{	
}

call_t ViewMonitor::keypress(int& key)
{
	switch(key)
	{
		
		case KEY_MOUSE:
		{
			// http://pronix.linuxdelta.de/C/Linuxprogrammierung/Linuxsystemprogrammieren_C_Kurs_Kapitel10b.shtml
			MEVENT event;
			bool hit = false;
			if(getmouse(&event) == OK && event.bstate & (BUTTON1_CLICKED | BUTTON1_DOUBLE_CLICKED))
			{
				size_t column = start_x + close_offset_x;
				size_t row = start_y + close_offset_y;
				size_t mouse_x = event.x, mouse_y = event.y;
				if(mouse_y == row && mouse_x >= column && mouse_x < column + label_close.length())
					hit = true;
			}
			if(!hit)
				break;
				
			// fall through to next case
			__attribute__ ((fallthrough));
		}
		case KEY_ENT:
			run_worker = false;
			key = -1; // do return from view
			wclear(win);
			wrefresh(win);
			t_worker.join();
			break;
		default:
			break;
	}
	return calls[0];
}

std::string ViewMonitor::fancyDigitalString(uint8_t& b)
{
	std::stringstream str;
	str << std::bitset<8>(b).to_string();
	str << " ";
	str << "0x" << std::setfill ('0') << std::setw(2) << std::hex << (int) b << std::dec;
	return str.str();
}

std::string ViewMonitor::fancyAnalogString(uint16_t& v)
{
	std::stringstream str;
	double volt = round(v * 100.0 * 5.0 / 1023.0) / 100.0;
	
	str << std::setfill ('0') << std::setw(4) << (int) v << "   " << std::fixed << std::setprecision(2) << volt << " V   ";
	
	str << "[";
	uint8_t p = round(v * 40.0 / 1023.0);
	for(uint8_t i = 0; i < p; i++)
		str << "X";
	for(uint8_t i = 0; i < 40 - p; i++)
		str << " ";
	str << "]" << std::endl;
		
	return str.str();
}

void ViewMonitor::worker()
{
	B15F& drv =	B15F::getInstance();
	while(run_worker)
	{
		try
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			
			uint8_t be0 = drv.digitalRead0();
			uint8_t be1 = drv.digitalRead1();
			uint8_t dsw = drv.readDipSwitch();
			uint16_t adc[8];
			for(uint8_t i = 0; i < sizeof(adc) / sizeof(adc[0]); i++)
				adc[i] = drv.analogRead(i);
			
			
			std::stringstream str;
			
			// hline
			for(uint8_t i = 0; i < width - 2 * text_offset_x; i++)
				if(i % 2 == 0)
					str << "-";
				else
					str << " ";
			str << std::endl;
					
			str << "Digitale Enigaenge:" << std::endl;
			str << "Binaere Eingabe 0: " << fancyDigitalString(be0) << std::endl;
			str << "Binaere Eingabe 1: " << fancyDigitalString(be1) << std::endl;
			str << "Dip Schalter (S7): " << fancyDigitalString(dsw) << std::endl;
			
			// hline
			for(uint8_t i = 0; i < width - 2 * text_offset_x; i++)
				if(i % 2 == 0)
					str << "-";
				else
					str << " ";
			str << std::endl;
					
			str << "Analoge Eingaenge:" << std::endl;
			for(uint8_t i = 0; i < sizeof(adc) / sizeof(adc[0]); i++)
			{
				str << "Kanal " << std::to_string((int) i) << ": ";
				str << fancyAnalogString(adc[i]) << std::endl;
			}
			
			text = str.str();
			repaint();
		}
		catch(...)
		{
			drv.reconnect();
		}
	}
}
