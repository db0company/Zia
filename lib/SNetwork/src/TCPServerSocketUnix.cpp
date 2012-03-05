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
#include "TCPClientSocketUnix.h"
#include "TCPServerSocketUnix.h"
#include "Selector.hpp"

TCPServerSocketUnix::TCPServerSocketUnix(ISelector *selector) :
  ATCPServerSocket(), _selector(selector), _socket(-1), _error(NOERRORSOCKET), _canread(false), _canwrite(false)
{
}

TCPServerSocketUnix::~TCPServerSocketUnix()
{
}

TCPServerSocketUnix::TCPServerSocketUnix(const TCPServerSocketUnix &other)
{
  this->_socket = other._socket;
  this->_error = other._error;
  this->_port = other._port;
  this->_host = other._host;
  this->_selector = other._selector;
  this->_canread = other._canread;
  this->_canwrite = other._canwrite;
}

TCPServerSocketUnix& TCPServerSocketUnix::operator=(const TCPServerSocketUnix &other)
{
  this->_socket = other._socket;
  this->_error = other._error;
  this->_port = other._port;
  this->_host = other._host;
  this->_selector = other._selector;
  this->_canread = other._canread;
  this->_canwrite = other._canwrite;
  return (*this);
}

bool		TCPServerSocketUnix::SNCreate(std::string const &host, int port)
{
  int		yes;
  struct sockaddr_in addr;

  yes = 1;
  this->_host = host;
  this->_port = port;
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(this->_port);
  addr.sin_addr.s_addr = INADDR_ANY;
  if ((this->_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0 ||
      setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
      this->_error = SOCKETCREAT;
      return (false);
    }
  if (bind(this->_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
      this->_error = ALREADYBIND;
      return (false);
    }
  this->_error = NOERRORSOCKET;
  return (true);
}

int		TCPServerSocketUnix::SNRead(char *msg, uint32_t size)
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

int		TCPServerSocketUnix::SNWrite(const char *msg, uint32_t size)
{
  int		err;

  if (this->SNGetWrite())
    {
      if ((err = write(this->_socket, msg, size)) <= 0)
	{
	  this->SNDelWrite();
	  this->_error = CANTWRITE;
	  return (err);
	}
      this->_error = NOERRORSOCKET;
      this->_canwrite = false;
      return (err);
    }
  this->_error = ALREADY_WRITE;
  return (-1);
}

bool		TCPServerSocketUnix::SNListen(void)
{
  if (listen(this->_socket, 42) < 0)
    {
      this->_error = CANTLISTEN;
      return (false);
    }
  this->_error = NOERRORSOCKET;
  return (true);
}

TCPClientSocketUnix	*TCPServerSocketUnix::SNAccept(void)
{
  int			clientsocket;
  socklen_t             addrlen;
  struct sockaddr_in     addr;
  TCPClientSocketUnix	*new_client;

  addrlen = sizeof(struct sockaddr_in);
  clientsocket = accept(this->_socket, (struct sockaddr *)&addr, &addrlen);
  if (clientsocket == -1)
    {
      this->_error = CANTACCEPT;
      return (NULL);
    }
  new_client = new TCPClientSocketUnix(this->_selector);
  new_client->SNCreateAccept(clientsocket, addr);
  this->_error = NOERRORSOCKET;
  return (new_client);
}

bool		TCPServerSocketUnix::SNClose(void)
{
  if (close(this->_socket) == -1)
    {
      this->_error = CLOSEERR;
      return (false);
    }
  this->_error = NOERRORSOCKET;
  return (true);
}

eSocketErr	TCPServerSocketUnix::SNGetLastErr(void) const
{
  return (this->_error);
}

bool		TCPServerSocketUnix::SNAddRead(void)
{
  if (this->_selector)
    {
      static_cast <Selector<int> *>(this->_selector)->SNAddRead(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		TCPServerSocketUnix::SNAddWrite(void)
{
  if (this->_selector)
    {
      static_cast <Selector<int> *>(this->_selector)->SNAddWrite(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		TCPServerSocketUnix::SNDelRead(void)
{
  if (this->_selector)
    {
      static_cast <Selector<int> *>(this->_selector)->SNDelRead(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		TCPServerSocketUnix::SNDelWrite(void)
{
  if (this->_selector)
    {
      static_cast <Selector<int> *>(this->_selector)->SNDelWrite(this->_socket, this);
      return (true);
    }
  return (false);
}

void		TCPServerSocketUnix::SNSetRead(bool state)
{
  this->_canread = state;
}

void		TCPServerSocketUnix::SNSetWrite(bool state)
{
  this->_canwrite = state;
}

bool		TCPServerSocketUnix::SNGetRead(void) const
{
  return (this->_canread);
}

bool		TCPServerSocketUnix::SNGetWrite(void) const
{
  return (this->_canwrite);
}

char *		TCPServerSocketUnix::getIp(void) const
{
  return (NULL);
}
