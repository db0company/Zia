#include "ScopedLock.hpp"
#include "IMutex.hpp"

ScopedLock::ScopedLock(IMutex *m)
  : _mutex(m)
{
  _mutex->Lock();
}

ScopedLock::~ScopedLock()
{
  _mutex->Unlock();
}
