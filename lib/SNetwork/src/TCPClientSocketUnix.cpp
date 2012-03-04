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
#include "ATCPClientSocket.h"
#include "TCPClientSocketUnix.h"

TCPClientSocketUnix::TCPClientSocketUnix(ISelector *selector) : ATCPClientSocket(), _selector(selector), _socket(-1),
								_error(NOERRORSOCKET), _canread(false), _canwrite(false)
{
}

TCPClientSocketUnix::~TCPClientSocketUnix(void)
{
}

TCPClientSocketUnix::TCPClientSocketUnix(const TCPClientSocketUnix&other)
{
  this->_addr = other._addr;
  this->_socket = other._socket;
  this->_error = other._error;
  this->_port = other._port;
  this->_host = other._host;
  this->_selector = other._selector;
  this->_canread = other._canread;
  this->_canwrite = other._canwrite;
}

TCPClientSocketUnix& TCPClientSocketUnix::operator=(const TCPClientSocketUnix&other)
{
  this->_addr = other._addr;
  this->_socket = other._socket;
  this->_error = other._error;
  this->_port = other._port;
  this->_host = other._host;
  this->_selector = other._selector;
  this->_canread = other._canread;
  this->_canwrite = other._canwrite;
  return (*this);
}

bool	TCPClientSocketUnix::SNCreate(std::string const &host, int port)
{
  this->_host = host;
  this->_port = port;
  if ((this->_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
      this->_error = SOCKETCREAT;
      return (false);
    }
  this->_error = NOERRORSOCKET;
  return (true);
}

int		TCPClientSocketUnix::SNRead(char *msg, unsigned int size)
{
  int		err;

  if (this->SNGetRead())
    {
      if ((err = read(this->_socket, msg, size)) <= 0)
	{
	  if (err == 0)
	    this->_error = CONNECTIONLOST;
	  else
	    this->_error = CANTREAD;
	  this->SNDelRead();
	  return (err);
	}
      this->_error = NOERRORSOCKET;
      this->_canread = false;
      return (err);
    }
  this->_error = ALREADY_READ;
  return (-1);
}

int		TCPClientSocketUnix::SNWrite(const char *msg, unsigned int size)
{
  int		err;

  if (this->SNGetWrite())
    {
      if ((err = write(this->_socket, msg, size)) <= 0)
	{
	  this->_error = CANTWRITE;
	  this->SNDelWrite();
	  return (err);
	}
      this->_error = NOERRORSOCKET;
      this->_canwrite = false;
      return (err);
    }
  this->_error = ALREADY_WRITE;
  return (-1);
}

bool	TCPClientSocketUnix::SNConnect(void)
{
  struct sockaddr_in	addr;
  // struct hostent	*hp;

  memset(&addr, 0, sizeof(struct sockaddr_in));
  // if ((hp = gethostbyname(this->_host.c_str())) == NULL)
  //   {
  //  this->_error = CANTGETHOST;
  //     return (false);
  //   }
  addr.sin_family = AF_INET;
  addr.sin_port = htons(this->_port);
  addr.sin_addr.s_addr = inet_addr(this->_host.c_str());
  //  addr.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
  if (connect(this->_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
      this->_error = CONNECTIONERR;
      return (false);
    }
  this->_error = NOERRORSOCKET;
  return (true);
}

void			TCPClientSocketUnix::SNCreateAccept(int socket, struct sockaddr_in addr)
{
  memcpy(&(this->_addr), &addr, sizeof(sockaddr_in));
  this->_host = "";
  this->_port = -1;
  this->_error = NOERRORSOCKET;
  this->_socket = socket;
}

bool			TCPClientSocketUnix::SNClose(void)
{
  this->SNDelRead();
  this->SNDelWrite();
  if (close(this->_socket) != 0)
    {
      return (false);
    }
  this->_error = NOERRORSOCKET;
  return (true);
}

eSocketErr	TCPClientSocketUnix::SNGetLastErr(void) const
{
  return (this->_error);
}

bool		TCPClientSocketUnix::SNAddRead(void)
{
  if (this->_selector)
    {
      static_cast <Selector<int> *>(this->_selector)->SNAddRead(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		TCPClientSocketUnix::SNAddWrite(void)
{
  if (this->_selector)
    {
      static_cast <Selector<int> *>(this->_selector)->SNAddWrite(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		TCPClientSocketUnix::SNDelRead(void)
{
  if (this->_selector)
    {
      static_cast <Selector<int> *>(this->_selector)->SNDelRead(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		TCPClientSocketUnix::SNDelWrite(void)
{
  if (this->_selector)
    {
      static_cast <Selector<int> *>(this->_selector)->SNDelWrite(this->_socket, this);
      return (true);
    }
  return (false);
}

void		TCPClientSocketUnix::SNSetRead(bool state)
{
  this->_canread = state;
}

void		TCPClientSocketUnix::SNSetWrite(bool state)
{
  this->_canwrite = state;
}

bool		TCPClientSocketUnix::SNGetRead(void) const
{
  return (this->_canread);
}

bool		TCPClientSocketUnix::SNGetWrite(void) const
{
  return (this->_canwrite);
}

char		*TCPClientSocketUnix::getIp(void) const
{
  char *str = new char[50];

  inet_ntop(AF_INET, &(this->_addr.sin_addr), str, 49);
  return (str);
}
