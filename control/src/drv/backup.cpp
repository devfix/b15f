
void USART::writeByte(uint8_t b)
{
    int sent = write(file_desc, &b, 1);
    if (sent != 1)
    {
        std::cout << "WARNUNG: Fehler beim Senden (" << sent << "): writeByte(), wiederhole..." << std::endl;
        usleep(100000);
        sent = write(file_desc, &b, 1);
        if (sent != 1)
            throw USARTException("Fehler beim Senden: writeByte()");
    }

}

void USART::writeInt(uint16_t d)
{
    int sent = write(file_desc, reinterpret_cast<char *>(&d), 2);
    if (sent != 2)
        throw USARTException("Fehler beim Senden: writeInt()");
}

void USART::writeU32(uint32_t w)
{
    int sent = write(file_desc, reinterpret_cast<char *>(&w), 4);
    if (sent != 4)
        throw USARTException("Fehler beim Senden: writeU32()");
}

uint8_t USART::readByte(void)
{
    char b;
    auto start = std::chrono::steady_clock::now();
    auto end = start;
    uint16_t elapsed = 0;
    while (elapsed < timeout * 100)
    {
        int code = read(file_desc, &b, 1);
        if (code > 0)
            return static_cast<uint8_t>(b);

        end = std::chrono::steady_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    throw TimeoutException("Verbindung unterbrochen.", timeout);
}

uint16_t USART::readInt(void)
{
    return readByte() | readByte() << 8;
}
