#ifndef _NON_COPY
#define _NON_COPY
class NonCopyable
{
protected:
	NonCopyable() {}
	~NonCopyable() {}
private:
#ifndef __EMSCRIPTEN__
	NonCopyable(const NonCopyable &);
	NonCopyable& operator=(const NonCopyable &);
#endif
}; 
#endif