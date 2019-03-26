#include <iostream>
#include "drv/b15f.h"

int main()
{
	B15F& drv = B15F::getInstance();
	drv.init();
	std::cout << "Schluss." << std::endl;
}
