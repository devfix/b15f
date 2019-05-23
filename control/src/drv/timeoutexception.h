#ifndef TIMEOUTEXCEPTION_H
#define TIMEOUTEXCEPTION_H

#include <exception>

// SOURCE: https://stackoverflow.com/a/8152888

/*! Exception for USART related timeouts. */

class TimeoutException: public std::exception
{
public:
    explicit TimeoutException(const char* message, int timeout) : TimeoutException(std::string(message), timeout)
    {
    }

    explicit TimeoutException(const std::string& message, int timeout) : msg(message), m_timeout(timeout)
    {
        if(!msg.length())
            msg = "Timeout reached (" + std::to_string(m_timeout) + ")";
    }

    virtual ~TimeoutException() throw ()
    {
    }

    virtual const char* what() const throw ()
    {
        return msg.c_str();
    }

protected:
    std::string msg;
    int m_timeout;
};

#endif // TIMEOUTEXCEPTION_H
