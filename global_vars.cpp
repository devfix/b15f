#include "global_vars.h"

SPI spi;
MCP23S17 beba0(spi, SPIADR::BEBA0);
MCP23S17 beba1(spi, SPIADR::BEBA1);
MCP23S17 sw(spi, SPIADR::SWITCH);
TLC5615 dac0(spi, SPIADR::AA0);
TLC5615 dac1(spi, SPIADR::AA1);
ADU adu;
USART usart;
