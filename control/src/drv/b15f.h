#ifndef B15F_H
#define B15F_H

#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <cstdint>
#include <vector>

#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>

#include "requests.h"
#include "usart.h"
#include "driverexception.h"
#include "timeoutexception.h"

// wichtig für die Register-Zugriffe
#define _AVR_IO_H_ 1 // Erzwinge die Inklusion
#include "/usr/lib/avr/include/avr/sfr_defs.h"
#include "/usr/lib/avr/include/avr/iom1284p.h"

typedef std::function<void(std::exception&)> errorhandler_t;


/*! main driver class */

class B15F
{
public:

    /*************************************
     * Grundfunktionen des B15F Treibers *
     *************************************/

    /**
     * Liefert eine Referenz zur aktuellen Treiber-Instanz, die Verbindung wird gegebenenfalls automatisch hergestellt.
     * @throws DriverException
     */
    static B15F& getInstance(void);

    /**
     * Versucht die Verbindung zum B15 wiederherzustellen
     * \throws DriverException
     */
    void reconnect(void);

    /**
     * Verwirft Daten im USART Puffer auf dieser Maschine und B15
     * \throws DriverException
     */
    void discard(void);

    /**
     * Testet die USART Verbindung auf Funktion
     * \throws DriverException
     */
    bool testConnection(void);

    /**
     * Testet die Integer Konvertierung der USART Verbindung
     * \throws DriverException
     */
    bool testIntConv(void);

    /**
     * Liefert Informationen zur aktuellen Firmware des B15
     * \throws DriverException
     */
    std::vector<std::string> getBoardInfo(void);

    /**
     * Lässt den Treiber für eine angegebene Zeit pausieren
     * \param ms Verzögerung in Millisekunden
     */
    void delay_ms(uint16_t ms);

    /**
     * Lässt den Treiber für eine angegebene Zeit pausieren
     * \param us Verzögerung in Microsekunden
     */
    void delay_us(uint16_t us);

    /**
     * Invertiert das Bitmuster eines Bytes
     * z.B.: 10100001 --> 10000101
     * \param b Byte, das invertiert wird
     */
    void reverse(uint8_t& b);

    /**
     * Führt ein Befehl auf dieser Maschine aus und liefert stdout zurück
     * \param cmd Der Befehl
     */
    static std::string exec(std::string cmd);

    /**
     * Multithread sicherer Abbruch des B15F-Treibers
     * \param msg Beschreibung der Abbruchursache
     */
    static void abort(std::string msg);

    /**
     * Multithread sicherer Abbruch des B15F-Treibers
     * \param ex Exception als Abbruchursache
     */
    static void abort(std::exception& ex);

    /**
     * Setzt eine Fehlerbehandlungsroutine für den Treiberabbruch (abort)
     * \param func Funktion, die Exception als Parameter bekommt
     */
    static void setAbortHandler(errorhandler_t func);

    /*************************************/



    /*************************
     * Steuerbefehle für B15 *
     *************************/

    /**
     * Versetzt das Board in den Selbsttest-Modus
     * WICHTIG: Es darf dabei nichts an den Klemmen angeschlossen sein!
     * \throws DriverException
     */
    void activateSelfTestMode(void);

    /**
     * Setzt den Wert des digitalen Ausgabeports 0
     * \param port Wert für gesamten Port
     * \throws DriverException
     */
    void digitalWrite0(uint8_t);

    /**
     * Setzt den Wert des digitalen Ausgabeports 1
     * \param port Wert für gesamten Port
     * \throws DriverException
     */
    void digitalWrite1(uint8_t);

    /**
     * Liest den Wert des digitalen Eingabeports 0
     * \return Wert für gesamten Port
     * \throws DriverException
     */
    uint8_t digitalRead0(void);

    /**
     * Liest den Wert des digitalen Eingabeports 1
     * \return Wert für gesamten Port
     * \throws DriverException
     */
    uint8_t digitalRead1(void);

    /**
     * Liest den Wert des digitalen Eingabeports, an dem der DIP-switch angeschlossen ist (S7)
     * \return Wert für gesamten Port
     * \throws DriverException
     */
    uint8_t readDipSwitch(void);

    /**
     * Setzt den Wert des Digital-Analog-Converters (DAC / DAU) 0
     * \param port 10-Bit Wert
     * \throws DriverException
     */
    void analogWrite0(uint16_t port);

    /**
     * Setzt den Wert des Digital-Analog-Converters (DAC / DAU) 1
     * \param port 10-Bit Wert
     * \throws DriverException
     */
    void analogWrite1(uint16_t port);

    /**
     * Liest den Wert des Analog-Digital-Converters (ADC / ADU)
     * \param channel Kanalwahl von 0 - 7
     * \throws DriverException
     */
    uint16_t analogRead(uint8_t channel);

    /**
     * DAC 0 wird auf den Startwert gesetzt und dann schrittweise um Delta inkrementiert.
     * Für jeden eingestelleten DAC-Wert werden zwei ADCs (channel_a und channel_b) angesprochen und die Werte übermittelt.
     * Die Werte werden in buffer_a für Kanal a und buffer_b für Kanal b gespeichert.
     * \param channel_a Auswahl des ADC a, von 0 - 7
     * \param buffer_a Speichertort für Werte des Kanals a
     * \param offset_a Anzahl an Werten des Kanals a, die im Speicher übersprungen werden sollen
     * \param channel_b Auswahl des ADC b, von 0 - 7
     * \param buffer_b Speichertort für Werte des Kanals b
     * \param offset_b Anzahl an Werten des Kanals b, die im Speicher übersprungen werden
     * \param start Startwert des DACs
     * \param delta Schrittweite, mit welcher der DAC inkrementiert wird
     * \param count Anzahl an Inkrementierungen
     * \throws DriverException
     */
    void analogSequence(uint8_t channel_a, uint16_t* buffer_a, uint32_t offset_a, uint8_t channel_b, uint16_t* buffer_b, uint32_t offset_b, uint16_t start, int16_t delta, uint16_t count);

    /**
     * Frequenz von PWM an PB4.
     * Setzt die Register so, dass näherungsweise die gewünschte Frequenz erzeugt wird.
     * Ist freq == 0 wird PWM deaktiviert.
     * Standardfrequenz: 31300 (empfohlen, da dann TOP == 255)
     * \param freq PWM Frequenz
     * \return TOP Wert des PWM Value für die gesetzte Frequenz
     * \throws DriverException
     */
    uint8_t pwmSetFrequency(uint32_t freq);

    /**
     * Setzt den PWM Wert an PB4.
     * \param value PWM Wert [0..TOP]
     * \throws DriverException
     */
    void pwmSetValue(uint8_t value);

    /**
     * Setzt direkt den Wert einer MCU Speicherzelle der Größe 8 Bit.
     * Diese kann ein Register oder RAM-Daten sein.
     * *Wichtig:* bei einer falschen Adresse kann das Board 15 ernsthaften Schaden nehmen!
     * \param adr Speicheradresse
     * \param val Neuer Wert für die Zelle
     * \return true, falls Vorgang erfolgreich
     */
    void setMem8(volatile uint8_t* adr, uint8_t val);

    /**
     * Liefert den Wert einer MCU Speicherzelle der Größe 8 Bit.
     * Diese kann ein Register oder RAM-Daten sein.
     * \param adr Speicheradresse
     * \return Wert der Speicherzelle
     */
    uint8_t getMem8(volatile uint8_t* adr);

    /**
     * Setzt direkt den Wert einer MCU Speicherzelle der Größe 16 Bit.
     * Diese kann ein Register oder RAM-Daten sein.
     * *Wichtig:* bei einer falschen Adresse kann das Board 15 ernsthaften Schaden nehmen!
     * \param adr Speicheradresse
     * \param val Neuer Wert für die Zelle
     * \throws DriverException
     */
    void setMem16(volatile uint16_t* adr, uint16_t val);

    /**
     * Liefert den Wert einer MCU Speicherzelle der Größe 16 Bit.
     * Diese kann ein Register oder RAM-Daten sein.
     * \param adr Speicheradresse
     * \return Wert der Speicherzelle
     */
    uint16_t getMem16(volatile uint16_t* adr);

    /**
     * Diese Funktion ist ein Alias für setMem8().
     * *Wichtig:* bei einer falschen Adresse kann das Board 15 ernsthaften Schaden nehmen!
     * \param adr Speicheradresse
     * \param val Neuer Wert für das Register
     * \throws DriverException
     */
    void setRegister(volatile uint8_t* adr, uint8_t val);

    /**
     * Diese Funktion ist ein Alias für getMem8().
     * \param adr Speicheradresse
     * \return Wert des Registers
     */
    uint8_t getRegister(volatile uint8_t* adr);

    /**
     * Liefert die Adresse des ersten Interrupt Counters (BASISR).
     * \return Adresse (in der MCU)
     */
    uint16_t* getInterruptCounterOffset(void);

    /**
     * Aktiviert das Servo Signal an PB2 und Initialisiert es mit 1,5ms Pulselänge.
     * \throws DriverException
     */
    void setServoEnabled(void);

    /**
     * Deaktiviert das Servo Signal an PB2.
     * \throws DriverException
     */
    void setServoDisabled(void);

    /**
     * Setzt die Pulselänge des Servo Signals und damit die Position.
     * \param pos Pulselänge des Signals in Mikrosekunden
     * \throws DriverException
     */
    void setServoPosition(uint16_t pos);

    /*************************/


    // CONSTANTS
    const std::string PRE = "[B15F] "; //!< B15F stdout prefix
    constexpr static uint8_t  MSG_OK = 0xFF; //!< Value to acknowledge a received command
    constexpr static uint8_t  MSG_FAIL = 0xFE; //!< Value to reject a received command
    constexpr static uint16_t RECONNECT_TIMEOUT = 64; //!< Time in ms after which a reconnect attempt aborts
    constexpr static uint16_t WDT_TIMEOUT = 15; //!< Time in ms after which the watch dog timer resets the MCU
    constexpr static uint8_t  RECONNECT_TRIES = 3; //!< Maximum count of reconnect attempts after which the driver stops
    constexpr static uint32_t BAUDRATE = 57600; //!< USART baudrate for communication with the MCU

private:

    /**
     * Privater Konstruktor
     */
    B15F(void);

    /**
     * Initialisiert und testet die Verbindung zum B15
     * \throws DriverException
     */
    void init(void);

    /**
     * Wirft eine Exception, falls der Code ungleich dem erwarteten Wert ist.
     * \throws DriverException
     */
    template<typename CodeType, typename ExpectationType>
    void assertCode(CodeType& code, ExpectationType expectation) const
    {
        if(code != static_cast<CodeType>(expectation))
            throw DriverException("Ungültige Antwort erhalten: " + std::to_string((int) code) + " (erwartet: " + std::to_string((int) expectation) + ")");
    }

    /**
     * Wirft eine Exception, falls die Request die falsche Länge hat.
     * \throws DriverException
     */
    template<size_t RequestLength>
    void assertRequestLength(uint8_t (&)[RequestLength], uint8_t rq_num)
    {
        if(RequestLength != rq_len[rq_num])
            throw DriverException("Ungültige Request Länge: " + std::to_string(RequestLength) + " (erwartet: " + std::to_string(rq_len[rq_num]) + ")");
    }

    USART usart; //!< USART Instanz für serielle Verbindung
    static B15F* instance; //!< private Instanz für Singleton
    static errorhandler_t errorhandler; //!< Error Handler für Exceptions und Fehler
};

#endif // B15F_H
