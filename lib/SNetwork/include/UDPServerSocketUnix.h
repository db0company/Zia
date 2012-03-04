#ifndef __UDP_SERVER_SOCKET_UNIX_HH__
#define __UDP_SERVER_SOCKET_UNIX_HH__

#include <iostream>
#include <stdint.h>
#include <arpa/inet.h>
#include "ISocket.h"
#include "AUDPServerSocket.h"
#include "ISelector.h"

class UDPServerSocketUnix : public AUDPServerSocket
{
private:
  UDPServerSocketUnix(void);
public:
  UDPServerSocketUnix(ISelector *);
  virtual ~UDPServerSocketUnix(void);
  UDPServerSocketUnix(const UDPServerSocketUnix &other);
  UDPServerSocketUnix& operator=(const UDPServerSocketUnix &other);
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

  virtual char*		getIp(void)const;

  virtual int				SNReadClient(char *msg, unsigned int size, std::string &ip);
  virtual int				SNWriteClients(const char *msg, unsigned int size);
  virtual int				SNWriteToClient(const char *msg, unsigned int size, const std::string &ip);

private:
  int			_socket;
  ISelector		*_selector;
  std::string		_host;
  int			_port;
  struct sockaddr_in	_daddr;
  eSocketErr		_error;
  bool			_canread;
  bool			_canwrite;
};

#endif //__UDP_SERVER_SOCKET_UNIX_HH__
