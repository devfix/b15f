#include "b15f.h"

B15F* B15F::instance = nullptr;

B15F::B15F()
{
}

void B15F::init(void)
{
	std::cout << "moint: " << std::endl;
}

B15F& B15F::getInstance(void)
{
	if(!instance)
		instance = new B15F();

	return *instance;
}
