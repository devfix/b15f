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
constexpr static uint8_t RQ_SET_MEM_8       = 16;
constexpr static uint8_t RQ_GET_MEM_8       = 17;
constexpr static uint8_t RQ_SET_MEM_16      = 18;
constexpr static uint8_t RQ_GET_MEM_16      = 19;

uint8_t const rq_len[] = {
	1 /* RQ_DISCARD */,
	1 /* RQ_TEST */ + 1 /* test byte */,
	1 /* RQ_INFO */,
	1 /* RQ_INT_TEST */ + 1 /* test int high low */ + 1 /* test int high high */,
	1 /* RQ_SELF_TEST */,
	1 /* RQ_DIGITAL_WRITE_0 */ + 1 /* port value */,
	1 /* RQ_DIGITAL_WRITE_1 */ + 1 /* port value */,
	1 /* RQ_DIGITAL_READ_0 */,
	1 /* RQ_DIGITAL_READ_1 */,
	1 /* RQ_READ_DIP_SWITCH */,
	1 /* RQ_ANALOG_WRITE_0 */ + 1 /* test int high low */ + 1 /* test int high high */,
	1 /* RQ_ANALOG_WRITE_1 */ + 1 /* test int high low */ + 1 /* test int high high */,
	1 /* RQ_ANALOG_READ */ + 1 /* adc channel */,
	1 /* RQ_ADC_DAC_STROKE */ + 1 /* channel a */ + 1 /* channel b */ + 1 /* start low */ + 1 /* start high */ + 1 /* delta low */ + 1 /* delta high */ + 1 /* count low */ + 1 /* count high */,
	1 /* RQ_PWM_SET_FREQ */ + 1 /* freq low low */ + 1 /* freq low high */ + 1 /* freq high low */ + 1 /* freq high high */,
	1 /* RQ_PWM_SET_VALUE */ + 1 /* pwm value */,
	1 /* RQ_SET_MEM_8 */ + 1 /* memory address low */ + 1 /* memory address high */ + 1 /* memory value (8-bit) */,
	1 /* RQ_GET_MEM_8 */ + 1 /* memory address low */ + 1 /* memory address high */,
	1 /* RQ_SET_MEM_16 */ + 1 /* memory address low */ + 1 /* memory address high */ + 1 /* memory value low */ + 1 /* memory value high */,
	1 /* RQ_GET_MEM_16 */ + 1 /* memory address low */ + 1 /* memory address high */,
};

#endif // REQUESTS_H
