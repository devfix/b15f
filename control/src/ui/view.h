#ifndef VIEW_H
#define VIEW_H

#include <iostream>
#include <cmath>
#include <vector>
#include <functional>
#include <ncurses.h> // sudo apt-get install libncurses5-dev
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#include "../drv/b15f.h"

extern std::string ERR_MSG;
typedef std::function<void(int)> call_t;

/*! Base class for multiple views with the ncurses user interface. */

class View
{
public:
    /**
     * standard constructor, takes no args
     */
    View(void);

    /**
     * standard destructor
     */
    virtual ~View(void);

    /**
     * Sets static view context, used for every view
     * Note: this UI systems supports only one window
     * \param win window context
     */
    static void setWinContext(WINDOW* win);

    /**
     * \return static window context for all views
     */
    static WINDOW* getWinContext(void);

    /**
     * Splits a string by a delimeter and returns the parts in a vector
     * \param str input string
     * \param delim the delimeter for splitting
     * \return splitted parts of str
     */
    static std::vector<std::string> str_split(const std::string& str, const std::string delim);

    /**
     * Sets the title of this view
     * \param title string to set title
     */
    virtual void setTitle(std::string title);

    /**
     * Repaints the whole window with the current view.
     * The centered position of the window in the terminal gets new calculated.
     * The window box gets repainted.
     */
    virtual void repaint(void);

    /**
     * Abstract function for drawing ths particular view.
     * Gets overridden in the derived classes to paints for example a promt.
     */
    virtual void draw(void) = 0;

    /**
     * Abstract function for the view to reacted on a keypress.
     * Gets overridden in the derived classes to close for example a view on ESC.
     */
    virtual call_t keypress(int& key) = 0;


protected:
    int width; //!< width of view in terminal characters
    int height; //!< height of view in terminal characters
    int start_x = 0; //!< x offset (characters) in the terminal, used to center the window on repaint()
    int start_y = 0; //!< y offset (characters) in the terminal, used to center the window on repaint()
    std::string title; //!< title of the view
    std::vector<call_t> calls; //!< calls (function pointers) for different button actions in the view (if any)

    static WINDOW* win; //!< static window contexts for all views
    constexpr static int KEY_ENT = 10; //!< Key value for the Enter key
};

#endif // VIEW_H
