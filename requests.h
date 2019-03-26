#ifndef REQUESTS_H
#define REQUESTS_H

#include "global_vars.h"

constexpr static uint8_t RQ_DISC = 0;
constexpr static uint8_t RQ_TEST = 1;
constexpr static uint8_t RQ_INFO = 2;
constexpr static uint8_t RQ_INT  = 3;

void rqTestConnection(void);
void rqBoardInfo(void);
void rqTestIntConv(void);
void rqTestLongConv(void);

#endif // REQUESTS_H
