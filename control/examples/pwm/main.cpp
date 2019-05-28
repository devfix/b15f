#include <iostream>
#include <cmath>
#include <b15f/b15f.h>
#include <b15f/plottyfile.h>

const char PLOT_FILE[] = "plot.bin";

int main()
{
	
	B15F& drv = B15F::getInstance();
	std::cout << "TOP: " << (int) drv.pwmSetFrequency(100000) << std::endl;
        drv.pwmSetValue(40);
}
