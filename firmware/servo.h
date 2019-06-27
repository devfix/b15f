#ifndef SERVO_H
#define SERVO_H

#include <avr/io.h>

class Servo
{
public:
    
    /**
     * Aktiviert das Servo Signal
     */
    void enable(void) volatile;
    
    /**
     * Deaktiviert das Servo Signal
     */
    void disable(void) const volatile;
    
    /**
     * Setzt die Pulselänge und damit die Servo Position
     */
    void setPosition(uint16_t pos) const volatile;
    
    /**
     * Beendet den aktuellen Impuls. Wird von der zugehörigen Interrupt-Routine aufgerufen.
     */
    void handleTimer1(void) const volatile;
    
    /**
     * Inkrementiert die Frequenzsteuerung und löst gegebenenfalls einen neuen Impuls aus.
     */
    void handleTimer2(void) volatile;
    
private:
    uint8_t repetition_counter;
    static constexpr uint8_t PRESCALER_IMPULSE = _BV(CS11); // prescaler 8
};

#endif // SERVO_H
