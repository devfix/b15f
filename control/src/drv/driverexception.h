#ifndef DRIVEREXCEPTION_H
#define DRIVEREXCEPTION_H

#include <exception>

// SOURCE: https://stackoverflow.com/a/8152888

/*! Exception driver problems, for instance incompatible firmware version. */

class DriverException: public std::exception
{
public:
    explicit DriverException(const char* message) : msg_(message)
    {
    }

    explicit DriverException(const std::string& message) : msg_(message)
    {
    }

    virtual ~DriverException() throw ()
    {
    }

    virtual const char* what() const throw ()
    {
        return msg_.c_str();
    }

protected:
    std::string msg_;
};

#endif // DRIVEREXCEPTION_H

