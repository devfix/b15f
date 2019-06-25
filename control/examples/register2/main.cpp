#include <b15f/b15f.h>
#include <b15f/plottyfile.h>

/*
 * Dieses Beispiel liest ein par Interrupt Counter aus.
 * Die Counter sind 16-Bit groß und in einem Feld.
 * Die Vector Nummer ist gleich die Counter-Nummer im Feld.
 * Ausname: Vector 0 (Reset). Dieser ist im Feld stattdessen der BADISR-Interrupt
 */
int main()
{
    uint8_t tmp;
	B15F& drv = B15F::getInstance();
    
    // INT2 für falling edge
    tmp = drv.getRegister(&EICRA);
    tmp |= _BV(ISC21);
    drv.setRegister(&EICRA, tmp);
    
    // aktiviere INT2
    tmp = drv.getRegister(&EIMSK);
    tmp |= _BV(INT2);
    drv.setRegister(&EIMSK, tmp);
    
    // ab jetzt sollte kann man INT2 mit einem Pullup/Pulldown Widerstand betreiben.
    // Nachdem man eine Flanke auf INT2 gegeben hat und dieses Programm erneut aufruft, siehtman wie counter[INT2] hochzählt.
    
    // Erhalte Adress-Offset zum ersten Counter.
    uint16_t* cnt = drv.getInterruptCounterOffset();
    std::cout << "mem offset: " << reinterpret_cast<size_t>(cnt) << std::endl;
    
    // gib beispielhaft ein par Counter aus:
    std::cout << "counter[BADISR]: " << (int) drv.getMem16(cnt) << std::endl;
    std::cout << "counter[INT0]: " << (int) drv.getMem16(cnt + 1) << std::endl;
    std::cout << "counter[INT1]: " << (int) drv.getMem16(cnt + 2) << std::endl;
    std::cout << "counter[INT2]: " << (int) drv.getMem16(cnt + 3) << std::endl;
    std::cout << "counter[ANALOG_COMP]: " << (int) drv.getMem16(cnt + 23) << std::endl;
    std::cout << "counter[TIMER3_OVF]: " << (int) drv.getMem16(cnt + 34) << std::endl;
    
}
