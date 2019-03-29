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
#include "usart.h"
#include "driverexception.h"
#include "timeoutexception.h"

class B15F
{
private:
	// privater Konstruktor
	B15F(void);
public:
	
	/*************************************
	 * Grundfunktionen des B15F Treibers *
	 *************************************/
	
	/**
	 * Initialisiert und testet die Verbindung zum B15
	 * \throws DriverException
	 */	 
	void init(void);
	
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
	 * Liefert eine Referenz zur aktuellen Treiber-Instanz
	 * @throws DriverException
	 */
	static B15F& getInstance(void);
	
	/**
	 * Führt ein Befehl auf dieser Maschine aus und liefert stdout zurück
	 * \param cmd Der Befehl
	 */
	static std::string exec(std::string cmd);
	
	/*************************************/
	
	/*************************
	 * Steuerbefehle für B15 *
	 *************************/
	 
	/**
	 * Setzt den Wert des digitalen Ausgabeports 0
	 * \param port Wert für gesamten Port
	 * \throws DriverException
	 */
	bool digitalWrite0(uint8_t);
	 
	/**
	 * Setzt den Wert des digitalen Ausgabeports 1
	 * \param port Wert für gesamten Port
	 * \throws DriverException
	 */
	bool digitalWrite1(uint8_t);
	 
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
	 * Setzt den Wert des Digital-Analog-Converters (DAC / DAU) 0
	 * \param port 10-Bit Wert
	 * \throws DriverException
	 */
	bool analogWrite0(uint16_t);
	 
	/**
	 * Setzt den Wert des Digital-Analog-Converters (DAC / DAU) 1
	 * \param port 10-Bit Wert
	 * \throws DriverException
	 */
	bool analogWrite1(uint16_t);
	 
	/**
	 * Liest den Wert des Analog-Digital-Converters (ADC / ADU)
	 * \param channel Kanalwahl von 0 - 7
	 * \throws DriverException
	 */
	uint16_t analogRead(uint8_t channel);
	 
	/**
	 * \brief Komplexe Analoge Sequenz
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
	bool analogSequence(uint8_t channel_a, uint16_t* buffer_a, uint32_t offset_a, uint8_t channel_b, uint16_t* buffer_b, uint32_t offset_b, uint16_t start, int16_t delta, uint16_t count);
	
	/*************************/

private:
	USART usart;

	static B15F* instance;


	// CONSTANTS
	const std::string PRE = "[B15F] ";
	const std::string SERIAL_DEVICE = "/dev/ttyUSB0";
	constexpr static uint8_t  MSG_OK = 0xFF;
	constexpr static uint8_t  MSG_FAIL = 0xFE;
	constexpr static uint16_t RECONNECT_TIMEOUT = 64; // ms
	constexpr static uint8_t  RECONNECT_TRIES = 3;
	constexpr static uint32_t BAUDRATE = 115200;
	
	// REQUESTS
	constexpr static uint8_t RQ_DISC = 0;
	constexpr static uint8_t RQ_TEST = 1;
	constexpr static uint8_t RQ_INFO = 2;
	constexpr static uint8_t RQ_INT  = 3;
	constexpr static uint8_t RQ_BA0  = 5;
	constexpr static uint8_t RQ_BA1  = 6;
	constexpr static uint8_t RQ_BE0  = 7;
	constexpr static uint8_t RQ_BE1  = 8;
	constexpr static uint8_t RQ_AA0  = 9;
	constexpr static uint8_t RQ_AA1  = 10;
	constexpr static uint8_t RQ_ADC  = 11;
	constexpr static uint8_t RQ_ADC_DAC_STROKE  = 12;
};

#endif // B15F_H
