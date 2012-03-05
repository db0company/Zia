#ifndef __UDP_CLIENT_SOCKET_WINDOWS_HH__
#define __UDP_CLIENT_SOCKET_WINDOWS_HH__

#include <iostream>
#include <winsock2.h>
#include "ISocket.h"
#include "ISelector.h"

class UDPClientSocketWindows : public ISocket
{
private:
  UDPClientSocketWindows(void);
public:
  UDPClientSocketWindows(ISelector *);
  virtual ~UDPClientSocketWindows(void);
  UDPClientSocketWindows(const UDPClientSocketWindows &other);
  UDPClientSocketWindows& operator=(const UDPClientSocketWindows &other);
  virtual bool		SNCreate(std::string const &host, int port);
  virtual int		SNRead(char *msg, unsigned int size);
  virtual int		SNWrite(const char *msg, unsigned int size);
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
  virtual char		*  getIp(void) const;
private:
  SOCKET			_socket;
  ISelector			*_selector;
  std::string		_host;
  int				_port;
  eSocketErr		_error;
  struct sockaddr_in	_servaddr;
  bool				_canread;
  bool				_canwrite;
};

#endif //__UDP_CLIENT_SOCKET_WINDOWS_HH__
