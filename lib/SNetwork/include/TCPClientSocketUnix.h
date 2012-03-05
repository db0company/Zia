#ifndef __TCP_CLIENT_SOCKET_UNIX_HH_
#define __TCP_CLIENT_SOCKET_UNIX_HH_

#include <iostream>
#include <string>
#include <stdint.h>
#include "ISocket.h"
#include "ISelector.h"
#include "ATCPClientSocket.h"
#include <arpa/inet.h>

class 	TCPClientSocketUnix : public ATCPClientSocket
{
private:
  TCPClientSocketUnix(void);
public:
  TCPClientSocketUnix(ISelector*_selector);
  virtual ~TCPClientSocketUnix(void);
  TCPClientSocketUnix(const TCPClientSocketUnix &other);
  TCPClientSocketUnix& operator=(const TCPClientSocketUnix &other);
  virtual bool		SNCreate(std::string const &host, int port);
  void			SNCreateAccept(int socket, struct sockaddr_in addr);
  virtual int		SNRead(char *msg, unsigned int size);
  virtual int		SNWrite(const char *msg, unsigned int size);
  virtual bool		SNConnect(void);
  virtual bool		SNClose(void);
  virtual eSocketErr	SNGetLastErr(void) const;

  virtual bool		SNAddRead(void);
  virtual bool		SNAddWrite(void);
  virtual bool		SNDelRead(void);
  virtual bool		SNDelWrite(void);

  virtual void		SNSetRead(bool);
  virtual void		SNSetWrite(bool);
  virtual bool		SNGetRead(void) const;
  virtual bool		SNGetWrite(void) const;

  virtual char*		getIp(void)const;
private:
  ISelector		*_selector;
  int			_socket;
  eSocketErr		_error;
  bool			_canread;
  bool			_canwrite;
  struct sockaddr_in	_addr;
};


#endif //__TCP_CLIENT_SOCKET_UNIX_HH_
