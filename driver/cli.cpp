/** TODO
 * 
 * - throw exception -> raise SIGINT
 * - delete view stack
 */


#include <stdio.h>
#include <ncurses.h> // sudo apt-get install libncurses5-dev
#include <vector>
#include <string>
#include <iostream>
#include <signal.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#include "ui/view_selection.h"
#include "ui/view_info.h"
#include "ui/view_monitor.h"
#include "ui/view_promt.h"
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
	//std::cout << std::endl << "Starte in 3s ..." << std::endl;
	//sleep(3);
	
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
	View::setWinContext(newwin(25, 85, 0, 0));
}

void finish(int)
{
	cleanup();
	exit(EXIT_SUCCESS);
}

void view_back(int)
{
	win_stack.pop_back();
	if(win_stack.size())
		win_stack.back()->repaint();
}

void input(int)
{
	std::function<void(int)> nextCall;
	int key;
	do
	{
		key = wgetch(View::getWinContext());
		win_stack.back()->repaint();
		nextCall = win_stack.back()->keypress(key);
		
		if(key == -1)
			view_back(key);
			
		if(nextCall)
			nextCall(key);
	}
	while(win_stack.size());
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

void show_monitor(int)
{
	ViewMonitor* view = new ViewMonitor();
	view->setTitle("Monitor");
	view->setText("\nErfasse Messwerte...");
	view->setLabelClose("[ Zurueck ]");
	view->repaint();
	
	win_stack.push_back(view);
	input(0);
}

void show_invalid_port_input(int)
{
	ViewInfo* view = new ViewInfo();
	view->setTitle("Falsche Eingabe");
	view->setText("Bitte geben Sie einen Wert aus dem Intervall [0, FF] an.");
	view->setLabelClose("[ Schliessen ]");
	view->repaint();
	
	win_stack.push_back(view);
	input(0);
}

void show_invalid_dac_input(int)
{
	ViewInfo* view = new ViewInfo();
	view->setTitle("Falsche Eingabe");
	view->setText("Bitte geben Sie einen Wert aus dem Intervall [0, 1023] an.");
	view->setLabelClose("[ Schliessen ]");
	view->repaint();
	
	win_stack.push_back(view);
	input(0);
}

void write_digital_output0(int)
{
	try
	{
		uint8_t port = std::stoi(static_cast<ViewPromt*>(win_stack.back())->getInput(), 0, 16);
		
		B15F& drv = B15F::getInstance();
		drv.digitalWrite0(port);		
		view_back(0);
	}
	catch(std::invalid_argument& ex)
	{
		show_invalid_port_input(0);
	} 
}

void write_digital_output1(int)
{
	try
	{
		uint8_t port = std::stoi(static_cast<ViewPromt*>(win_stack.back())->getInput(), 0, 16);
		
		B15F& drv = B15F::getInstance();
		drv.digitalWrite1(port);		
		view_back(0);
	}
	catch(std::invalid_argument& ex)
	{
		show_invalid_port_input(0);
	} 
}

void write_analog_output0(int)
{
	try
	{
		uint16_t port = std::stoi(static_cast<ViewPromt*>(win_stack.back())->getInput());
		if(port > 1023)
			throw std::invalid_argument("bad value");
		
		B15F& drv = B15F::getInstance();
		drv.analogWrite0(port);		
		view_back(0);
	}
	catch(std::invalid_argument& ex)
	{
		show_invalid_dac_input(0);
	} 
}

void write_analog_output1(int)
{
	try
	{
		uint16_t port = std::stoi(static_cast<ViewPromt*>(win_stack.back())->getInput());
		if(port > 1023)
			throw std::invalid_argument("bad value");
		
		B15F& drv = B15F::getInstance();
		drv.analogWrite1(port);		
		view_back(0);
	}
	catch(std::invalid_argument& ex)
	{
		show_invalid_dac_input(0);
	} 
}

void show_digital_output0(int)
{
	ViewPromt* view = new ViewPromt();
	view->setTitle("Digitale Ausgabe BE0");
	view->setMessage("\nEingabe Port-Wert (hex): 0x");
	view->setCancel("[ Zurueck ]", true);
	view->setConfirm("[ OK ]", &write_digital_output0);
	view->repaint();
	
	win_stack.push_back(view);
	input(0);
}

void show_digital_output1(int)
{
	ViewPromt* view = new ViewPromt();
	view->setTitle("Digitale Ausgabe BE1");
	view->setMessage("\nEingabe Port-Wert (hex): 0x");
	view->setCancel("[ Zurueck ]", true);
	view->setConfirm("[ OK ]", &write_digital_output1);
	view->repaint();
	
	win_stack.push_back(view);
	input(0);
}

void show_analog_output0(int)
{
	ViewPromt* view = new ViewPromt();
	view->setTitle("Analoge Ausgabe AA0");
	view->setMessage("\nEingabe 10-Bit-Wert (0...1023): ");
	view->setCancel("[ Zurueck ]", true);
	view->setConfirm("[ OK ]", &write_analog_output0);
	view->repaint();
	
	win_stack.push_back(view);
	input(0);
}

void show_analog_output1(int)
{
	ViewPromt* view = new ViewPromt();
	view->setTitle("Analoge Ausgabe AA1");
	view->setMessage("\nEingabe 10-Bit-Wert (0...1023): ");
	view->setCancel("[ Zurueck ]", true);
	view->setConfirm("[ OK ]", &write_analog_output1);
	view->repaint();
	
	win_stack.push_back(view);
	input(0);
}

void show_main(int)
{
	ViewSelection* view = new ViewSelection();	
	view->setTitle("B15F - Command Line Interface");
	view->addChoice("[ Monitor - Eingaben beobachten ]", &show_monitor);
	view->addChoice("[ Digitale Ausgabe BE0 ]", &show_digital_output0);
	view->addChoice("[ Digitale Ausgabe BE1 ]", &show_digital_output1);
	view->addChoice("[ Analoge  Ausgabe AA0 ]", &show_analog_output0);
	view->addChoice("[ Analoge  Ausgabe AA1 ]", &show_analog_output1);
	view->addChoice("[ Informationen ]", &show_info);
	view->addChoice("", nullptr);
	view->addChoice("[ Beenden ]", &finish);
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
