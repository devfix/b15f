#include "view.h"

WINDOW* View::win = nullptr;

View::View()
{
	if(!win)
	{
		ERR_MSG = "View::win not initialized, missing context!";
		raise(SIGINT);
	}
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

// from: https://stackoverflow.com/a/37454181
std::vector<std::string> View::str_split(const std::string& str, const std::string delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
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
	clear();
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
