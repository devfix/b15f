#include "view_info.h"

ViewInfo::ViewInfo()
{
}

void ViewInfo::setText(std::string text)
{
	this->text = text;
}

void ViewInfo::setLabelClose(std::string label)
{
	this->label_close = label;
}

void ViewInfo::draw()
{
	int li = 0;
	for(std::string line : str_split(text, "\n"))
		mvwprintw(win, text_offset_y + li++, text_offset_x, "%s", line.c_str());
	
	close_offset_x = (width - label_close.length()) / 2;
	close_offset_y = height - 2;
	
	wattron(win, A_REVERSE);
	mvwprintw(win, close_offset_y, close_offset_x, "%s", label_close.c_str());
	wattroff(win, A_REVERSE);
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
			key = -1; // do return from view
			break;
		default:
			break;
	}
	return ret;
}
