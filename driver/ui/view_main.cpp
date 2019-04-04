#include "view_main.h"

void ViewMain::draw()
{
	
	for(size_t i = 0; i < choices.size(); i++)
	{
		if(selection == i)
			wattron(win, A_REVERSE);
		mvwprintw(win, i + choice_offset_y, choice_offset_x, "%s", choices[i].c_str());
		if(selection == i)
			wattroff(win, A_REVERSE);		
	}
}

std::function<void(int)> ViewMain::keypress(int& key)
{
	std::function<void(int)> ret = nullptr;
	switch(key)
	{
		case KEY_UP:
			selection = (selection - 1) % choices.size();
			break;
		case KEY_DOWN:
			selection = (selection + 1) % choices.size();
			break;
		case KEY_MOUSE:
		{
			// http://pronix.linuxdelta.de/C/Linuxprogrammierung/Linuxsystemprogrammieren_C_Kurs_Kapitel10b.shtml
			MEVENT event;
			bool hit = false;
			if(getmouse(&event) == OK && event.bstate & (BUTTON1_CLICKED | BUTTON1_DOUBLE_CLICKED))
			{
				size_t column_start = start_x + choice_offset_x;
				size_t row_start = start_y + choice_offset_y;
				size_t mouse_x = event.x, mouse_y = event.y;
				for(size_t i = 0; i < choices.size(); i++)
					if(mouse_y == row_start + i && mouse_x >= column_start && mouse_x < column_start + choices[i].length())
					{
						if(selection == i || event.bstate & BUTTON1_DOUBLE_CLICKED)
							hit = true;
						selection = i;
					}
			}
			if(!hit)
				break;
			
			// fall through to next case
			__attribute__ ((fallthrough));
		}
		case KEY_ENT:
			if(selection == choices.size() - 1) // exit
				key = -1; // do return from view
			else
				ret = calls[selection];			
			break;
		default:
			break;
	}
	repaint();
	return ret;
}
