#ifndef __UDP_SERVER_SOCKET_HPP_
#define __UDP_SERVER_SOCKET_HPP_

#ifndef _WIN32
# include <stdint.h>
# include <arpa/inet.h>
#else
# include <winsock2.h>
#endif

#include <iostream>
#include <string>
#include <map>
#include "ISocket.h"

class AUDPServerSocket : public ISocket
{
public:
  AUDPServerSocket(void);
  virtual ~AUDPServerSocket(void);
  virtual bool		SNCreate(std::string const &host, int port) = 0;
  virtual int		SNRead(char *msg, unsigned int size) = 0;
  virtual int		SNWrite(const char *msg, unsigned int size) = 0;
  virtual bool		SNClose(void) = 0;
  virtual eSocketErr	SNGetLastErr(void) const = 0;

  virtual bool		SNAddRead(void) = 0;
  virtual bool		SNAddWrite(void) = 0;
  virtual bool		SNDelRead(void) = 0;
  virtual bool		SNDelWrite(void) = 0;

  virtual void		SNSetRead(bool) = 0;
  virtual void		SNSetWrite(bool) = 0;
  virtual bool		SNGetRead(void) const = 0;
  virtual bool		SNGetWrite(void) const = 0;

  virtual char		*getIp(void) const = 0;

  bool				SNAddClient(std::string const &, int port);
  bool				SNDelClient(std::string const &);
  virtual int			SNReadClient(char *msg, unsigned int size, std::string &ip) = 0;
  virtual int			SNWriteClients(const char *msg, unsigned int size) = 0;
  virtual int			SNWriteToClient(const char *msg, unsigned int size, const std::string &ip) = 0;

protected:
	std::map<std::string, struct sockaddr_in *> _contactMap;
};

#endif // __UDP_SERVER_SOCKET_HPP_
