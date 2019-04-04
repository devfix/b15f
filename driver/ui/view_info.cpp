#include "view_info.h"

ViewInfo::ViewInfo()
{
}

void ViewInfo::draw()
{
	mvwprintw(win, text_offset_y, text_offset_x, "%s", "hello");
}

std::function<void(int)> ViewInfo::keypress(int& key)
{
	std::function<void(int)> ret = nullptr;
	switch(key)
	{
		
		case KEY_MOUSE:
		{
			// http://pronix.linuxdelta.de/C/Linuxprogrammierung/Linuxsystemprogrammieren_C_Kurs_Kapitel10b.shtml
			MEVENT event;
			if(getmouse(&event) == OK && event.bstate & BUTTON1_CLICKED)
				key = -1; // do return from view
			break;
		}
		case KEY_ENT:
			key = -1; // do return from view
			break;
		default:
			break;
	}
	return ret;
}
