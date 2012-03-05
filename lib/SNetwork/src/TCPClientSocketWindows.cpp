#include <iostream>
#include <string>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include "ISelector.h"
#include "ISocket.h"
#include "Selector.hpp"
#include "ATCPClientSocket.h"
#include "TCPClientSocketWindows.h"

#define PF_INET AF_INET;

TCPClientSocketWindows::TCPClientSocketWindows(void)
{
}

TCPClientSocketWindows::TCPClientSocketWindows(ISelector* selector) :
  ATCPClientSocket(), _selector(selector), _canread(false), _canwrite(false)
{
	this->_error = NOERRORSOCKET;
}

TCPClientSocketWindows::~TCPClientSocketWindows(void)
{
}

TCPClientSocketWindows::TCPClientSocketWindows(const TCPClientSocketWindows &other)
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

TCPClientSocketWindows& TCPClientSocketWindows::operator=(const TCPClientSocketWindows &other)
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

bool		TCPClientSocketWindows::SNCreate(std::string const &host, int port)
{
	WSADATA		startupdata;

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
		this->_error = SOCKETCREAT;
		return (false);
	}
	this->_error = NOERRORSOCKET;
	return (true);
}

void		TCPClientSocketWindows::SNCreateAccept(SOCKET socket, struct sockaddr_in addr)
{
  memcpy(&(this->_addr), &addr, sizeof(sockaddr_in));
//  this->_addr = addr;
  this->_host = "";
  this->_port = -1;
  this->_error = NOERRORSOCKET;
  this->_socket = socket;
}

int			TCPClientSocketWindows::SNRead(char *msg, unsigned int size)
{
	WSABUF	DataBuff;
	DWORD	BytesReceived;
	DWORD	flags = 0;

	DataBuff.buf = msg;
	DataBuff.len = size;
	if (WSARecv(this->_socket, &DataBuff, 1, &BytesReceived, &flags, NULL, NULL) == SOCKET_ERROR)
		{
			this->_error = CANTREAD;
			return (-1);
		}
	this->_error = NOERRORSOCKET;
	return (BytesReceived);
}

int			TCPClientSocketWindows::SNWrite(const char *msg, unsigned int size)
{
	WSABUF		WDataBuf;
	DWORD		SendBytes;

	WDataBuf.buf = (const_cast <char *> (msg));
	WDataBuf.len = size;
	if (WSASend(this->_socket, &WDataBuf, 1, &SendBytes, 0, NULL, NULL) == SOCKET_ERROR)
		{
			this->_error = CANTWRITE;
			return (-1);
		}
	this->_error = NOERRORSOCKET;
	return (SendBytes);
}

bool		TCPClientSocketWindows::SNConnect(void)
{
	struct sockaddr_in	s;

	s.sin_family = AF_INET;
    s.sin_addr.s_addr = inet_addr(this->_host.c_str());
    s.sin_port = htons(this->_port);
	if (WSAConnect(this->_socket, (sockaddr *)&s, sizeof(s), NULL, NULL, NULL, NULL) == SOCKET_ERROR)
	{
		this->_error = CONNECTIONERR;
		return (false);
	}
	this->_error = NOERRORSOCKET;
	return (true);
}

bool		TCPClientSocketWindows::SNClose(void)
{
//	if (closesocket(this->_socket) == SOCKET_ERROR)
//		return (false);
	if (WSACleanup() == SOCKET_ERROR)
		return (false);
	return (true);
}

eSocketErr	TCPClientSocketWindows::SNGetLastErr(void) const
{
	return (this->_error);
}

bool		TCPClientSocketWindows::SNAddRead(void)
{
 if (this->_selector)
    {
      static_cast <Selector<SOCKET> *>(this->_selector)->SNAddRead(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		TCPClientSocketWindows::SNAddWrite(void)
{
  if (this->_selector)
    {
      static_cast <Selector<SOCKET> *>(this->_selector)->SNAddWrite(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		TCPClientSocketWindows::SNDelRead(void)
{
  if (this->_selector)
    {
      static_cast <Selector<SOCKET> *>(this->_selector)->SNDelRead(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		TCPClientSocketWindows::SNDelWrite(void)
{
  if (this->_selector)
    {
      static_cast <Selector<SOCKET> *>(this->_selector)->SNDelWrite(this->_socket, this);
      return (true);
    }
  return (false);
}

void		TCPClientSocketWindows::SNSetRead(bool status)
{
	this->_canread = status;
}

void		TCPClientSocketWindows::SNSetWrite(bool status)
{
	this->_canwrite = status;
}

bool		TCPClientSocketWindows::SNGetRead(void) const
{
	return (this->_canread);
}

bool		TCPClientSocketWindows::SNGetWrite(void) const
{
	return (this->_canwrite);
}

char *TCPClientSocketWindows::getIp(void) const
{
  char *str = new char[50];

  InetNtop(AF_INET, (void *)&(this->_addr.sin_addr), reinterpret_cast<PSTR>(str), 49);
	//  inet_ntop(AF_INET, &(this->_addr.sin_addr), str, 49);
  return (str);
}
