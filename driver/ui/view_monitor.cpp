#include "view_monitor.h"

ViewMonitor::ViewMonitor() : t_worker(&ViewMonitor::worker, this)
{	
}

std::function<void(int)> ViewMonitor::keypress(int& key)
{
	switch(key)
	{
		
		case KEY_MOUSE:
		{
			// http://pronix.linuxdelta.de/C/Linuxprogrammierung/Linuxsystemprogrammieren_C_Kurs_Kapitel10b.shtml
			MEVENT event;
			if(getmouse(&event) == OK && event.bstate & (BUTTON1_CLICKED | BUTTON1_DOUBLE_CLICKED))
			{
				size_t column = start_x + close_offset_x;
				size_t row = start_y + close_offset_y;
				if(event.y == row && event.x >= column && event.x < column + label_close.length())
					key = -1; // do return from view
			}
			break;
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

void ViewMonitor::worker()
{
	while(run_worker)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
