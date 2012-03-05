#ifndef _ISELECTOR_HH_
#define _ISELECTOR_HH_

class	ISelector
{
 public:
  virtual bool SNSelect(void) = 0;
  virtual void setTimer(long sec, long usec) = 0;
  virtual long getSec(void) const = 0;
  virtual long getUsec(void) const = 0;
};

#endif //_ISELECTOR_HH_
