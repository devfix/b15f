#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#include "mcp23s17.h"
#include "tlc5615.h"
#include "adu.h"

extern SPI spi;
extern MCP23S17 beba0;
extern MCP23S17 beba1;
extern MCP23S17 sw;
extern TLC5615 dac0;
extern TLC5615 dac1;
extern ADU adu;

#endif // GLOBAL_VARS_H
