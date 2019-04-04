#include "view.h"

WINDOW* View::win = nullptr;

View::View()
{
	if(!win)
		throw std::runtime_error("View::win not initialized, missing context!");
	getmaxyx(win, height, width); // init width and height	
	keypad(win, TRUE);
}

void View::setWinContext(WINDOW* win)
{
	View::win = win;
}

WINDOW* View::getWinContext()
{
	return win;
}

void View::addCall(std::function<void(int)> call)
{
	calls.push_back(call);
}

void View::setTitle(std::string title)
{
	this->title = title;
}

void View::repaint()
{
	// get screen size
	struct winsize size;	
	if (ioctl(0, TIOCGWINSZ, (char *) &size) < 0)
		throw std::runtime_error("TIOCGWINSZ error");
	
	
	start_x = floor((size.ws_col - width) / 2.);
	start_y = floor((size.ws_row - height) / 2.);
	
	mvwin(win, start_y, start_x);

	wclear(win);
	
	// generic draw
	box(win, 0, 0);
	int offset_x = (width - title.length()) / 2;
	mvwprintw(win, 1, offset_x, "%s", title.c_str());
	
	// specific draw
	draw();

	refresh();
	wrefresh(win);
}
