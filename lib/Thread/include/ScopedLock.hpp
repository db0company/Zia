#ifndef SCOPLOCK_HPP_
#define SCOPLOCK_HPP_

#include "IMutex.hpp"

class ScopedLock
{
  IMutex	*_mutex;
public:
  ScopedLock(IMutex *m);
  ~ScopedLock();
};

#endif
