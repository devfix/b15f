#include "request_handlers.h"

void handleRequest()
{
	const uint8_t req = usart.readByte();
	
	wdt_reset();
	
	switch(req)
	{
		case RQ_DISCARD:
			break;

		case RQ_TEST:
			rqTestConnection();
			break;
		
		case RQ_INFO:
			rqBoardInfo();
			break;
		
		case RQ_INT_TEST:
			rqTestIntConv();
			break;

		case RQ_SELF_TEST:
			rqSelfTest();
			break;
			
		case RQ_DIGITAL_WRITE_0:
			rqDigitalWrite0();
			break;

		case RQ_DIGITAL_WRITE_1:
			rqDigitalWrite1();
			break;

		case RQ_DIGITAL_READ_0:
			rqDigitalRead0();
			break;

		case RQ_DIGITAL_READ_1:
			rqDigitalRead1();
			break;
			
		case RQ_READ_DIP_SWITCH:
			rqReadDipSwitch();
			break;

		case RQ_ANALOG_WRITE_0:
			rqAnalogWrite0();
			break;

		case RQ_ANALOG_WRITE_1:
			rqAnalogWrite1();
			break;

		case RQ_ANALOG_READ:
			rqAnalogRead();
			break;
			
		case RQ_ADC_DAC_STROKE:
			rqAdcDacStroke();
			break;
			
		case RQ_PWM_SET_FREQ:
			rqPwmSetFreq();
			break;
			
		case RQ_PWM_SET_VALUE:
			rqPwmSetValue();
			break;
			
		case RQ_SET_REGISTER:
			rqSetRegister();
			break;
			
		case RQ_GET_REGISTER:
			rqGetRegister();
			break;

		default:
			break;
	}
	
	usart.initRX();
	
	wdt_disable();
}

void rqTestConnection()
{
	usart.initTX();
	uint8_t dummy = usart.readByte();
	usart.writeByte(USART::MSG_OK);
	usart.writeByte(dummy);
	usart.flush();
}

void rqBoardInfo()
{
	usart.initTX();
	usart.writeByte(3); // Anzahl an Strings
	usart.writeStr(DATE, sizeof(DATE));
	usart.writeStr(TIME, sizeof(TIME));
	usart.writeStr(FSRC, sizeof(FSRC));
	usart.writeByte(USART::MSG_OK);
	usart.flush();
}

void rqTestIntConv()
{
	usart.initTX();
	uint16_t d = usart.readInt();
	usart.writeInt(d * 3);
	usart.flush();
}

void rqSelfTest()
{
	usart.initTX();
	usart.writeByte(USART::MSG_OK);
	usart.flush();
	
	wdt_disable();
	
	while(1)
	{
		testAll();
	}
}

void rqDigitalWrite0()
{
	usart.initTX();
	uint8_t port = usart.readByte();
	dio0.writePortA(port);

	usart.writeByte(USART::MSG_OK);
	usart.flush();
}

void rqDigitalWrite1()
{
	usart.initTX();
	uint8_t port = usart.readByte();
	dio1.writePortA(port);

	usart.writeByte(USART::MSG_OK);
	usart.flush();
}

void rqDigitalRead0()
{
	usart.initTX();
	uint8_t port = dio0.readPortB();
	usart.writeByte(port);
	usart.flush();
}

void rqDigitalRead1()
{
	usart.initTX();
	uint8_t port = dio1.readPortB();
	usart.writeByte(port);
	usart.flush();
}

void rqReadDipSwitch()
{
	usart.initTX();
	uint8_t port = dsw.readPortB();
	usart.writeByte(port);
	usart.flush();
}

void rqAnalogWrite0()
{
	usart.initTX();
	uint16_t value = usart.readInt();
	dac0.setValue(value);

	usart.writeByte(USART::MSG_OK);
	usart.flush();
}

void rqAnalogWrite1()
{
	usart.initTX();
	uint16_t value = usart.readInt();
	dac1.setValue(value);

	usart.writeByte(USART::MSG_OK);
	usart.flush();
}

void rqAnalogRead()
{
	usart.initTX();
	uint8_t channel = usart.readByte();
	uint16_t value = adu.getValue(channel);
	usart.writeInt(value);
	usart.flush();
}

void rqAdcDacStroke()
{	
	uint8_t channel_a = usart.readByte();
	uint8_t channel_b = usart.readByte();
	
	int16_t start = static_cast<int16_t>(usart.readInt());
	int16_t delta = static_cast<int16_t>(usart.readInt());
	int16_t count = static_cast<int16_t>(usart.readInt());
	
	count *= delta;
	
	for(int16_t i = start; i < count; i += delta)
	{
		dac0.setValue(i);
		wdt_reset();

		uint16_t val_a = adu.getValue(channel_a);
		uint16_t val_b = adu.getValue(channel_b);
		
		usart.initTX();
		usart.writeInt(val_a);
		usart.writeInt(val_b);
		usart.flush();
	}
	
	usart.initTX();
	usart.writeByte(USART::MSG_OK);
	usart.flush();
}

void rqPwmSetFreq()
{
	usart.initTX();
	uint32_t freq = usart.readU32();
    pwm.setFrequency(freq);

	usart.writeByte(pwm.getTop());
	usart.flush();
}

void rqPwmSetValue()
{
	usart.initTX();
	uint16_t value = usart.readByte();
    pwm.setValue(value);

	usart.writeByte(USART::MSG_OK);
	usart.flush();
}

void rqSetRegister()
{
	usart.initTX();
	uint16_t reg = usart.readByte();
	uint16_t val = usart.readByte();
    
    (*(volatile uint8_t *) reg) = val;
	usart.writeByte((*(volatile uint8_t *) reg));    
	usart.flush();
}

void rqGetRegister()
{
	usart.initTX();
	uint16_t reg = usart.readByte();
    
	usart.writeByte((*(volatile uint8_t *) reg));
	usart.flush();
}

