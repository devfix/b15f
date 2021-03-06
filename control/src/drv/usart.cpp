#include <stdexcept>
#include "usart.h"

USART::~USART()
{
    closeDevice();
}

void USART::openDevice(std::string device)
{
    // Benutze blockierenden Modus
    file_desc = open(device.c_str(), O_RDWR | O_NOCTTY);// | O_NDELAY
    if (file_desc <= 0)
        throw USARTException("Fehler beim Öffnen des Gerätes");

    struct termios options;
    int code = tcgetattr(file_desc, &options);
    if (code)
        throw USARTException("Fehler beim Lesen der Geräteparameter");

    options.c_cflag = CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    options.c_cc[VMIN] = 0;
    options.c_cc[VTIME] = timeout;
    code = cfsetspeed(&options, baudrate);
    if (code)
        throw USARTException("Fehler beim Setzen der Baudrate");

    code = tcsetattr(file_desc, TCSANOW, &options);
    if (code)
        throw USARTException("Fehler beim Setzen der Geräteparameter");

    code = fcntl(file_desc, F_SETFL, 0); // blockierender Modus
    if (code)
        throw USARTException("Fehler beim Aktivieren des blockierenden Modus'");

    clearOutputBuffer();
    clearInputBuffer();
}

void USART::closeDevice()
{
    if (file_desc > 0)
    {
        int code = close(file_desc);
        if (code)
            throw USARTException("Fehler beim Schließen des Gerätes");
        file_desc = -1;
    }
}

void USART::clearInputBuffer()
{
    int code = tcflush(file_desc, TCIFLUSH);
    if (code)
        throw USARTException("Fehler beim Leeren des Eingangspuffers");
}

void USART::clearOutputBuffer()
{
    int code = tcflush(file_desc, TCOFLUSH);
    if (code)
        throw USARTException("Fehler beim Leeren des Ausgangspuffers");
}

void USART::flushOutputBuffer()
{
    int code = tcdrain(file_desc);
    if (code)
        throw USARTException("Fehler beim Versenden des Ausgangspuffers");
}

void USART::transmit(uint8_t *buffer, uint16_t offset, uint8_t len)
{
    int code = write(file_desc, buffer + offset, len);
    if (code != len)
        throw USARTException(
            std::string(__FUNCTION__) + " failed: " + std::string(__FILE__) + "#" + std::to_string(__LINE__) +
            ", " + strerror(code) + " (code " + std::to_string(code) + " / " + std::to_string(len) + ")");
}

void USART::receive(uint8_t *buffer, uint16_t offset, uint8_t len)
{
    int bytes_avail, code;
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    do
    {
        code = ioctl(file_desc, FIONREAD, &bytes_avail);
        if (code)
            throw USARTException(
                std::string(__FUNCTION__) + " failed: " + std::string(__FILE__) + "#" + std::to_string(__LINE__) +
                ", " + strerror(code) + " (code " + std::to_string(code) + ")");

        end = std::chrono::steady_clock::now();
        long elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 100; // in Dezisekunden
        if (elapsed >= timeout)
            throw TimeoutException(
                std::string(__FUNCTION__) + " failed: " + std::string(__FILE__) + "#" + std::to_string(__LINE__) +
                ", " + std::to_string(elapsed) + " / " + std::to_string(timeout) + " ds");
    }
    while (bytes_avail < len);

    code = read(file_desc, buffer + offset, len);
    if (code != len)
        throw USARTException(
            std::string(__FUNCTION__) + " failed: " + std::string(__FILE__) + "#" + std::to_string(__LINE__) +
            ", " + strerror(code) + " (code " + std::to_string(code) + " / " + std::to_string(len) + ")");
}

void USART::drop(uint8_t len)
{
    // Kann bestimmt noch eleganter gelöst werden
    uint8_t dummy[len];
    receive(&dummy[0], 0, len);
}

uint32_t USART::getBaudrate()
{
    return baudrate;
}

uint8_t USART::getTimeout()
{
    return timeout;
}

void USART::setBaudrate(uint32_t baudrate)
{
    this->baudrate = baudrate;
}

void USART::setTimeout(uint8_t timeout)
{
    this->timeout = timeout;
}
