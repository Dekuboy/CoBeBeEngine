#ifndef _NON_COPY
#define _NON_COPY
class NonCopyable
{
protected:
	NonCopyable() {}
	~NonCopyable() {}
private:
	NonCopyable(const NonCopyable &);
	NonCopyable& operator=(const NonCopyable &);
}; 
#endif