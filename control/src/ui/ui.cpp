#include "ui.h"
#include "../drv/b15f.h"

std::vector<View*> win_stack;
std::thread t_refresh;

void show_main(int)
{
    ViewSelection* view = new ViewSelection();
    view->setTitle("B15F - Command Line Interface");
    view->addChoice("[ Monitor - Eingaben beobachten ]", &show_monitor);
    view->addChoice("[ Digitale Ausgabe BA0 ]", &show_digital_output0);
    view->addChoice("[ Digitale Ausgabe BA1 ]", &show_digital_output1);
    view->addChoice("[ Analoge  Ausgabe AA0 ]", &show_analog_output0);
    view->addChoice("[ Analoge  Ausgabe AA1 ]", &show_analog_output1);
    view->addChoice("[ Selbsttest des B15 ]", &show_selftest_info);
    view->addChoice("[ Informationen ]", &show_info);
    view->addChoice("", nullptr);
    view->addChoice("[ Beenden ]", &finish);
    view->repaint();

    win_stack.push_back(view);
    input(0);
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

void finish(int)
{
    cleanup();
    exit(EXIT_SUCCESS);
}

void cleanup()
{
    if(t_refresh.joinable())
        t_refresh.join();
    clrtoeol();
    refresh();
    endwin();
}

void show_info(int)
{
    ViewInfo* view = new ViewInfo();
    view->setTitle("Info");
    view->setText("Informationen zu Board 15 Famulus Edition\n \nProjektseite: https://github.com/devfix/b15f/\nDokumentation: https://devfix.github.io/b15f/\n \nB15F Software entwickelt von Tristan Krause für das Hardware-Labor.\nKontakt: tristan.krause@stud.htwk-leipzig.de");
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
    view->setMessage("\nAusgabe Port-Wert (hex): 0x");
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
    view->setMessage("\nAusgabe Port-Wert (hex): 0x");
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
    view->setMessage("\nAusgabe 10-Bit-Wert (0...1023): ");
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
    view->setMessage("\nAusgabe 10-Bit-Wert (0...1023): ");
    view->setCancel("[ Zurueck ]", true);
    view->setConfirm("[ OK ]", &write_analog_output1);
    view->repaint();

    win_stack.push_back(view);
    input(0);
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

void stop_selftest(int)
{
    B15F& drv = B15F::getInstance();
    drv.discard();
    drv.delay_ms(B15F::WDT_TIMEOUT);
    drv.reconnect();
    drv.digitalWrite0(0);
    drv.digitalWrite1(0);
}

void show_selftest_info(int)
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
