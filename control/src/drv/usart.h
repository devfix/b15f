#ifndef USART_H
#define USART_H

#include <cstdint>
#include <chrono>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <string.h>
#include "usartexception.h"
#include "timeoutexception.h"

/*! C++ Wrapper class for termios usart library. */

class USART
{
public:

    /*************************************************
     * Methoden für die Verwaltung der Schnittstelle *
     *************************************************/

    /**
     * Standard-Konstruktor
     */
    explicit USART() = default;

    /**
     * Destructor, ruft automatisch closeDevice() auf
     */
    virtual ~USART(void);

    /**
     * Öffnet die USART Schnittstelle
     * \param device Linux-Gerätepfad
     * \throws USARTException
     */
    void openDevice(std::string device);

    /**
     * Schließt die USART Schnittstelle
     * \throws USARTException
     */
    void closeDevice(void);

    /**
     * Verwirft Daten, die bereits im Puffer liegen, aber noch nicht gelesen wurden
     * \throws USARTException
     */
    void clearInputBuffer(void);

    /**
     * Verwirft Daten, die bereits im Puffer liegen, aber noch nicht gesendet wurden
     * \throws USARTException
     */
    void clearOutputBuffer(void);

    /**
     * Schreibt Daten, die bereits im Puffer liegen, aber noch nicht gesendet wurden
     * \throws USARTException
     */
    void flushOutputBuffer(void);

    /*************************************************/



    /*************************************
     * Methoden für die Datenübertragung *
     *************************************/

    /**
     * Sends n bytes from the buffer over USART
     * \param buffer target buffer
     * \param offset in buffer (mostly 0)
     * \param len count of bytes to send
     * \throws USARTException
     */
    void transmit(uint8_t *buffer, uint16_t offset, uint8_t len);

    /**
     * Receives n bytes from USART and writes them into the buffer
     * \param buffer target buffer
     * \param offset in buffer (mostly 0)
     * \param len count of bytes to receive
     * \throws USARTException
     */
    void receive(uint8_t *buffer, uint16_t offset, uint8_t len);

    /*************************************/



    /***************************************
     * Methoden für einstellbare Parameter *
     ***************************************/

    /**
     * Liefert die eingestellte Baudrate
     * <b>Änderungen werden erst nach einem open() wirksam</b>
     */
    uint32_t getBaudrate(void);

    /**
     * Liefert den eingestellten Timeout (in Dezisekunden)
     * <b>Änderungen werden erst nach einem open() wirksam</b>
     */
    uint8_t getTimeout(void);

    /**
     * Setzt die Baudrate
     * <b>Änderungen werden erst nach openDevice() wirksam</b>
     */
    void setBaudrate(uint32_t baudrate);

    /**
     * Setzt den Timeout (in Dezisekunden)
     * <b>Änderungen werden erst nach openDevice() wirksam</b>
     */
    void setTimeout(uint8_t timeout);

    /***************************************/

private:

    int file_desc = -1; //!< Linux Dateideskriptor
    uint32_t baudrate = 9600; //!< Standard-Baudrate, sollte mit setBaudrate() überschrieben werden!
    uint8_t timeout = 10; //!< in Dezisekunden
};

#endif // USART_H
