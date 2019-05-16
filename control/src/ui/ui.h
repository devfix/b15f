#ifndef UI_H
#define UI_H

#include <vector>
#include "view_selection.h"
#include "view_info.h"
#include "view_monitor.h"
#include "view_promt.h"

void show_main(int);
void input(int);
void view_back(int);
void finish(int);
void cleanup();

void show_info(int);
void show_monitor(int);
void show_invalid_port_input(int);
void show_invalid_dac_input(int);
void write_digital_output0(int);
void write_digital_output1(int);
void write_analog_output0(int);
void write_analog_output1(int);
void show_digital_output0(int);
void show_digital_output1(int);
void show_analog_output0(int);
void show_analog_output1(int);

// selftest group
void show_selftest_info(int);
void start_selftest(int);
void stop_selftest(int);


extern std::vector<View*> win_stack;
extern std::thread t_refresh;

#endif // UI_H
