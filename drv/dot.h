#ifndef DOT_H
#define DOT_H

#include <cstdint>

enum DotColor
{
	PURPLE = 0,
	GREEN  = 32,
};

class Dot
{
public:
	Dot(uint16_t x, uint16_t y, DotColor color);
	uint16_t getX(void) const;
	uint16_t getY(void) const;
	DotColor getColor(void) const;
	
private:
	uint16_t x, y;
	DotColor color;
};


#endif // DOT_H
