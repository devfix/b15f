#ifndef REQUEST_HANDLERS_H
#define REQUEST_HANDLERS_H

#include <avr/wdt.h>
#include "../control/src/drv/requests.h"
#include "global_vars.h"
#include "selftest.h"
#include "boardinfo.h"
#include "pwm.h"

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
void rqPwmSetFreq(void);
void rqPwmSetValue(void);
void rqSetMem8(void);
void rqGetMem8(void);
void rqSetMem16(void);
void rqGetMem16(void);
void rqGetInterruptCounterOffset(void);

#endif // REQUEST_HANDLERS_H
