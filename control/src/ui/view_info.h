#ifndef VIEW_INFO
#define VIEW_INFO

#include "view.h"

/**
 * Klasse für einfache Textausgaben (Benachrichtigungen).
 * Diese können mit einem Button geschlossen werden.
 */

class ViewInfo : public View
{
public:
    /**
     * Standard-Konstruktor ohne Argumente
     */
    ViewInfo(void);

    /**
     * Setzt den Text dieser Benachrichtigungs-View
     * \param text Text der View
     */
    virtual void setText(std::string text);

    /**
     * Setzt die Beschriftung des Buttons zum Schließen
     * \param label Beschriftung des Buttons
     */
    virtual void setLabelClose(std::string label);

    /**
     * Setzt den Call der aufgerufen wird, wenn der Button angewählt wird.
     * Wurde setCall weggelassen oder setCall(nullptr) gesetzt, wird diese View nur geschlossen und keine weitere Aktion ausgelöst.
     * \param call Nachfolge-Aktion
     */
    virtual void setCall(call_t call);

    /**
     * Zeichnet diese View mit dem Benachrichtigungstext.
     */
    virtual void draw(void) override;

    /**
     * Verarbeitet einen Tastendruck, z.B. Enter = Button angewählt.
     * \param key gedrückte Taste
     * \return Call, der nach dem keypress ausgeführt werden soll
     */
    virtual call_t keypress(int& key) override;

protected:
    std::string text; //!< Benachrichtigungstext dieser View
    std::string label_close; //!< Beschriftung für Button zum Schließen
    int close_offset_x = 0; //!< Relative X Koordinate des Buttons zum Schließen im Window
    int close_offset_y = 0; //!< Relative Y Koordinate des Buttons zum Schließen im Window
    constexpr static int text_offset_x = 2; //!< Relativer Abstand des Textes zum linken Rahmen
    constexpr static int text_offset_y = 3; //!< Relativer Abstand des Textes zum oberen Rahmen
};

#endif // VIEW_INFO
