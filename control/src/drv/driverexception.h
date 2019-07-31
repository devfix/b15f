#ifndef DRIVEREXCEPTION_H
#define DRIVEREXCEPTION_H

#include <exception>

// SOURCE: https://stackoverflow.com/a/8152888

/*! Exception driver problems, for instance incompatible firmware version. */

class DriverException: public std::exception
{
public:
    /**
     * Constructor
     * @param message as c-string
     */
    explicit DriverException(const char* message) : msg_(message)
    {
    }

    /**
     * Constructor
     * @param message as c++-string
     */
    explicit DriverException(const std::string& message) : msg_(message)
    {
    }

    /**
     * Standard-destructor
     */
    virtual ~DriverException() throw ()
    {
    }

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

#endif // DRIVEREXCEPTION_H

