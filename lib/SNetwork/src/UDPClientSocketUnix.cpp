#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#include <string>
#include <stdint.h>
#include "ISocket.h"
#include "ISelector.h"
#include "Selector.hpp"
#include "UDPClientSocketUnix.h"

UDPClientSocketUnix::UDPClientSocketUnix(void)
{
}

UDPClientSocketUnix::UDPClientSocketUnix(ISelector *s) :
  _socket(-1), _selector(s), _host("127.0.0.1"), _port(12345), _error(NOERRORSOCKET), _canread(false), _canwrite(false)
{
}

UDPClientSocketUnix::~UDPClientSocketUnix(void)
{
}

UDPClientSocketUnix::UDPClientSocketUnix(const UDPClientSocketUnix &other)
{
  this->_socket = other._socket;
  this->_selector = other._selector;
  this->_host = other._host;
  this->_port = other._port;
  this->_error = other._error;
  this->_canread = other._canread;
  this->_canwrite = other._canwrite;
}

UDPClientSocketUnix& UDPClientSocketUnix::operator=(const UDPClientSocketUnix &other)
{
  this->_socket = other._socket;
  this->_selector = other._selector;
  this->_host = other._host;
  this->_port = other._port;
  this->_error = other._error;
  this->_canread = other._canread;
  this->_canwrite = other._canwrite;
  return (*this);
}

bool		UDPClientSocketUnix::SNCreate(std::string const &host, int port)
{
  // struct hostent	*hostinfo;

  this->_port = port;
  this->_host = host;
  if ((this->_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
      this->_error = SOCKETCREAT;
      return (false);
    }
  // if ((hostinfo = gethostbyname(this->_host.c_str())) == NULL)
  //   {
  //     this->_error = CANTGETHOST;
  //     return (false);
  //   }
  // server.sin_addr = hostinfo->h_addr;
  this->_servaddr.sin_family = AF_INET;
  this->_servaddr.sin_port = htons(this->_port);
  this->_servaddr.sin_addr.s_addr = inet_addr(this->_host.c_str());
  // if (bind(this->_socket, (struct sockaddr *)&this->_servaddr, sizeof(this->_servaddr)) == -1)
  //   {
  //     this->_error = ALREADYBIND;
  //     return (false);
  //   }
  this->_error = NOERRORSOCKET;
  return (true);
}

int		UDPClientSocketUnix::SNRead(char *msg, uint32_t size)
{
  struct sockaddr_in *from;
  unsigned int	length;
  int		ret;

  length = sizeof(from);
  if ((ret = recvfrom(this->_socket, msg, size, 0, (struct sockaddr *)&from, &length)) <= 0)
    {
      if (ret == 0)
	this->_error = CONNECTIONLOST;
      else
	this->_error = CANTREAD;
      return (ret);
    }
  this->_error = NOERRORSOCKET;
  return (ret);
}

int		UDPClientSocketUnix::SNWrite(const char *msg, uint32_t size)
{
  int		ret;

  if ((ret = sendto(this->_socket, msg, size, 0, (sockaddr *)&(this->_servaddr), sizeof(this->_servaddr))) <= 0)
    {
      if (ret == 0)
	this->_error = CONNECTIONLOST;
      else
	this->_error = CANTREAD;
      return (ret);
    }
  this->_error = NOERRORSOCKET;
  return (ret);
}

bool		UDPClientSocketUnix::SNClose(void)
{
  if (close(this->_socket) == -1)
    return (false);
  return (true);
}

std::string	UDPClientSocketUnix::getHost(void) const
{
  return (this->_host);
}

int		UDPClientSocketUnix::getPort(void) const
{
  return (this->_port);
}

eSocketErr	UDPClientSocketUnix::SNGetLastErr(void) const
{
  return (this->_error);
}

bool		UDPClientSocketUnix::SNAddRead(void)
{
  if (this->_selector)
    {
      static_cast <Selector<int> *>(this->_selector)->SNAddRead(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		UDPClientSocketUnix::SNAddWrite(void)
{
  if (this->_selector)
    {
      static_cast <Selector<int> *>(this->_selector)->SNAddWrite(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		UDPClientSocketUnix::SNDelRead(void)
{
  if (this->_selector)
    {
      static_cast <Selector<int> *>(this->_selector)->SNDelRead(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		UDPClientSocketUnix::SNDelWrite(void)
{
  if (this->_selector)
    {
      static_cast <Selector<int> *>(this->_selector)->SNDelWrite(this->_socket, this);
      return (true);
    }
  return (false);
}

void		UDPClientSocketUnix::SNSetRead(bool state)
{
  this->_canread = state;
}

void		UDPClientSocketUnix::SNSetWrite(bool state)
{
  this->_canwrite = state;
}

bool		UDPClientSocketUnix::SNGetRead(void) const
{
  return (this->_canread);
}

bool		UDPClientSocketUnix::SNGetWrite(void) const
{
  return (this->_canwrite);
}

char*		UDPClientSocketUnix::getIp(void) const
{
  return (NULL);
}
