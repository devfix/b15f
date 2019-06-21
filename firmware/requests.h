#ifndef REQUESTS_H
#define REQUESTS_H

constexpr static uint8_t RQ_DISCARD         = 0;
constexpr static uint8_t RQ_TEST            = 1;
constexpr static uint8_t RQ_INFO            = 2;
constexpr static uint8_t RQ_INT_TEST        = 3;
constexpr static uint8_t RQ_SELF_TEST       = 4;
constexpr static uint8_t RQ_DIGITAL_WRITE_0 = 5;
constexpr static uint8_t RQ_DIGITAL_WRITE_1 = 6;
constexpr static uint8_t RQ_DIGITAL_READ_0  = 7;
constexpr static uint8_t RQ_DIGITAL_READ_1  = 8;
constexpr static uint8_t RQ_READ_DIP_SWITCH = 9;
constexpr static uint8_t RQ_ANALOG_WRITE_0  = 10;
constexpr static uint8_t RQ_ANALOG_WRITE_1  = 11;
constexpr static uint8_t RQ_ANALOG_READ     = 12;
constexpr static uint8_t RQ_ADC_DAC_STROKE  = 13;
constexpr static uint8_t RQ_PWM_SET_FREQ    = 14;
constexpr static uint8_t RQ_PWM_SET_VALUE   = 15;
constexpr static uint8_t RQ_SET_REGISTER    = 16;
constexpr static uint8_t RQ_GET_REGISTER    = 17;

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
	/* RQ_PWM_SET_FREQ */ 5,
	/* RQ_PWM_SET_VALUE */ 2,
	/* RQ_SET_REG */ 3,
	/* RQ_GET_REG */ 2
};

#endif // REQUESTS_H
