#include "ThreadWindows.hpp"

static void *RunThread(void *data)
{
  IExec *ex = reinterpret_cast<IExec *>(data);
  ex->RunExec();
  return (NULL);
}

ThreadWindows::ThreadWindows(void): _state(OFF)
{
}

ThreadWindows::~ThreadWindows(void)
{
}

ThreadWindows::ThreadWindows(ThreadWindows const &other)
{
  this->_threadId = other._threadId;
  this->_handle = other._handle;
  this->_state = other._state;
}

ThreadWindows &ThreadWindows::operator=(ThreadWindows const &other)
{
  this->_threadId = other._threadId;
  this->_handle = other._handle;
  this->_state = other._state;
  return (*this);
}

bool ThreadWindows::Create(IExec *data)
{
  this->_handle = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(&RunThread), reinterpret_cast<void *>(data), 0, &(this->_threadId));
  if (this->_handle == NULL)
    {
      return (false);
    }
  this->_state = ON;
  return (true);
}

bool ThreadWindows::operator()(IExec *data)
{
  this->_handle = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(&RunThread), reinterpret_cast<void *>(data), 0, &(this->_threadId));
  if (this->_handle == NULL)
    {
      return (false);
    }
  this->_state = ON;
  return (true);
}

bool ThreadWindows::Destroy(void)
{
	if (CloseHandle(this->_handle) == 0)
	{
		return (false);
	}
	return (true);
}

bool ThreadWindows::Wait(void)
{
	if (WaitForMultipleObjects(1, &(this->_handle), TRUE, INFINITE) == WAIT_FAILED)
	{
		return (false);
	}
	this->_state = DEAD;
	return (true);
}

eThreadState ThreadWindows::getState() const
{
	return (this->_state);
}
