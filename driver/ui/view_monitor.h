#ifndef VIEW_MONITOR_H
#define VIEW_MONITOR_H

#include <thread>
#include <chrono>
#include "view_info.h"

class ViewMonitor : public ViewInfo
{
	
public:
	ViewMonitor(void);
	virtual std::function<void(int)> keypress(int& key) override;

protected:
	virtual void worker(void);
	volatile bool run_worker = true;
	std::thread t_worker;
	
};

#endif // VIEW_MONITOR_H
