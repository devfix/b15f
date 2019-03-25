/***
 * mcus.h
 * This file is part of the PIO library.
 * For license information see "pio.h" in the parent directory.
 */

#if !defined(PIOLIB) || PIOLIB < 100
#error This file should be included directly. Use "pio.h" instead.
#endif

#ifndef PIO_MCUS_H
#define PIO_MCUS_H

#include "mcus/atmega328p.h"
#include "mcus/atmega16.h"
#include "mcus/atmega1284.h"

#ifndef MCU
#error No compatible MCU header file found.
#endif

#endif // PIO_MCUS_H
