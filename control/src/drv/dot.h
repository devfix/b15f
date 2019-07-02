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
     * \return the x coordinate
     */
    uint16_t getX(void) const;

    /**
     * \return the y coordinate
     */
    uint16_t getY(void) const;

    /**
     * \return the curve index
     */
    uint8_t getCurve(void) const;

private:
    const uint16_t x, y; //!< coordinates of this dot
    const uint8_t curve; //!< curve index of this dot
};


#endif // DOT_H
