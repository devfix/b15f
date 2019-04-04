#include <stdio.h>
#include <ncurses.h> // sudo apt-get install libncurses5-dev
#include <vector>
#include <string>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include "ui/view_main.h"
#include "ui/view_info.h"


std::vector<View*> win_stack;
ViewMain* view_main = nullptr;
ViewInfo* view_info = nullptr;

void init()
{
	initscr();
	start_color();
	curs_set(0); // 0: invisible, 1: normal, 2: very visible
	clear();
	noecho();
	cbreak();  // Line buffering disabled. pass on everything
	mousemask(ALL_MOUSE_EVENTS, NULL);
	
	View::setWinContext(newwin(32, 128, 0, 0));
}

void cleanup()
{
	clrtoeol();
	refresh();
	endwin();
}

void finish(int key)
{
	cleanup();
	exit(EXIT_SUCCESS);
}

void input(int prev_key)
{
	std::function<void(int)> nextCall;
	int key;
	do
	{
		key = wgetch(View::getWinContext());
		nextCall = win_stack.back()->keypress(key);
		
		if(key == -1)
		{
			win_stack.pop_back();
			if(win_stack.size())
				win_stack.back()->repaint();
			return;
		}
			
		if(nextCall)
			nextCall(key);
	}
	while(!false);
}

void show_info(int key)
{
	View* view = new ViewInfo();
	view->setTitle("Info");
	view->repaint();
	
	win_stack.push_back(view);
	input(0);
}

void show_main(int key)
{
	View* view = new ViewMain();	
	view->setTitle("B15F - Command Line Interface");
	view->addCall(&show_info);
	view->addCall(&finish);
	view->repaint();
	
	win_stack.push_back(view);
	input(0);
}

int main()
{

	init();
	
	show_main(0);	
	
	cleanup();
	return EXIT_SUCCESS;
}
