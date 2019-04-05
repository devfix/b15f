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
#include <future>
#include <thread>
#include <chrono>
#include "ui/view_selection.h"
#include "ui/view_info.h"
#include "ui/view_monitor.h"
#include "ui/view_promt.h"
#include "drv/b15f.h"

// global error message
std::string ERR_MSG;

std::vector<View*> win_stack;

volatile int win_changed_cooldown = 0;
volatile bool t_refresh_active = false;
std::thread t_refresh;

void cleanup()
{
	if(t_refresh.joinable())
		t_refresh.join();
	clrtoeol();
	refresh();
	endwin();
}

void signal_handler(int signal)
{
	if(signal == SIGWINCH)
	{
		win_changed_cooldown = 10; // 100ms
		
		if (!t_refresh_active)
		{
			if(t_refresh.joinable())
				t_refresh.join();
			t_refresh_active = true;
			t_refresh = std::thread([](){
				
				while(win_changed_cooldown--)
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
					
				t_refresh_active = false;
				
				if(win_stack.size())
					win_stack.back()->repaint();
					
			});
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
	std::cout << std::endl << "Starte in 3s ..." << std::endl;
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
	if(win_stack.size())
	{
		delete win_stack.back();
		win_stack.pop_back();
	}
	if(win_stack.size())
		win_stack.back()->repaint();
}

void input(int)
{
	call_t nextCall;
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
	view->setText("Informationen zu Board 15 Famulus Edition\nEs war einmal...");
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
		int d = std::stoi(static_cast<ViewPromt*>(win_stack.back())->getInput(), 0, 16);
		if(d > 255 || 0 > d)
			throw std::invalid_argument("bad value");
		uint8_t port = static_cast<uint8_t>(d);
		
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
		int d = std::stoi(static_cast<ViewPromt*>(win_stack.back())->getInput(), 0, 16);
		if(d > 255 || 0 > d)
			throw std::invalid_argument("bad value");
		uint8_t port = static_cast<uint8_t>(d);
		
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


void stop_selftest(int)
{
	B15F& drv = B15F::getInstance();
	drv.discard();
}

void start_selftest(int)
{
	B15F& drv = B15F::getInstance();
	drv.activateSelfTestMode();
	
	ViewInfo* view = new ViewInfo();
	view->setTitle("Selbsttest aktiv");
	view->setText("Das B15 befindet sich jetzt im Selbsttestmodus.\n \nSelbsttest:\nZu Beginn geht der Reihe nach jede LED von BA0 bis BA1 an.\nDanach leuchten die LEDs an AA0 und AA1 kurz auf.\nZum Schluss spiegelt in einer Endlosschleife:\n* BA0 Port BE0\n* BA1 die DIP-Schalter S7\n* AA0 ADC0\n* AA1 ADC1");
	view->setLabelClose("[ Selbsttest Beenden ]");
	view->setCall(&stop_selftest);
	view->repaint();
	
	win_stack.push_back(view);
	input(0);
}

void show_selftest(int)
{
	ViewInfo* view = new ViewInfo();
	view->setTitle("Selbsttest");
	view->setText("Bitte entfernen Sie jetzt alle Draehte von den Anschlussklemmen und bestaetigen\nmit Enter.");
	view->setLabelClose("[ Weiter ]");
	view->setCall(&start_selftest);
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
	view->addChoice("[ Selbsttest des B15 ]", &show_selftest);
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
