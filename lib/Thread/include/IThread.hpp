#ifndef _ITHREAD_HPP__
#define _ITHREAD_HPP__

#include "IExec.hpp"

enum eThreadState
{
	ON,
	OFF,
	DEAD
};

class IThread
{
public:
        virtual ~IThread(void){}
        virtual bool Create(IExec *work) = 0;
	virtual bool operator()(IExec *work) = 0;
	virtual bool Destroy(void) = 0;
	virtual bool Wait(void) = 0;
	virtual eThreadState getState(void) const = 0;
};


#endif // _ITHREAD_HPP__
