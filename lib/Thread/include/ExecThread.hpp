#include "IExec.hpp"

template <typename T>
class ExecThread : public IExec
{
private:
  T param;
public:
  ExecThread(T p);
  ExecThread(ExecThread&);
  ~ExecThread();
  ExecThread &operator=(ExecThread&);
  void RunExec(void);
};
