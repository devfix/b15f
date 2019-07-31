#ifndef VIEW_MONITOR_H
#define VIEW_MONITOR_H

#include <thread>
#include <chrono>
#include <sstream>
#include <bitset>
#include "view_info.h"
#include "../drv/b15f.h"

/**
 * Klasse für die Anzeige aller analogen & digitalen Eingänge des B15.
 */

class ViewMonitor : public ViewInfo
{

public:
    /**
     * Standard-Konstruktor ohne Argumente
     */
    ViewMonitor(void);

    /**
     * Verarbeitet einen Tastendruck, z.B. Enter = Button angewählt.
     * \param key gedrückte Taste
     * \return Call, der nach dem keypress ausgeführt werden soll
     */
    virtual call_t keypress(int& key) override;

private:
    /**
     * Formatiert einen eingelesen Port-Wert in einen Bitstring und Hexadezimalzahlen.
     * \param b Port-Wert
     * \return formatierter String
     */
    std::string fancyDigitalString(uint8_t& b);
    /**
     * Formatiert einen eingelesen ADC-Wert und zeigt eine Prozentleiste.
     * \param b analoger Wert
     * \return formatierter String
     */
    std::string fancyAnalogString(uint16_t& v);

protected:
    virtual void worker(void); //!< Funktion, die vom Worker-Thread ausgeführt, um die Anzeige zu aktualisieren.
    volatile bool run_worker = true; //!< Legt fest, ob die Schleife im worker() weiterhin fortgeführt werden soll. Bei false bricht die Schleife ab.
    std::thread t_worker; //!< Worker-Thread

};

#endif // VIEW_MONITOR_H
