#ifndef SPI_MASTER_H
#define SPI_MASTER_H

#include <util/delay.h>
#include "pio.h"

#define MOSI B5
#define MISO B6
#define SCLK B7

class SPI {
public:
	SPI(void);
	void init(void) const;

};

#endif
