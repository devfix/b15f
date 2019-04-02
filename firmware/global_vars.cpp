#include "global_vars.h"

volatile SPI spi;
volatile MCP23S17 beba0(*((SPI*) &spi), SPIADR::BEBA0);
volatile MCP23S17 beba1(*((SPI*) &spi), SPIADR::BEBA1);
volatile MCP23S17 sw(*((SPI*) &spi), SPIADR::SWITCH);
volatile TLC5615 dac0(*((SPI*) &spi), SPIADR::AA0);
volatile TLC5615 dac1(*((SPI*) &spi), SPIADR::AA1);
volatile ADU adu;
volatile USART usart;


volatile uint8_t receive_buffer[32];
volatile uint8_t receive_pos;
volatile uint8_t send_buffer[32];
volatile uint8_t send_pos;
volatile uint8_t send_len;
