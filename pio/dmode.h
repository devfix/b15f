/***
 * dmode.h
 * This file is part of the PIO library.
 * For license information see "pio.h" in the parent directory.
 */

#if !defined(PIOLIB) || PIOLIB < 100
#error This file should be included directly. Use "pio.h" instead.
#endif

#ifndef PIO_DMODE_H
#define PIO_DMODE_H

#define dMode(A, B) dMode_(A, B)
#define dMode_(A, B) DMODE ## _ ## A ## _ ## B

#ifdef PA0
#define DMODE_A0_1 DDRA |= 0x01
#define DMODE_A0_0 DDRA &= 0xFE
#else
#define DMODE_A0_1 # Pin A0 not supported on this MCU!
#define DMODE_A0_0 DMODE_A0_1
#endif
#ifdef PA1
#define DMODE_A1_1 DDRA |= 0x02
#define DMODE_A1_0 DDRA &= 0xFD
#else
#define DMODE_A1_1 # Pin A1 not supported on this MCU!
#define DMODE_A1_0 DMODE_A1_1
#endif
#ifdef PA2
#define DMODE_A2_1 DDRA |= 0x04
#define DMODE_A2_0 DDRA &= 0xFB
#else
#define DMODE_A2_1 # Pin A2 not supported on this MCU!
#define DMODE_A2_0 DMODE_A2_1
#endif
#ifdef PA3
#define DMODE_A3_1 DDRA |= 0x08
#define DMODE_A3_0 DDRA &= 0xF7
#else
#define DMODE_A3_1 # Pin A3 not supported on this MCU!
#define DMODE_A3_0 DMODE_A3_1
#endif
#ifdef PA4
#define DMODE_A4_1 DDRA |= 0x10
#define DMODE_A4_0 DDRA &= 0xEF
#else
#define DMODE_A4_1 # Pin A4 not supported on this MCU!
#define DMODE_A4_0 DMODE_A4_1
#endif
#ifdef PA5
#define DMODE_A5_1 DDRA |= 0x20
#define DMODE_A5_0 DDRA &= 0xDF
#else
#define DMODE_A5_1 # Pin A5 not supported on this MCU!
#define DMODE_A5_0 DMODE_A5_1
#endif
#ifdef PA6
#define DMODE_A6_1 DDRA |= 0x40
#define DMODE_A6_0 DDRA &= 0xBF
#else
#define DMODE_A6_1 # Pin A6 not supported on this MCU!
#define DMODE_A6_0 DMODE_A6_1
#endif
#ifdef PA7
#define DMODE_A7_1 DDRA |= 0x80
#define DMODE_A7_0 DDRA &= 0x7F
#else
#define DMODE_A7_1 # Pin A7 not supported on this MCU!
#define DMODE_A7_0 DMODE_A7_1
#endif


#ifdef PB0
#define DMODE_B0_1 DDRB |= 0x01
#define DMODE_B0_0 DDRB &= 0xFE
#else
#define DMODE_B0_1 # Pin B0 not supported on this MCU!
#define DMODE_B0_0 DMODE_B0_1
#endif
#ifdef PB1
#define DMODE_B1_1 DDRB |= 0x02
#define DMODE_B1_0 DDRB &= 0xFD
#else
#define DMODE_B1_1 # Pin B1 not supported on this MCU!
#define DMODE_B1_0 DMODE_B1_1
#endif
#ifdef PB2
#define DMODE_B2_1 DDRB |= 0x04
#define DMODE_B2_0 DDRB &= 0xFB
#else
#define DMODE_B2_1 # Pin B2 not supported on this MCU!
#define DMODE_B2_0 DMODE_B2_1
#endif
#ifdef PB3
#define DMODE_B3_1 DDRB |= 0x08
#define DMODE_B3_0 DDRB &= 0xF7
#else
#define DMODE_B3_1 # Pin B3 not supported on this MCU!
#define DMODE_B3_0 DMODE_B3_1
#endif
#ifdef PB4
#define DMODE_B4_1 DDRB |= 0x10
#define DMODE_B4_0 DDRB &= 0xEF
#else
#define DMODE_B4_1 # Pin B4 not supported on this MCU!
#define DMODE_B4_0 DMODE_B4_1
#endif
#ifdef PB5
#define DMODE_B5_1 DDRB |= 0x20
#define DMODE_B5_0 DDRB &= 0xDF
#else
#define DMODE_B5_1 # Pin B5 not supported on this MCU!
#define DMODE_B5_0 DMODE_B5_1
#endif
#ifdef PB6
#define DMODE_B6_1 DDRB |= 0x40
#define DMODE_B6_0 DDRB &= 0xBF
#else
#define DMODE_B6_1 # Pin B6 not supported on this MCU!
#define DMODE_B6_0 DMODE_B6_1
#endif
#ifdef PB7
#define DMODE_B7_1 DDRB |= 0x80
#define DMODE_B7_0 DDRB &= 0x7F
#else
#define DMODE_B7_1 # Pin B7 not supported on this MCU!
#define DMODE_B7_0 DMODE_B7_1
#endif


#ifdef PC0
#define DMODE_C0_1 DDRC |= 0x01
#define DMODE_C0_0 DDRC &= 0xFE
#else
#define DMODE_C0_1 # Pin C0 not supported on this MCU!
#define DMODE_C0_0 DMODE_C0_1
#endif
#ifdef PC1
#define DMODE_C1_1 DDRC |= 0x02
#define DMODE_C1_0 DDRC &= 0xFD
#else
#define DMODE_C1_1 # Pin C1 not supported on this MCU!
#define DMODE_C1_0 DMODE_C1_1
#endif
#ifdef PC2
#define DMODE_C2_1 DDRC |= 0x04
#define DMODE_C2_0 DDRC &= 0xFB
#else
#define DMODE_C2_1 # Pin C2 not supported on this MCU!
#define DMODE_C2_0 DMODE_C2_1
#endif
#ifdef PC3
#define DMODE_C3_1 DDRC |= 0x08
#define DMODE_C3_0 DDRC &= 0xF7
#else
#define DMODE_C3_1 # Pin C3 not supported on this MCU!
#define DMODE_C3_0 DMODE_C3_1
#endif
#ifdef PC4
#define DMODE_C4_1 DDRC |= 0x10
#define DMODE_C4_0 DDRC &= 0xEF
#else
#define DMODE_C4_1 # Pin C4 not supported on this MCU!
#define DMODE_C4_0 DMODE_C4_1
#endif
#ifdef PC5
#define DMODE_C5_1 DDRC |= 0x20
#define DMODE_C5_0 DDRC &= 0xDF
#else
#define DMODE_C5_1 # Pin C5 not supported on this MCU!
#define DMODE_C5_0 DMODE_C5_1
#endif
#ifdef PC6
#define DMODE_C6_1 DDRC |= 0x40
#define DMODE_C6_0 DDRC &= 0xBF
#else
#define DMODE_C6_1 # Pin C6 not supported on this MCU!
#define DMODE_C6_0 DMODE_C6_1
#endif
#ifdef PC7
#define DMODE_C7_1 DDRC |= 0x80
#define DMODE_C7_0 DDRC &= 0x7F
#else
#define DMODE_C7_1 # Pin C7 not supported on this MCU!
#define DMODE_C7_0 DMODE_C7_1
#endif


#ifdef PD0
#define DMODE_D0_1 DDRD |= 0x01
#define DMODE_D0_0 DDRD &= 0xFE
#else
#define DMODE_D0_1 # Pin D0 not supported on this MCU!
#define DMODE_D0_0 DMODE_D0_1
#endif
#ifdef PD1
#define DMODE_D1_1 DDRD |= 0x02
#define DMODE_D1_0 DDRD &= 0xFD
#else
#define DMODE_D1_1 # Pin D1 not supported on this MCU!
#define DMODE_D1_0 DMODE_D1_1
#endif
#ifdef PD2
#define DMODE_D2_1 DDRD |= 0x04
#define DMODE_D2_0 DDRD &= 0xFB
#else
#define DMODE_D2_1 # Pin D2 not supported on this MCU!
#define DMODE_D2_0 DMODE_D2_1
#endif
#ifdef PD3
#define DMODE_D3_1 DDRD |= 0x08
#define DMODE_D3_0 DDRD &= 0xF7
#else
#define DMODE_D3_1 # Pin D3 not supported on this MCU!
#define DMODE_D3_0 DMODE_D3_1
#endif
#ifdef PD4
#define DMODE_D4_1 DDRD |= 0x10
#define DMODE_D4_0 DDRD &= 0xEF
#else
#define DMODE_D4_1 # Pin D4 not supported on this MCU!
#define DMODE_D4_0 DMODE_D4_1
#endif
#ifdef PD5
#define DMODE_D5_1 DDRD |= 0x20
#define DMODE_D5_0 DDRD &= 0xDF
#else
#define DMODE_D5_1 # Pin D5 not supported on this MCU!
#define DMODE_D5_0 DMODE_D5_1
#endif
#ifdef PD6
#define DMODE_D6_1 DDRD |= 0x40
#define DMODE_D6_0 DDRD &= 0xBF
#else
#define DMODE_D6_1 # Pin D6 not supported on this MCU!
#define DMODE_D6_0 DMODE_D6_1
#endif
#ifdef PD7
#define DMODE_D7_1 DDRD |= 0x80
#define DMODE_D7_0 DDRD &= 0x7F
#else
#define DMODE_D7_1 # Pin D7 not supported on this MCU!
#define DMODE_D7_0 DMODE_D7_1
#endif

#endif // PIO_DMODE_H
