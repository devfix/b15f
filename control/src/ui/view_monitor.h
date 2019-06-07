#ifndef VIEW_MONITOR_H
#define VIEW_MONITOR_H

#include <thread>
#include <chrono>
#include <sstream>
#include <bitset>
#include "view_info.h"
#include "../drv/b15f.h"

/*! View to display all B15 inputs. */

class ViewMonitor : public ViewInfo
{

public:
    ViewMonitor(void);
    virtual call_t keypress(int& key) override;

private:
    std::string fancyDigitalString(uint8_t& b);
    std::string fancyAnalogString(uint16_t& v);

protected:
    virtual void worker(void);
    volatile bool run_worker = true;
    std::thread t_worker;

};

#endif // VIEW_MONITOR_H
