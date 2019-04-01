#include "dot.h"

Dot::Dot(uint16_t x, uint16_t y, uint8_t curve) : x(x), y(y), curve(curve)
{
	if(curve >= 64)
		throw std::range_error("Kurvenindex muss im Bereich [0, 63] liegen");
}

uint16_t Dot::getX() const
{
	return x;
}

uint16_t Dot::getY() const
{
	return y;
}

uint8_t Dot::getCurve(void) const
{
	return curve;
}
