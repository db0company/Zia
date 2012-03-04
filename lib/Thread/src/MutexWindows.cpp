#include <Windows.h>
#include "MutexWindows.hpp"

MutexWindows::MutexWindows(void)
{
	InitializeCriticalSection(&(this->_section));
}

MutexWindows::~MutexWindows(void)
{
	DeleteCriticalSection(&(this->_section));
}

MutexWindows::MutexWindows(MutexWindows const &other)
{
  this->_section = other._section;
}

MutexWindows &MutexWindows::operator=(MutexWindows const &other)
{
  this->_section = other._section;
  return (*this);
}


bool MutexWindows::Lock(void)
{
	// todo: can raise an exeption ?
	EnterCriticalSection(&(this->_section));
	return (true);
}

bool MutexWindows::Unlock(void)
{
	LeaveCriticalSection(&(this->_section));
	return (true);
}

bool MutexWindows::Try(void)
{
	if (TryEnterCriticalSection(&(this->_section)) == 0)
	{
		return (false);
	}
	return (true);
}

CRITICAL_SECTION	*MutexWindows::getCS(void)
{
	return (&this->_section);
}