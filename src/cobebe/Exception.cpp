#include "Exception.h"
#include <iostream>

Exception::Exception(const std::string& message)
{
	m_message = message;
}

const char* Exception::what() const throw()
{
	return m_message.c_str();
}
