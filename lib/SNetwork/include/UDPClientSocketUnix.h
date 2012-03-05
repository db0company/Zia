#ifndef __UDP_CLIENT_SOCKET_UNIX_HH__
#define __UDP_CLIENT_SOCKET_UNIX_HH__

#include <iostream>
#include <stdint.h>
#include <arpa/inet.h>
#include "ISocket.h"

class UDPClientSocketUnix : public ISocket
{
private:
  UDPClientSocketUnix(void);
public:
  UDPClientSocketUnix(ISelector *);
  virtual ~UDPClientSocketUnix(void);
  UDPClientSocketUnix(const UDPClientSocketUnix &other);
  UDPClientSocketUnix& operator=(const UDPClientSocketUnix &other);
  virtual bool		SNCreate(std::string const &host, int port);
  virtual int		SNRead(char *msg, uint32_t size);
  virtual int		SNWrite(const char *msg, uint32_t size);
  virtual bool		SNClose(void);
  std::string		getHost(void) const;
  int			getPort(void) const;
  virtual eSocketErr	SNGetLastErr(void) const;

  virtual bool		SNAddRead(void);
  virtual bool		SNAddWrite(void);
  virtual bool		SNDelRead(void);
  virtual bool		SNDelWrite(void);

  virtual void		SNSetRead(bool);
  virtual void		SNSetWrite(bool);
  virtual bool		SNGetRead(void) const;
  virtual bool		SNGetWrite(void) const;
  virtual char *	getIp(void) const;
private:
  int			_socket;
  ISelector		*_selector;
  std::string		_host;
  int			_port;
  eSocketErr		_error;
  struct sockaddr_in	_servaddr;
  bool			_canread;
  bool			_canwrite;
};

#endif //__UDP_CLIENT_SOCKET_UNIX_HH__
