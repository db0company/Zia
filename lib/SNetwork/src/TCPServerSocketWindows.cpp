#include <iostream>
#include <string>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include "ISocket.h"
#include "ISelector.h"
#include "Selector.hpp"
#include "ATCPServerSocket.h"
#include "ATCPClientSocket.h"
#include "TCPClientSocketWindows.h"
#include "TCPServerSocketWindows.h"

//#define PF_INET AF_INET;

//typedef int socklent_t;

TCPServerSocketWindows::TCPServerSocketWindows(void)
{
}
TCPServerSocketWindows::TCPServerSocketWindows(ISelector *selector) :
	ATCPServerSocket(), _selector(selector), _error(NOERRORSOCKET), _canread(false), _canwrite(false)
{
}

TCPServerSocketWindows::~TCPServerSocketWindows()
{
}

TCPServerSocketWindows::TCPServerSocketWindows(const TCPServerSocketWindows &other)
{
 this->_socket = other._socket;
  this->_error = other._error;
  this->_port = other._port;
  this->_host = other._host;
  this->_selector = other._selector;
  this->_canread = other._canread;
  this->_canwrite = other._canwrite;
}

TCPServerSocketWindows& TCPServerSocketWindows::operator=(const TCPServerSocketWindows &other)
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

bool				TCPServerSocketWindows::SNCreate(std::string const &host, int port)
{
	WSADATA		startupdata;
	sockaddr_in	s;
	this->_host = host;
	this->_port = port;
	if (WSAStartup(MAKEWORD(2, 2), &startupdata) != 0)
	{
		this->_error = WSASTARTUP;
		return (false);
	}
	if ((this->_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP,
		NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
//		std::cout << "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
		this->_error = SOCKETCREAT;
		return (false);
	}
	s.sin_family = AF_INET;
    s.sin_addr.s_addr = INADDR_ANY;
    s.sin_port = htons(this->_port);
	if (bind(this->_socket, (const sockaddr *)&s, sizeof(s)) == SOCKET_ERROR)
	{
//		std::cout << "WWWWWWprout cacaWWWWWWWWWWWWWWWWWWWWWWWWWWW" << std::endl;
//		std::cout << "bind error" << WSAGetLastError() << std::endl;
		this->_error = ALREADYBIND;
		return (false);
	}
	this->_error = NOERRORSOCKET;
	return (true);
}

int				TCPServerSocketWindows::SNRead(char *msg, unsigned int size)
{
	WSABUF	DataBuff;
	DWORD	BytesReceived;
	DWORD	flags = 0;

	DataBuff.buf = (msg);
	DataBuff.len = size;
	if (WSARecv(this->_socket, &DataBuff, 1, &BytesReceived, &flags, NULL, NULL) == SOCKET_ERROR)
		{
			this->_error = CANTREAD;
			return (-1);
		}
	this->_error = NOERRORSOCKET;
	return (BytesReceived);
}
int				TCPServerSocketWindows::SNWrite(const char *msg, unsigned int size)
{
	WSABUF		DataBuff;
	DWORD		SendBytes;

	DataBuff.buf = const_cast <char *> (msg);
	DataBuff.len = size;
	if (WSASend(this->_socket, &DataBuff, 1, &SendBytes, 0, NULL, NULL) == SOCKET_ERROR)
		{
			this->_error = CANTWRITE;
			return (-1);
		}
	this->_error = NOERRORSOCKET;
	return (SendBytes);
}

bool				TCPServerSocketWindows::SNListen(void)
{
	if (listen(this->_socket, SOMAXCONN) == SOCKET_ERROR)
	{
		this->_error = CANTLISTEN;
		return (false);
	}
	this->_error = NOERRORSOCKET;
	return (true);
}

TCPClientSocketWindows		*TCPServerSocketWindows::SNAccept(void)
{
  SOCKET			client_socket;
  TCPClientSocketWindows	*new_client;
  struct sockaddr_in addr;
  socklen_t addrlen;

  addrlen = sizeof(addr);
  //if ((client_socket = accept(this->_socket, (sockaddr *)&addr, &addrlen)) == INVALID_SOCKET)
    if ((client_socket = WSAAccept(this->_socket, (SOCKADDR*) &addr, &addrlen, 
        NULL, NULL)) == INVALID_SOCKET)
    {
      this->_error = CANTACCEPT;
      return (NULL);
    }
  new_client = new TCPClientSocketWindows(this->_selector);
  new_client->SNCreateAccept(client_socket, addr);
  this->_error = NOERRORSOCKET;
  return (new_client);
}

bool				TCPServerSocketWindows::SNClose(void)
{
//	if (closesocket(this->_socket) == SOCKET_ERROR)
//		return (false);
	if (WSACleanup() == SOCKET_ERROR)
		return (false);
	return (true);
}

eSocketErr			TCPServerSocketWindows::SNGetLastErr(void) const
{
	return (this->_error);
}

bool				TCPServerSocketWindows::SNAddRead(void)
{
  if (this->_selector)
    {
      static_cast <Selector<SOCKET> *>(this->_selector)->SNAddRead(this->_socket, this);
      return (true);
    }
  return (false);
}

bool				TCPServerSocketWindows::SNAddWrite(void)
{
  if (this->_selector)
    {
      static_cast <Selector<SOCKET> *>(this->_selector)->SNAddWrite(this->_socket, this);
      return (true);
    }
  return (false);
}

bool				TCPServerSocketWindows::SNDelRead(void)
{
  if (this->_selector)
    {
      static_cast <Selector<SOCKET> *>(this->_selector)->SNDelRead(this->_socket, this);
      return (true);
    }
  return (false);
}

bool				TCPServerSocketWindows::SNDelWrite(void)
{
  if (this->_selector)
    {
      static_cast <Selector<SOCKET> *>(this->_selector)->SNDelWrite(this->_socket, this);
      return (true);
    }
  return (false);
}

void				TCPServerSocketWindows::SNSetRead(bool s)
{
	this->_canread = s;
}

void				TCPServerSocketWindows::SNSetWrite(bool s)
{
	this->_canwrite = s;
}

bool				TCPServerSocketWindows::SNGetRead(void) const
{
	return (this->_canread);
}

bool				TCPServerSocketWindows::SNGetWrite(void) const
{
	return (this->_canwrite);
}

char *				TCPServerSocketWindows::getIp(void) const
{
  return (NULL);
}
