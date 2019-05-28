#ifndef REQUESTS_H
#define REQUESTS_H

#include <avr/wdt.h>
#include "global_vars.h"
#include "selftest.h"
#include "boardinfo.h"
#include "pwm.h"

constexpr static uint8_t RQ_DISC = 0;
constexpr static uint8_t RQ_TEST = 1;
constexpr static uint8_t RQ_INFO = 2;
constexpr static uint8_t RQ_INT  = 3;
constexpr static uint8_t RQ_ST   = 4;
constexpr static uint8_t RQ_BA0  = 5;
constexpr static uint8_t RQ_BA1  = 6;
constexpr static uint8_t RQ_BE0  = 7;
constexpr static uint8_t RQ_BE1  = 8;
constexpr static uint8_t RQ_DSW  = 9;
constexpr static uint8_t RQ_AA0  = 10;
constexpr static uint8_t RQ_AA1  = 11;
constexpr static uint8_t RQ_ADC  = 12;
constexpr static uint8_t RQ_ADC_DAC_STROKE  = 13;
constexpr static uint8_t RQ_SET_PWM  = 14;

uint8_t const rq_len[] = {
	/* RQ_DISC */ 1,
	/* RQ_TEST */ 2,
	/* RQ_INFO */ 1,
	/* RQ_INT  */ 3,
	/* RQ_ST   */ 1,
	/* RQ_BA0  */ 2,
	/* RQ_BA1  */ 2,
	/* RQ_BE0  */ 1,
	/* RQ_BE1  */ 1,
	/* RQ_DSW  */ 1,
	/* RQ_AA0  */ 3,
	/* RQ_AA1  */ 3,
	/* RQ_ADC  */ 2,
	/* RQ_ADC_DAC_STROKE */ 9,
	/* RQ_SET_PWM */ 2
};

/**
 * Hauptfunktion für die Verarbeitung einer neuen empfangen Request
 */
void handleRequest(void);

// spezifische Funktion für jede Request
void rqTestConnection(void);
void rqBoardInfo(void);
void rqTestIntConv(void);
void rqTestLongConv(void);
void rqSelfTest(void);
void rqDigitalWrite0(void);
void rqDigitalWrite1(void);
void rqDigitalRead0(void);
void rqDigitalRead1(void);
void rqReadDipSwitch(void);
void rqAnalogWrite0(void);
void rqAnalogWrite1(void);
void rqAnalogRead(void);
void rqAdcDacStroke(void);
void rqSetPwm(void);

#endif // REQUESTS_H
