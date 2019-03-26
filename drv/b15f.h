#ifndef B15F_h
#define B15F_h

#include <iostream>

class B15F
{
private:
	B15F(void); // privater Konstruktor
public:
	void init(void);
	static B15F& getInstance(void);

private:
	static B15F* instance;
};

#endif // B15F_h
