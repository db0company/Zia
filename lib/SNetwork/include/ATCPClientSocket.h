#ifndef __ATCP_CLIENT_SOCKET_HH_
#define __ATCP_CLIENT_SOCKET_HH_

#include <iostream>
#include <string>
#include "ISocket.h"

class 	ATCPClientSocket : public ISocket
{
public:
  ATCPClientSocket(void);
  virtual ~ATCPClientSocket(void);
  virtual bool		SNCreate(std::string const &host, int port) = 0;
  virtual int		SNRead(char *msg, unsigned int size) = 0;
  virtual int		SNWrite(const char *buffer, unsigned int size) = 0;
  virtual bool		SNConnect(void) = 0;
  virtual bool		SNClose(void) = 0;
  virtual eSocketErr	SNGetLastErr(void) const = 0;
  virtual char		*getIp(void) const = 0;
  std::string		getHost(void) const;
  int			getPort(void) const;

  virtual bool		SNAddRead(void) = 0;
  virtual bool		SNAddWrite(void) = 0;
  virtual bool		SNDelRead(void) = 0;
  virtual bool		SNDelWrite(void) = 0;

  virtual void		SNSetRead(bool) = 0;
  virtual void		SNSetWrite(bool) = 0;
  virtual bool		SNGetRead(void) const = 0;
  virtual bool		SNGetWrite(void) const = 0;
protected:
  std::string		_host;
  int			_port;
};


#endif //__ATCP_CLIENT_SOCKET_HH_
