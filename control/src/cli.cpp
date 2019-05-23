#define B15F_CLI_DEBUG

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
#include "drv/b15f.h"
#include "ui/ui.h"
#include "ui/view_selection.h"
#include "ui/view_info.h"
#include "ui/view_monitor.h"
#include "ui/view_promt.h"

volatile int win_changed_cooldown = 0;
volatile bool t_refresh_active = false;

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
            t_refresh = std::thread([]()
            {

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
        exit(EXIT_FAILURE);
    }
}

void abort_handler(std::exception& ex)
{
    ViewInfo* view = new ViewInfo();
    view->setTitle("Fehler");
    std::string msg(ex.what());
    msg += "\n\nBeende in 5 Sekunden.";
    view->setText(msg.c_str());
    view->setLabelClose("");
    view->repaint();

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    cleanup();
    std::cerr << std::endl << "*** EXCEPTION ***" << std::endl << ex.what() << std::endl;
    exit(EXIT_FAILURE);
}

void init()
{
    // init b15 driver
    B15F::getInstance();
#ifndef B15F_CLI_DEBUG
    std::cout << std::endl << "Starte in 3s ..." << std::endl;
    sleep(3);
#endif
    B15F::setAbortHandler(&abort_handler);

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


int main()
{
    init();

    int exit_code = EXIT_SUCCESS;

    show_main(0);

    cleanup();

    return exit_code;
}
