/***
 * impl0.h
 * This file is part of the PIO library.
 * For license information see "pio.h" in the super parent directory.
 */

#if !defined(PIOLIB) || PIOLIB < 100
#error This file should be included directly. Use "pio.h" instead.
#endif

#ifndef F_CPU
#error F_CPU not defined!
#endif

#ifndef F_I2C
#ifndef PIO_DISABLE_I2C
#warning F_I2C not defined, I2C disabled.
#endif
#else

#include <stdlib.h>

// AVR TWI master transmitter status codes
#define TWS_START          0x08
#define TWS_REPEATED_START 0x10
#define TWS_ADDR_ACK       0x18
#define TWS_ADDR_NOT_ACK   0x20
#define TWS_DATA_ACK       0x28
#define TWS_DATA_NOT_ACK   0x30
#define TWS_ARB_LOST       0x38

// functions
void i2cInit(void);
void i2cBeginTransmission(uint8_t);
void i2cSend(uint8_t);
void i2cEndTransmission(void);

// error function pointer
void (*i2cError)(void) = NULL;

void i2cInit() {
    // i2c clock speed, see SCL frequency formula in datasheet
    uint16_t sp = F_CPU / F_I2C - 16;
    uint16_t bp = sp;
    while(sp > 510) {
        TWSR++;
        sp /= 4;
    }
    TWBR = bp / (1<<(2*(TWSR & 0x03)+1));
}

void i2cBeginTransmission(uint8_t addr) {
    TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWSTA);
    while (!(TWCR & _BV(TWINT)));
    if((TWSR & 0xF8) != TWS_START)
        i2cError();

    TWDR = (addr & 0xFE) << 1;
    TWCR = _BV(TWEN) | _BV(TWINT);
    while (!(TWCR & _BV(TWINT)));
    if((TWSR & 0xF8) != TWS_ADDR_ACK)
        i2cError();
}

void i2cSend(uint8_t b) {
    TWDR = b;
    TWCR = _BV(TWEN) | _BV(TWINT);
    while (!(TWCR & _BV(TWINT)));
    if((TWSR & 0xF8) != TWS_DATA_ACK)
        i2cError();
}

void i2cEndTransmission() {
    TWCR = _BV(TWEN) | _BV(TWINT) | _BV(TWSTO);
    while (TWCR & _BV(TWSTO));
}

#endif
