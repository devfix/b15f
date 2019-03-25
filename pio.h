/***
 *     _______  _____   ___    
 *    |_   __ \|_   _|.'   `.  
 *      | |__) | | | /  .-.  \ 
 *      |  ___/  | | | |   | | 
 *     _| |_    _| |_\  `-'  / 
 *    |_____|  |_____|`.___.'  
 * 
 *    Preprocessor I/O Library
 *
 *    ~ version 1.0.0
 *    ~ written by Tristan Krause
 *    ~ visit www.devfix.net
 * 
 *    You should have received a copy of the MIT License.
 *    If not, see <https://opensource.org/licenses/MIT>.
 * 
 *    How does it work?
 *    ----------------------------------------------
 *    Instead of the classical way
 *    (1a)   DDRA |= (1<<PA0);
 *    you can now write
 *    (1b)   dMode(A0, OUT);
 * 
 *    It gets directly replaced by the fast
 *    PORT manipulation command (1a) using
 *    preprocessor macros. This way, PIO
 *    does not increase the overall memory
 *    consumption or slow down the execution
 *    like Arduino does.
 * 
 *    Why using PIO? The Port commands are enough...
 *    ----------------------------------------------
 *    First, the code gets a bit more readable,
 *    especially for beginners.
 *    Second, you can define pins regardless
 *    their corresponding port, resulting in
 *    a more flexible code. For instance:
 *    (2a)   #define LED A0
 *           dMode(LED, OUT);
 *           dWrite(LED, HIGH);
 *    If you now choose another pin, the rest
 *    of the code can stay the same and PIO
 *    will take care of the right PORT commands.
 *    (2b)   #define LED D6     // this changed
 *           dMode(LED, OUT);   // same command
 *           dWrite(LED, HIGH); // same command
 *                             
 */

#ifndef PIO_H
#define PIO_H

// current version
#define PIOLIB 100

#include <avr/io.h>

#ifdef HIGH
#undef HIGH
#endif
#define HIGH 1

#ifndef LOW
#undef LOW
#endif
#define LOW  0

#ifndef OUT
#undef OUT
#endif
#define OUT 1

#ifndef OUTPUT
#undef OUTPUT
#endif
#define OUTPUT 1

#ifndef IN
#undef IN
#endif
#define IN 0

#ifndef INPUT
#undef INPUT
#endif
#define INPUT 0

#include "pio/dmode.h"
#include "pio/dwrite.h"
#include "pio/dread.h"

#include "pio/mcus.h"

#endif // PIO_H
