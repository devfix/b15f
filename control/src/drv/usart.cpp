#include "usart.h"

USART::~USART() {
    closeDevice();
}

void USART::openDevice(std::string device) {
    // Benutze blockierenden Modus
    file_desc = open(device.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
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
    options.c_cc[VMIN] = 0; // #bytes read returns at least
    options.c_cc[VTIME] = timeout;
    code = cfsetspeed(&options, baudrate);
    if (code)
        throw USARTException("Fehler beim Setzen der Baudrate");

    code = tcsetattr(file_desc, TCSANOW, &options);
    if (code)
        throw USARTException("Fehler beim Setzen der Geräteparameter");

    clearOutputBuffer();
    clearInputBuffer();
}

void USART::closeDevice() {
    if (file_desc > 0) {
        int code = close(file_desc);
        if (code)
            throw USARTException("Fehler beim Schließen des Gerätes");
        file_desc = -1;
    }
}

void USART::clearInputBuffer() {
    int code = tcflush(file_desc, TCIFLUSH);
    if (code)
        throw USARTException("Fehler beim Leeren des Eingangspuffers");
}

void USART::clearOutputBuffer() {
    int code = tcflush(file_desc, TCOFLUSH);
    if (code)
        throw USARTException("Fehler beim Leeren des Ausgangspuffers");
}

void USART::flushOutputBuffer() {
    int code = tcdrain(file_desc);
    if (code)
        throw USARTException("Fehler beim Versenden des Ausgangspuffers");
}

void USART::writeByte(uint8_t b) {
    int sent = write(file_desc, &b, 1);
    if (sent != 1) {
        std::cout << "WARNUNG: Fehler beim Senden (" << sent << "): writeByte(), wiederhole..." << std::endl;
        usleep(100000);
        sent = write(file_desc, &b, 1);
        if (sent != 1)
            throw USARTException("Fehler beim Senden: writeByte()");
    }

}

void USART::writeInt(uint16_t d) {
    int sent = write(file_desc, reinterpret_cast<char *>(&d), 2);
    if (sent != 2)
        throw USARTException("Fehler beim Senden: writeInt()");
}

void USART::writeU32(uint32_t w) {
    int sent = write(file_desc, reinterpret_cast<char *>(&w), 4);
    if (sent != 4)
        throw USARTException("Fehler beim Senden: writeU32()");
}

void USART::receive(uint8_t *buffer, uint16_t offset, uint8_t len) {
    int n = read(file_desc, buffer + offset, len);
    if (n != len)
        throw USARTException(
                std::string(__FUNCTION__) + " failed: " + std::string(__FILE__) + "#" + std::to_string(__LINE__));
}

void USART::transmit(uint8_t *buffer, uint16_t offset, uint8_t len) {
    int n = write(file_desc, buffer + offset, len);
    if (n != len)
        throw USARTException(
                std::string(__FUNCTION__) + " failed: " + std::string(__FILE__) + "#" + std::to_string(__LINE__));
}

uint8_t USART::readByte(void) {
    char b;
    auto start = std::chrono::steady_clock::now();
    auto end = start;
    uint16_t elapsed = 0;
    while (elapsed < timeout * 100) {
        int code = read(file_desc, &b, 1);
        if (code > 0)
            return static_cast<uint8_t>(b);

        end = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    throw TimeoutException("Verbindung unterbrochen.", timeout);
}

uint16_t USART::readInt(void) {
    return readByte() | readByte() << 8;
}

uint32_t USART::getBaudrate() {
    return baudrate;
}

uint8_t USART::getTimeout() {
    return timeout;
}

void USART::setBaudrate(uint32_t baudrate) {
    this->baudrate = baudrate;
}

void USART::setTimeout(uint8_t timeout) {
    this->timeout = timeout;
}
