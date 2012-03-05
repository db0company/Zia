#ifndef __MUTEX_WINDOWS_HPP__
#define __MUTEX_WINDOWS_HPP__


#include <Windows.h>
#include "IMutex.hpp"

class MutexWindows : public IMutex
{
public:
  MutexWindows(void);
  MutexWindows(MutexWindows const &);
  MutexWindows &operator=(MutexWindows const &);
  virtual ~MutexWindows(void);
  virtual bool Lock(void);
  virtual bool Unlock(void);
  virtual bool Try(void);
  CRITICAL_SECTION	*getCS();
private:
  CRITICAL_SECTION _section;
};

#endif // __MUTEX_WINDOWS_HPP__
