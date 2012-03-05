#ifndef SELECTOR_H_
# define SELECTOR_H_

#ifdef _WIN32
# include <winsock2.h>
#else
# include <sys/types.h>
# include <unistd.h>
#include <errno.h>
#endif

#include <utility>
#include <list>
#include <map>
#include "ISelector.h"
#include "ISocket.h"

template <typename T>
class	Selector : public ISelector
{
public:
  Selector(void)  : _maxFd(0)
  {
    FD_ZERO(&(this->_readFd));
    FD_ZERO(&(this->_writeFd));
    this->_timeout.tv_sec = 0;
    this->_timeout.tv_usec = 0;
  }
  ~Selector(void) {}

  Selector(const Selector & other)
  {
    this->_readFd = other._readFd;
    this->_writeFd = other._writeFd;
    this->_maxFd = other._maxFd;
    this->_timeout.tv_sec = other._timeout.tv_sec;
    this->_timeout.tv_usec = other._timeout.tv_usec;
  }

  Selector &	operator=(const Selector& other)
  {
    this->_readFd = other._readFd;
    this->_writeFd = other._writeFd;
    this->_maxFd = other._maxFd;
    this->_timeout.tv_sec = other._timeout.tv_sec;
    this->_timeout.tv_usec = other._timeout.tv_usec;
    return (*this);
  }

  virtual bool SNSelect(void)
  {
    typename std::map<T, ISocket *>::iterator it;

    FD_ZERO(&(this->_readFd));
    FD_ZERO(&(this->_writeFd));
    for (it = this->_readMap.begin(); it != this->_readMap.end(); ++it)
      {
	if (!FD_ISSET((*it).first, &(this->_readFd)))
	  FD_SET((*it).first, &(this->_readFd));
      }
    for (it = this->_writeMap.begin(); it != this->_writeMap.end(); ++it)
      {
	if (!FD_ISSET((*it).first, &(this->_writeFd)))
	  FD_SET((*it).first, &(this->_writeFd));
      }
    if (select(this->_maxFd + 1, &(this->_readFd), &(this->_writeFd),
	       NULL, &(this->_timeout)) == -1)
      {
#ifdef _WIN32
		std::cout << "Fail Error S: " << WSAGetLastError() << std::endl;
#endif
	return (false);
      }
    for (it = this->_writeMap.begin(); it != this->_writeMap.end(); ++it)
      {
	if (FD_ISSET((*it).first, &(this->_writeFd)))
	  (*it).second->SNSetWrite(true);
	else
	  (*it).second->SNSetWrite(false);
      }
    for (it = this->_readMap.begin(); it != this->_readMap.end(); ++it)
      {
	if (FD_ISSET((*it).first, &(this->_readFd)))
	  (*it).second->SNSetRead(true);
	else
	  (*it).second->SNSetRead(false);
      }
    return (true);
  }

  bool SNAddRead(T socket, ISocket * isocket)
  {
    if (this->_readMap.find(socket) == this->_readMap.end())
      this->_readMap.insert(std::pair<T, ISocket *>(socket, isocket));
    FD_SET(socket, &(this->_readFd));
#ifndef _WIN32
    if (socket > this->_maxFd)
      this->_maxFd = socket;
#endif
    return (true);
  }

  bool SNAddWrite(T socket, ISocket * isocket)
  {
    if (this->_writeMap.find(socket) == this->_writeMap.end())
      this->_writeMap.insert(std::pair<T, ISocket *>(socket, isocket));
    FD_SET(socket, &(this->_writeFd));
#ifndef _WIN32
    if (socket > this->_maxFd)
      this->_maxFd = socket;
#endif
    return (true);
  }

  bool SNDelRead(T socket, ISocket *)
  {
    this->_readMap.erase(socket);
    FD_CLR(socket, &(this->_readFd));
    return (true);
  }

  bool SNDelWrite(T socket, ISocket *)
  {
    this->_writeMap.erase(socket);
    FD_CLR(socket, &(this->_writeFd));
    return (true);
  }

  void setTimer(long sec, long usec)
  {
    this->_timeout.tv_sec = sec;
    this->_timeout.tv_usec = usec;
  }

  long getSec(void) const
  {
    return (this->_timeout.tv_sec);
  }

  long getUsec(void) const
  {
    return (this->_timeout.tv_usec);
  }

private:
  fd_set	_readFd;
  fd_set	_writeFd;
  int		_maxFd;
  struct timeval _timeout;
  std::map<T, ISocket *> _readMap;
  std::map<T, ISocket *> _writeMap;
};

#endif	// SELECTOR
