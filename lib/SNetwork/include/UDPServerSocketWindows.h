#ifndef __UDP_SERVER_SOCKET_WINDOWS_HH__
#define __UDP_SERVER_SOCKET_WINDOWS_HH__

#include <winsock2.h>
#include <iostream>
#include "ISocket.h"
#include "AUDPServerSocket.h"
#include "ISelector.h"

class UDPServerSocketWindows : public AUDPServerSocket
{
private:
  UDPServerSocketWindows(void);
public:
  UDPServerSocketWindows(ISelector *);
  virtual ~UDPServerSocketWindows(void);
  UDPServerSocketWindows(const UDPServerSocketWindows &other);
  UDPServerSocketWindows& operator=(const UDPServerSocketWindows &other);
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

  virtual char		*getIp(void) const;

  virtual int				SNReadClient(char *msg, unsigned int size, std::string &ip);
  virtual int				SNWriteClients(const char *msg, unsigned int size);
  virtual int				SNWriteToClient(const char *msg, unsigned int size, const std::string &ip);

private:
  SOCKET		_socket;
  ISelector		*_selector;
  std::string	_host;
  int			_port;
  struct sockaddr_in	_daddr;
  eSocketErr	_error;
  bool			_canread;
  bool			_canwrite;
};

#endif //__UDP_SERVER_SOCKET_WINDOWS_HH__
