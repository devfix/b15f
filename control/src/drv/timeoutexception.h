#ifndef TIMEOUTEXCEPTION_H
#define TIMEOUTEXCEPTION_H

#include <exception>
#include <string>

/*! Exception for USART related timeouts. */

class TimeoutException: public std::exception
{
public:
    /**
     * Constructor
     * @param message as c-string
     */
    explicit TimeoutException(const char* message) : msg_(message)
    {
    }

    /**
     * Constructor
     * @param message as c++-string
     */
    explicit TimeoutException(const std::string& message) : msg_(message)
    {
    }

    /**
     * Standard-destructor
     */
    virtual ~TimeoutException() = default;

    /**
     * Get failure description
     * @return error message as c-string
     */
    virtual const char* what() const throw ()
    {
        return msg_.c_str();
    }

protected:
    std::string msg_; //!< failure description
};

#endif // TIMEOUTEXCEPTION_H
