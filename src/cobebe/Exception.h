#ifndef _COBEBE_EXCEPTION
#define _COBEBE_EXCEPTION
#include <exception>
#include <string>

struct Exception : public std::exception
{
public:
	Exception(const std::string& message);
	virtual ~Exception() throw() {}
	virtual const char* what() const throw();

private:
	std::string m_message;

};

#endif
