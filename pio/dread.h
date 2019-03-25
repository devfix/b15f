/***
 * dread.h
 * This file is part of the PIO library.
 * For license information see "pio.h" in the parent directory.
 */

#if !defined(PIOLIB) || PIOLIB < 100
#error This file should be included directly. Use "pio.h" instead.
#endif

#ifndef PIO_DREAD_H
#define PIO_DREAD_H

#define dRead(A) dRead_(A)
#define dRead_(A) DREAD ## _ ## A

#ifdef PA0
#define DREAD_A0 (PINA & 0x01)
#else
#define DREAD_A0 # Pin A0 not supported on this MCU!
#endif
#ifdef PA1
#define DREAD_A1 (PINA & 0x02)
#else
#define DREAD_A1 # Pin A1 not supported on this MCU!
#endif
#ifdef PA2
#define DREAD_A2 (PINA & 0x04)
#else
#define DREAD_A2 # Pin A2 not supported on this MCU!
#endif
#ifdef PA3
#define DREAD_A3 (PINA & 0x08)
#else
#define DREAD_A3 # Pin A3 not supported on this MCU!
#endif
#ifdef PA4
#define DREAD_A4 (PINA & 0x10)
#else
#define DREAD_A4 # Pin A4 not supported on this MCU!
#endif
#ifdef PA5
#define DREAD_A5 (PINA & 0x20)
#else
#define DREAD_A5 # Pin A5 not supported on this MCU!
#endif
#ifdef PA6
#define DREAD_A6 (PINA & 0x40)
#else
#define DREAD_A6 # Pin A6 not supported on this MCU!
#endif
#ifdef PA7
#define DREAD_A7 (PINA & 0x80)
#else
#define DREAD_A7 # Pin A7 not supported on this MCU!
#endif


#ifdef PB0
#define DREAD_B0 (PINB & 0x01)
#else
#define DREAD_B0 # Pin B0 not supported on this MCU!
#endif
#ifdef PB1
#define DREAD_B1 (PINB & 0x02)
#else
#define DREAD_B1 # Pin B1 not supported on this MCU!
#endif
#ifdef PB2
#define DREAD_B2 (PINB & 0x04)
#else
#define DREAD_B2 # Pin B2 not supported on this MCU!
#endif
#ifdef PB3
#define DREAD_B3 (PINB & 0x08)
#else
#define DREAD_B3 # Pin B3 not supported on this MCU!
#endif
#ifdef PB4
#define DREAD_B4 (PINB & 0x10)
#else
#define DREAD_B4 # Pin B4 not supported on this MCU!
#endif
#ifdef PB5
#define DREAD_B5 (PINB & 0x20)
#else
#define DREAD_B5 # Pin B5 not supported on this MCU!
#endif
#ifdef PB6
#define DREAD_B6 (PINB & 0x40)
#else
#define DREAD_B6 # Pin B6 not supported on this MCU!
#endif
#ifdef PB7
#define DREAD_B7 (PINB & 0x80)
#else
#define DREAD_B7 # Pin B7 not supported on this MCU!
#endif


#ifdef PC0
#define DREAD_C0 (PINC & 0x01)
#else
#define DREAD_C0 # Pin C0 not supported on this MCU!
#endif
#ifdef PC1
#define DREAD_C1 (PINC & 0x02)
#else
#define DREAD_C1 # Pin C1 not supported on this MCU!
#endif
#ifdef PC2
#define DREAD_C2 (PINC & 0x04)
#else
#define DREAD_C2 # Pin C2 not supported on this MCU!
#endif
#ifdef PC3
#define DREAD_C3 (PINC & 0x08)
#else
#define DREAD_C3 # Pin C3 not supported on this MCU!
#endif
#ifdef PC4
#define DREAD_C4 (PINC & 0x10)
#else
#define DREAD_C4 # Pin C4 not supported on this MCU!
#endif
#ifdef PC5
#define DREAD_C5 (PINC & 0x20)
#else
#define DREAD_C5 # Pin C5 not supported on this MCU!
#endif
#ifdef PC6
#define DREAD_C6 (PINC & 0x40)
#else
#define DREAD_C6 # Pin C6 not supported on this MCU!
#endif
#ifdef PC7
#define DREAD_C7 (PINC & 0x80)
#else
#define DREAD_C7 # Pin C7 not supported on this MCU!
#endif


#ifdef PD0
#define DREAD_D0 (PIND & 0x01)
#else
#define DREAD_D0 # Pin D0 not supported on this MCU!
#endif
#ifdef PD1
#define DREAD_D1 (PIND & 0x02)
#else
#define DREAD_D1 # Pin D1 not supported on this MCU!
#endif
#ifdef PD2
#define DREAD_D2 (PIND & 0x04)
#else
#define DREAD_D2 # Pin D2 not supported on this MCU!
#endif
#ifdef PD3
#define DREAD_D3 (PIND & 0x08)
#else
#define DREAD_D3 # Pin D3 not supported on this MCU!
#endif
#ifdef PD4
#define DREAD_D4 (PIND & 0x10)
#else
#define DREAD_D4 # Pin D4 not supported on this MCU!
#endif
#ifdef PD5
#define DREAD_D5 (PIND & 0x20)
#else
#define DREAD_D5 # Pin D5 not supported on this MCU!
#endif
#ifdef PD6
#define DREAD_D6 (PIND & 0x40)
#else
#define DREAD_D6 # Pin D6 not supported on this MCU!
#endif
#ifdef PD7
#define DREAD_D7 (PIND & 0x80)
#else
#define DREAD_D7 # Pin D7 not supported on this MCU!
#endif
#endif // PIO_DREAD_H
