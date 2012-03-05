#ifndef _IMUTEX_HPP__
#define _IMUTEX_HPP__

class IMutex
{
public:
	virtual bool Lock(void) = 0;
	virtual bool Unlock(void) = 0;
	virtual bool Try(void) = 0;
};

#endif //_IMUTEX_HPP__
