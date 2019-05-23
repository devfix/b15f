#ifndef DOT_H
#define DOT_H

#include <cstdint>
#include <stdexcept>

/**
 * Immutable dot class with x and y coordinate and curve index.
 * Dots with the same curve index get the same color by plotty.
 */

class Dot
{
public:
    /**
     * Constructor with x and y coordinate and curve index.
     */
    Dot(uint16_t x, uint16_t y, uint8_t curve);

    /**
     * Returns the x coordinate.
     */
    uint16_t getX(void) const;

    /**
     * Returns the y coordinate.
     */
    uint16_t getY(void) const;

    /**
     * Returns the curve index.
     */
    uint8_t getCurve(void) const;

private:
    uint16_t x, y;
    uint8_t curve;
};


#endif // DOT_H
