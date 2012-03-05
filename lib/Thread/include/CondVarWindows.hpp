#ifndef _CONDVAR_WINDOWS_HPP
#define _CONDVAR_WINDOWS_HPP

#include "ICondvar.hpp"
#include "MutexWindows.hpp"

class CondVarWindows : public ICondVar
{
public:
  CondVarWindows();
  ~CondVarWindows(void);
  CondVarWindows(CondVarWindows const &);
  CondVarWindows &operator=(CondVarWindows const &);
  virtual bool	wait();
  virtual void	signal();
  virtual void	broadcast();
private:
  CONDITION_VARIABLE _condvar;
  MutexWindows	   _m;
};

#endif //_CONDVAR_WINDOWS_HPP
