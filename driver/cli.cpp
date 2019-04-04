#include <stdio.h>
#include <ncurses.h> // sudo apt-get install libncurses5-dev
#include <vector>
#include <string>
#include <iostream>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#include "ui/view_main.h"
#include "ui/view_info.h"
#include "drv/b15f.h"

// global error message
std::string ERR_MSG;

std::vector<View*> win_stack;

void cleanup()
{
	clrtoeol();
	refresh();
	endwin();
}

void signal_handler(int signal)
{
	if(signal == SIGWINCH)
	{
		if(win_stack.size())
		{
			usleep(1000);
			win_stack.back()->repaint();
		}
	}
	else if(signal == SIGINT)
	{
		cleanup();
		std::cout << "SIGINT - Abbruch." << std::endl;
		if(ERR_MSG.length())
			std::cout << "ERR_MSG: " << ERR_MSG << std::endl;
		exit(EXIT_FAILURE);
	}
}

void init()
{
	// init b15 driver
	B15F::getInstance();
	
	// init all ncurses stuff
	initscr();
	start_color();
	curs_set(0); // 0: invisible, 1: normal, 2: very visible
	clear();
	noecho();
	cbreak();  // Line buffering disabled. pass on everything
	mousemask(ALL_MOUSE_EVENTS, NULL);
	
	// connect signals to handler
	signal(SIGWINCH, signal_handler);	
	signal(SIGINT, signal_handler);
	
	// set view context
	View::setWinContext(newwin(32, 128, 0, 0));
}

void finish(int)
{
	cleanup();
	exit(EXIT_SUCCESS);
}

void input(int)
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

void show_info(int)
{
	ViewInfo* view = new ViewInfo();
	view->setTitle("Info");
	view->setText("Informationen zu Board 15 Famulus Edition\nEs war einmal");
	view->setLabelClose("[ Zurueck ]");
	view->repaint();
	
	win_stack.push_back(view);
	input(0);
}

void show_main(int)
{
	ViewMain* view = new ViewMain();	
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
