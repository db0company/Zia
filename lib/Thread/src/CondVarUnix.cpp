
#include "IMutex.hpp"
#include "MutexUnix.hpp"
#include "CondVarUnix.hpp"


CondVarUnix::CondVarUnix()
{
  pthread_cond_init(&this->_Cond, NULL);
}

CondVarUnix::~CondVarUnix()
{
  int	ret;
  //  CriticalError	e("Cond error : Some thread are waiting this cond, you can't destroy it");

  ret = pthread_cond_destroy(&this->_Cond);
  if (ret != 0)
    {
      this->broadcast();
      // throw e;
    }
}

bool	CondVarUnix::wait()
{
  if (pthread_cond_wait(&this->_Cond, _m.getMutex()) == 0)
	  return (true);
  return (false);
}

void	CondVarUnix::signal()
{
  pthread_cond_signal(&this->_Cond);
}

void	CondVarUnix::broadcast()
{
  pthread_cond_broadcast(&this->_Cond);
}
