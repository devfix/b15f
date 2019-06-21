#include "global_vars.h"

volatile SPI spi;
volatile MCP23S17 dio0(spi, SPIADR::BEBA0);
volatile MCP23S17 dio1(spi, SPIADR::BEBA1);
volatile MCP23S17 dsw(spi, SPIADR::SWITCH);
volatile TLC5615 dac0(spi, SPIADR::AA0);
volatile TLC5615 dac1(spi, SPIADR::AA1);
volatile ADU adu;
volatile USART usart;
volatile PWM pwm;
volatile bool nextRequest = false;
volatile uint16_t interruptCounters[35];
