#ifndef __ATCP_SERVER_SOCKET_HH__
#define __ATCP_SERVER_SOCKET_HH__

#include <iostream>
#include "ISocket.h"
#include "ATCPClientSocket.h"

class 	ATCPServerSocket : public ISocket
{
public:
  ATCPServerSocket(void);
  virtual ~ATCPServerSocket();
  virtual bool			SNCreate(std::string const &host, int port) = 0;
  virtual int			SNRead(char *buffer, unsigned int size) = 0;
  virtual int			SNWrite(const char *msg, unsigned int) = 0;
  virtual bool			SNListen(void) = 0;
  virtual ATCPClientSocket *	SNAccept(void) = 0;
  std::string			getHost(void) const;
  int				getPort(void) const;
  virtual char			*getIp(void) const = 0;
  virtual bool			SNClose(void) = 0;
  virtual eSocketErr		SNGetLastErr(void) const = 0;

  virtual bool			SNAddRead(void) = 0;
  virtual bool			SNAddWrite(void) = 0;
  virtual bool			SNDelRead(void) = 0;
  virtual bool			SNDelWrite(void) = 0;

  virtual void			SNSetRead(bool) = 0;
  virtual void			SNSetWrite(bool) = 0;
  virtual bool			SNGetRead(void) const = 0;
  virtual bool			SNGetWrite(void) const = 0;
protected:
  std::string		_host;
  int			_port;
};

#endif //__ATCP_SERVER_SOCKET_HH__
