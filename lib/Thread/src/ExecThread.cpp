#include "ExecThread.hpp"
#include "ThreadData.hpp"
#include "PacketTask.hpp"
template <typename T>
ExecThread<T>::ExecThread(T p)
  :param(p)
{
}

template <typename T>
ExecThread<T>::ExecThread(ExecThread<T>& old)
  :param(old.param)
{
}

template <typename T>
ExecThread<T>::~ExecThread()
{
}


template <typename T>
void ExecThread<T>::RunExec(void)
{
  param->ExecParam();
}


template <typename T>
ExecThread<T> &ExecThread<T>::operator=(ExecThread<T>& old)
{
  this->param = old.param;
  return (*this);
}


template class ExecThread<IThreadData *>;
