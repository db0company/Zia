#ifndef _THREAD_WINDOWS_HH_
#define  _THREAD_WINDOWS_HH_

#include <windows.h>
#include "IThread.hpp"

class ThreadWindows : public IThread
{
public:
  ThreadWindows(void);
  ThreadWindows(ThreadWindows const &);
  ThreadWindows &operator=(ThreadWindows const &);
  virtual ~ThreadWindows(void);
  virtual bool Create(IExec *data);
  virtual bool operator()(IExec *data);
  virtual bool Destroy(void);
  virtual bool Wait(void);
  virtual eThreadState getState(void) const;

private:
  DWORD _threadId;
  HANDLE _handle;
  eThreadState _state;
};

#endif //_THREAD_WINDOWS_HH_
