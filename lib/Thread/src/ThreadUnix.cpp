#include <pthread.h>
#include "ThreadUnix.hpp"

 static void *RunThread(void *data)
 {
   IExec *ex = reinterpret_cast<IExec *>(data);
   ex->RunExec();
   return (NULL);
 }

ThreadUnix::ThreadUnix(void) :
  _state(OFF)
{
}

ThreadUnix::~ThreadUnix(void)
{
}

ThreadUnix &ThreadUnix::operator=(ThreadUnix const &other)
{
  this->_state = other._state;
  this->_thread = other._state;
  return (*this);
}

ThreadUnix::ThreadUnix(ThreadUnix const &other)
{
  this->_state = other._state;
  this->_thread = other._state;
}

bool ThreadUnix::Create(IExec *work)
{
 if (pthread_create(&this->_thread, NULL, &RunThread, reinterpret_cast<void *>(work)) != 0)
    return (false);
  this->_state = ON;
  return (true);
}

bool ThreadUnix::operator()(IExec *work)
{
  if (pthread_create(&this->_thread, NULL, &RunThread, reinterpret_cast<void *>(work)) != 0)
    return (false);
  this->_state = ON;
  return (true);
}

bool ThreadUnix::Destroy(void)
{
  this->_state = OFF; // todo ?
  return (true);
}

bool ThreadUnix::Wait(void)
{
  void *res;

  if (pthread_join(this->_thread, &res) != 0)
    return (false);
  this->_state = DEAD;
  return (false);
}

eThreadState ThreadUnix::getState(void) const
{
  return (this->_state);
}

