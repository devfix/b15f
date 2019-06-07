#ifndef USARTEXCEPTION_H
#define USARTEXCEPTION_H

#include <exception>
#include <string>

/*! Exception for USART problems, for instance buffer overflow. */

class USARTException: public std::exception
{
public:
    /**
     * Constructor
     * @param message as c-string
     */
    explicit USARTException(const char* message) : msg(message)
    {
    }

    /**
     * Constructor
     * @param message as c++-string
     */
    explicit USARTException(const std::string& message) : msg(message)
    {
    }

    /**
     * Standard-destructor
     */
    virtual ~USARTException() = default;

    /**
     * Get failure description
     * @return error message as c-string
     */
    virtual const char* what() const throw ()
    {
        return msg.c_str();
    }

protected:
    std::string msg; //!< failure description
};

#endif // USARTEXCEPTION_H
