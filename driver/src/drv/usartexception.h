#ifndef USARTEXCEPTION_H
#define USARTEXCEPTION_H

#include <exception>
#include <string>

// SOURCE: https://stackoverflow.com/a/8152888

class USARTException: public std::exception
{
public:
	explicit USARTException(const char* message) : msg(message)
	{
      	}

	explicit USARTException(const std::string& message) : msg(message)
	{
	}

    	virtual ~USARTException() throw ()
	{
	}

	virtual const char* what() const throw ()
	{
		return msg.c_str();
	}

protected:
	std::string msg;
};

#endif // USARTEXCEPTION_H
