#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <ncurses.h> // sudo apt-get install libncurses5-dev
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#include "../drv/b15f.h"

extern std::string ERR_MSG;
typedef std::function<void(int)> call_t;

class View
{
public:
	View(void);
	virtual ~View(void);
	
	static void setWinContext(WINDOW* win);
	static WINDOW* getWinContext(void);
	static std::vector<std::string> str_split(const std::string& str, const std::string delim);
	
	virtual void setTitle(std::string title);
	
	virtual void repaint(void);
	
	virtual void draw(void) = 0;
	virtual call_t keypress(int& key) = 0;
	
	
protected:
	int width, height;
	int start_x = 0, start_y = 0;
	std::string title;
	std::vector<call_t> calls;
	
	static WINDOW* win;
	constexpr static int KEY_ENT = 10;
};

#endif // VIEW_H
