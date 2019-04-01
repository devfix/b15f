#ifndef TIMEOUTEXCEPTION_H
#define TIMEOUTEXCEPTION_H

#include <exception>

// SOURCE: https://stackoverflow.com/a/8152888

class TimeoutException: public std::exception
{
public:
	explicit TimeoutException(const char* message, int timeout) : TimeoutException(std::string(message), timeout)
	{
      	}

	explicit TimeoutException(const std::string& message, int timeout) : msg(message), timeout(timeout)
	{		
		if(!msg.length())
			msg = "Timeout reached (" + std::to_string(timeout) + ")";
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
	int timeout;
};

#endif // TIMEOUTEXCEPTION_H
