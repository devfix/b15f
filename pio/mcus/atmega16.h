/***
 * atmega16.h
 * This file is part of the PIO library.
 * For license information see "pio.h" in the super parent directory.
 */

#if !defined(PIOLIB) || PIOLIB < 100
#error This file should not be included directly. Use "pio.h" instead.
#endif

#ifdef __AVR_ATmega16__

#define MCU ATmega16

#include "../i2c/impl0.h"

#endif
