#ifndef DOT_H
#define DOT_H

#include <cstdint>
#include <stdexcept>

class Dot
{
public:
	Dot(uint16_t x, uint16_t y, uint8_t curve);
	uint16_t getX(void) const;
	uint16_t getY(void) const;
	uint8_t getCurve(void) const;
	
private:
	uint16_t x, y;
	uint8_t curve;
};


#endif // DOT_H
