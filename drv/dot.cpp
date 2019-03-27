#include "dot.h"

Dot::Dot(uint16_t x, uint16_t y, DotColor color) : x(x), y(y), color(color)
{
}

uint16_t Dot::getX() const
{
	return x;
}

uint16_t Dot::getY() const
{
	return y;
}

DotColor Dot::getColor(void) const
{
	return color;
}
