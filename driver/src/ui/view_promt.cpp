#include "view_promt.h"

void ViewPromt::draw()
{
	curs_set(2); // show cursor
	
	int li = text_offset_y;
	int ci = 0;
	for(std::string line : str_split(message + input, "\n"))
	{
		mvwprintw(win, ++li, text_offset_x, "%s", line.c_str());
		ci = line.length() + text_offset_x;
	}
	
	button_offset_x = (width - label_cancel.length() - sep.length() - label_confirm.length()) / 2;
	button_offset_y = height - text_offset_y;
	
	if(selection == 0)
	{
		wattron(win, A_REVERSE);
		mvwprintw(win, button_offset_y, button_offset_x, "%s", label_cancel.c_str());
		wattroff(win, A_REVERSE);
		mvwprintw(win, button_offset_y, button_offset_x + label_cancel.length(), "%s", sep.c_str());
		mvwprintw(win, button_offset_y, button_offset_x + label_cancel.length() + sep.length(), "%s", label_confirm.c_str());
	}
	else
	{
		mvwprintw(win, button_offset_y, button_offset_x, "%s", label_cancel.c_str());
		mvwprintw(win, button_offset_y, button_offset_x + label_cancel.length(), "%s", sep.c_str());
		wattron(win, A_REVERSE);
		mvwprintw(win, button_offset_y, button_offset_x + label_cancel.length() + sep.length(), "%s", label_confirm.c_str());
		wattroff(win, A_REVERSE);
	}
	wmove(win, li, ci);
}

void ViewPromt::setMessage(std::string message)
{
	this->message = message;
}

void ViewPromt::setConfirm(std::string name, std::function<void(int)> call)
{
	label_confirm = name;
	call_confirm = call;
}

void ViewPromt::setCancel(std::string name, bool cancelable)
{
	label_cancel = name;
	this->cancelable = cancelable;
}

std::string ViewPromt::getInput()
{
	return input;
}

std::function<void(int)> ViewPromt::keypress(int& key)
{	
	std::function<void(int)> ret = nullptr;
	switch(key)
	{
		case KEY_BACKSPACE:
			if(input.length())
				input.pop_back();
			break;
		case '\t':
		case KEY_LEFT:
		case KEY_RIGHT:
			selection = (selection + 1 ) % 2;
			break;
		case KEY_MOUSE:
		{
			// http://pronix.linuxdelta.de/C/Linuxprogrammierung/Linuxsystemprogrammieren_C_Kurs_Kapitel10b.shtml
			MEVENT event;
			bool hit = false;
			if(getmouse(&event) == OK && event.bstate & (BUTTON1_CLICKED | BUTTON1_DOUBLE_CLICKED))
			{
				size_t column_start = start_x + button_offset_x;
				size_t row_start = start_y + button_offset_y;
				size_t mouse_x = event.x, mouse_y = event.y;
				if(mouse_y == row_start)
				{
					if(cancelable && mouse_x >= column_start && mouse_x < column_start + label_cancel.length())
					{
						if(selection == 0 || event.bstate & BUTTON1_DOUBLE_CLICKED)
							hit = true;
						selection = 0;
					}
					if(mouse_x >= column_start + label_cancel.length() + sep.length() && mouse_x < column_start + label_cancel.length() + sep.length()  + label_confirm.length())
					{
						if(selection == 1 || event.bstate & BUTTON1_DOUBLE_CLICKED)
							hit = true;
						selection = 1;
					}
				}
			}
			if(!hit)
				break;
			
			// fall through to next case
			[[fallthrough]];
		}
		case KEY_ENT:
			if(selection == 0) // exit
				key = -1; // do return from view
			else
				ret = call_confirm;
			curs_set(0); // hide cursor again
			break;
		default:
			break;
	}
	
	if(key >= ' ' && key <= '~')
		input += (char) key;
	
	if(key != KEY_ENT)
		repaint();
	return ret;
}
