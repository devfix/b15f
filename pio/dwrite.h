/***
 * dwrite.h
 * This file is part of the PIO library.
 * For license information see "pio.h" in the parent directory.
 */

#if !defined(PIOLIB) || PIOLIB < 100
#error This file should be included directly. Use "pio.h" instead.
#endif

#ifndef PIO_DWRITE_H
#define PIO_DWRITE_H

#define dWrite(A, B) dWrite_(A, B)
#define dWrite_(A, B) DWRITE ## _ ## A ## _ ## B

#ifdef PA0
#define DWRITE_A0_1 PORTA |= 0x01
#define DWRITE_A0_0 PORTA &= 0xFE
#else
#define DWRITE_A0_1 # Pin A0 not supported on this MCU!
#define DWRITE_A0_0 DWRITE_A0_1
#endif
#ifdef PA1
#define DWRITE_A1_1 PORTA |= 0x02
#define DWRITE_A1_0 PORTA &= 0xFD
#else
#define DWRITE_A1_1 # Pin A1 not supported on this MCU!
#define DWRITE_A1_0 DWRITE_A1_1
#endif
#ifdef PA2
#define DWRITE_A2_1 PORTA |= 0x04
#define DWRITE_A2_0 PORTA &= 0xFB
#else
#define DWRITE_A2_1 # Pin A2 not supported on this MCU!
#define DWRITE_A2_0 DWRITE_A2_1
#endif
#ifdef PA3
#define DWRITE_A3_1 PORTA |= 0x08
#define DWRITE_A3_0 PORTA &= 0xF7
#else
#define DWRITE_A3_1 # Pin A3 not supported on this MCU!
#define DWRITE_A3_0 DWRITE_A3_1
#endif
#ifdef PA4
#define DWRITE_A4_1 PORTA |= 0x10
#define DWRITE_A4_0 PORTA &= 0xEF
#else
#define DWRITE_A4_1 # Pin A4 not supported on this MCU!
#define DWRITE_A4_0 DWRITE_A4_1
#endif
#ifdef PA5
#define DWRITE_A5_1 PORTA |= 0x20
#define DWRITE_A5_0 PORTA &= 0xDF
#else
#define DWRITE_A5_1 # Pin A5 not supported on this MCU!
#define DWRITE_A5_0 DWRITE_A5_1
#endif
#ifdef PA6
#define DWRITE_A6_1 PORTA |= 0x40
#define DWRITE_A6_0 PORTA &= 0xBF
#else
#define DWRITE_A6_1 # Pin A6 not supported on this MCU!
#define DWRITE_A6_0 DWRITE_A6_1
#endif
#ifdef PA7
#define DWRITE_A7_1 PORTA |= 0x80
#define DWRITE_A7_0 PORTA &= 0x7F
#else
#define DWRITE_A7_1 # Pin A7 not supported on this MCU!
#define DWRITE_A7_0 DWRITE_A7_1
#endif


#ifdef PB0
#define DWRITE_B0_1 PORTB |= 0x01
#define DWRITE_B0_0 PORTB &= 0xFE
#else
#define DWRITE_B0_1 # Pin B0 not supported on this MCU!
#define DWRITE_B0_0 DWRITE_B0_1
#endif
#ifdef PB1
#define DWRITE_B1_1 PORTB |= 0x02
#define DWRITE_B1_0 PORTB &= 0xFD
#else
#define DWRITE_B1_1 # Pin B1 not supported on this MCU!
#define DWRITE_B1_0 DWRITE_B1_1
#endif
#ifdef PB2
#define DWRITE_B2_1 PORTB |= 0x04
#define DWRITE_B2_0 PORTB &= 0xFB
#else
#define DWRITE_B2_1 # Pin B2 not supported on this MCU!
#define DWRITE_B2_0 DWRITE_B2_1
#endif
#ifdef PB3
#define DWRITE_B3_1 PORTB |= 0x08
#define DWRITE_B3_0 PORTB &= 0xF7
#else
#define DWRITE_B3_1 # Pin B3 not supported on this MCU!
#define DWRITE_B3_0 DWRITE_B3_1
#endif
#ifdef PB4
#define DWRITE_B4_1 PORTB |= 0x10
#define DWRITE_B4_0 PORTB &= 0xEF
#else
#define DWRITE_B4_1 # Pin B4 not supported on this MCU!
#define DWRITE_B4_0 DWRITE_B4_1
#endif
#ifdef PB5
#define DWRITE_B5_1 PORTB |= 0x20
#define DWRITE_B5_0 PORTB &= 0xDF
#else
#define DWRITE_B5_1 # Pin B5 not supported on this MCU!
#define DWRITE_B5_0 DWRITE_B5_1
#endif
#ifdef PB6
#define DWRITE_B6_1 PORTB |= 0x40
#define DWRITE_B6_0 PORTB &= 0xBF
#else
#define DWRITE_B6_1 # Pin B6 not supported on this MCU!
#define DWRITE_B6_0 DWRITE_B6_1
#endif
#ifdef PB7
#define DWRITE_B7_1 PORTB |= 0x80
#define DWRITE_B7_0 PORTB &= 0x7F
#else
#define DWRITE_B7_1 # Pin B7 not supported on this MCU!
#define DWRITE_B7_0 DWRITE_B7_1
#endif


#ifdef PC0
#define DWRITE_C0_1 PORTC |= 0x01
#define DWRITE_C0_0 PORTC &= 0xFE
#else
#define DWRITE_C0_1 # Pin C0 not supported on this MCU!
#define DWRITE_C0_0 DWRITE_C0_1
#endif
#ifdef PC1
#define DWRITE_C1_1 PORTC |= 0x02
#define DWRITE_C1_0 PORTC &= 0xFD
#else
#define DWRITE_C1_1 # Pin C1 not supported on this MCU!
#define DWRITE_C1_0 DWRITE_C1_1
#endif
#ifdef PC2
#define DWRITE_C2_1 PORTC |= 0x04
#define DWRITE_C2_0 PORTC &= 0xFB
#else
#define DWRITE_C2_1 # Pin C2 not supported on this MCU!
#define DWRITE_C2_0 DWRITE_C2_1
#endif
#ifdef PC3
#define DWRITE_C3_1 PORTC |= 0x08
#define DWRITE_C3_0 PORTC &= 0xF7
#else
#define DWRITE_C3_1 # Pin C3 not supported on this MCU!
#define DWRITE_C3_0 DWRITE_C3_1
#endif
#ifdef PC4
#define DWRITE_C4_1 PORTC |= 0x10
#define DWRITE_C4_0 PORTC &= 0xEF
#else
#define DWRITE_C4_1 # Pin C4 not supported on this MCU!
#define DWRITE_C4_0 DWRITE_C4_1
#endif
#ifdef PC5
#define DWRITE_C5_1 PORTC |= 0x20
#define DWRITE_C5_0 PORTC &= 0xDF
#else
#define DWRITE_C5_1 # Pin C5 not supported on this MCU!
#define DWRITE_C5_0 DWRITE_C5_1
#endif
#ifdef PC6
#define DWRITE_C6_1 PORTC |= 0x40
#define DWRITE_C6_0 PORTC &= 0xBF
#else
#define DWRITE_C6_1 # Pin C6 not supported on this MCU!
#define DWRITE_C6_0 DWRITE_C6_1
#endif
#ifdef PC7
#define DWRITE_C7_1 PORTC |= 0x80
#define DWRITE_C7_0 PORTC &= 0x7F
#else
#define DWRITE_C7_1 # Pin C7 not supported on this MCU!
#define DWRITE_C7_0 DWRITE_C7_1
#endif


#ifdef PD0
#define DWRITE_D0_1 PORTD |= 0x01
#define DWRITE_D0_0 PORTD &= 0xFE
#else
#define DWRITE_D0_1 # Pin D0 not supported on this MCU!
#define DWRITE_D0_0 DWRITE_D0_1
#endif
#ifdef PD1
#define DWRITE_D1_1 PORTD |= 0x02
#define DWRITE_D1_0 PORTD &= 0xFD
#else
#define DWRITE_D1_1 # Pin D1 not supported on this MCU!
#define DWRITE_D1_0 DWRITE_D1_1
#endif
#ifdef PD2
#define DWRITE_D2_1 PORTD |= 0x04
#define DWRITE_D2_0 PORTD &= 0xFB
#else
#define DWRITE_D2_1 # Pin D2 not supported on this MCU!
#define DWRITE_D2_0 DWRITE_D2_1
#endif
#ifdef PD3
#define DWRITE_D3_1 PORTD |= 0x08
#define DWRITE_D3_0 PORTD &= 0xF7
#else
#define DWRITE_D3_1 # Pin D3 not supported on this MCU!
#define DWRITE_D3_0 DWRITE_D3_1
#endif
#ifdef PD4
#define DWRITE_D4_1 PORTD |= 0x10
#define DWRITE_D4_0 PORTD &= 0xEF
#else
#define DWRITE_D4_1 # Pin D4 not supported on this MCU!
#define DWRITE_D4_0 DWRITE_D4_1
#endif
#ifdef PD5
#define DWRITE_D5_1 PORTD |= 0x20
#define DWRITE_D5_0 PORTD &= 0xDF
#else
#define DWRITE_D5_1 # Pin D5 not supported on this MCU!
#define DWRITE_D5_0 DWRITE_D5_1
#endif
#ifdef PD6
#define DWRITE_D6_1 PORTD |= 0x40
#define DWRITE_D6_0 PORTD &= 0xBF
#else
#define DWRITE_D6_1 # Pin D6 not supported on this MCU!
#define DWRITE_D6_0 DWRITE_D6_1
#endif
#ifdef PD7
#define DWRITE_D7_1 PORTD |= 0x80
#define DWRITE_D7_0 PORTD &= 0x7F
#else
#define DWRITE_D7_1 # Pin D7 not supported on this MCU!
#define DWRITE_D7_0 DWRITE_D7_1
#endif


#endif // PIO_DWRITE_H
