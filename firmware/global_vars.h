#ifndef GLOBAL_VARS_H
#define GLOBAL_VARS_H

#include "mcp23s17.h"
#include "tlc5615.h"
#include "adu.h"
#include "usart.h"

extern volatile SPI spi;
extern volatile MCP23S17 beba0;
extern volatile MCP23S17 beba1;
extern volatile MCP23S17 sw;
extern volatile TLC5615 dac0;
extern volatile TLC5615 dac1;
extern volatile ADU adu;
extern volatile USART usart;

extern volatile uint8_t receive_buffer[32];
extern volatile uint8_t receive_pos;
extern volatile uint8_t send_buffer[32];
extern volatile uint8_t send_pos;
extern volatile uint8_t send_len;
extern volatile bool send_active;
#endif // GLOBAL_VARS_H
