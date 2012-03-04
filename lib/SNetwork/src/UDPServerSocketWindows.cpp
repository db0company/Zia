#include <winsock2.h>
#include <Ws2tcpip.h>
#include <map>
#include <iterator>
#include "ISocket.h"
#include "ISelector.h"
#include "Selector.hpp"
#include "UDPServerSocketWindows.h"

UDPServerSocketWindows::UDPServerSocketWindows(void)
{
}

UDPServerSocketWindows::UDPServerSocketWindows(ISelector *s) :
	_selector(s), _host("127.0.0.1"), _port(12345), _error(NOERRORSOCKET), _canread(false), _canwrite(false)
{
}

UDPServerSocketWindows::~UDPServerSocketWindows(void)
{
}

UDPServerSocketWindows::UDPServerSocketWindows(const UDPServerSocketWindows &other)
{
  this->_socket = other._socket;
  this->_selector = other._selector;
  this->_host = other._host;
  this->_port = other._port;
  this->_error = other._error;
  this->_canread = other._canread;
  this->_canwrite = other._canwrite;
}

UDPServerSocketWindows& UDPServerSocketWindows::operator=(const UDPServerSocketWindows &other)
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

bool		UDPServerSocketWindows::SNCreate(std::string const &host, int port)
{
	WSADATA		startupdata;
	struct sockaddr_in server;

	this->_host = host;
	this->_port = port;
	if (WSAStartup(MAKEWORD(2, 2), &startupdata) != 0)
	{
		this->_error = WSASTARTUP;
		return (false);
	}
	if ((this->_socket = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP,
		NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET)
	{
		this->_error = SOCKETCREAT;
		return (false);
	}
	server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(this->_port);
	if (bind(this->_socket, (const sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		this->_error = ALREADYBIND;
		return (false);
	}
	this->_error = NOERRORSOCKET;
	return (true);
}

int		UDPServerSocketWindows::SNRead(char *msg, unsigned int size)
{
	WSABUF DataBuf;
	DWORD BytesReceived;
	DWORD Flags = 0;
	int structsize;

	structsize = sizeof(this->_daddr);
	DataBuf.len = size;
	DataBuf.buf = (msg);
	if (WSARecvFrom(this->_socket, &DataBuf, 1, &BytesReceived, &Flags, (SOCKADDR *)&(this->_daddr), &structsize, NULL, NULL) == SOCKET_ERROR)
	{
		this->_error = CANTREAD;
		return (-1);
	}
	this->_error = NOERRORSOCKET;
	return (BytesReceived);
}

int		UDPServerSocketWindows::SNWrite(const char *msg, unsigned int size)
{
	DWORD	SendBytes;
	WSABUF	DataBuf;

	DataBuf.buf = const_cast <char *> (msg);
	DataBuf.len = size;
	if (WSASendTo(this->_socket, &DataBuf, 1, &SendBytes, 0, (SOCKADDR *)&(this->_daddr), sizeof(this->_daddr), NULL, NULL) == SOCKET_ERROR)
	{
		this->_error = CANTWRITE;
	}
	this->_error = NOERRORSOCKET;
	return (SendBytes);
}

int				UDPServerSocketWindows::SNReadClient(char *msg, unsigned int size, std::string &ip)
{
	WSABUF DataBuf;
	DWORD BytesReceived;
	DWORD Flags = 0;
	int structsize;
	char *str = new char[50];

	structsize = sizeof(this->_daddr);
	DataBuf.len = size;
	DataBuf.buf = (msg);
	if (WSARecvFrom(this->_socket, &DataBuf, 1, &BytesReceived, &Flags, (SOCKADDR *)&(this->_daddr), &structsize, NULL, NULL) == SOCKET_ERROR)
	{
		this->_error = CANTREAD;
		return (-1);
	}
	this->_error = NOERRORSOCKET;
	InetNtop(AF_INET, (void *)&(this->_daddr.sin_addr), reinterpret_cast<PSTR>(str), 49);
	ip = str;
	return (BytesReceived);
}

int				UDPServerSocketWindows::SNWriteClients(const char *msg, unsigned int size)
{
	std::map<std::string, struct sockaddr_in *>::iterator it;
	DWORD	SendBytes;
	WSABUF	DataBuf;
	int client = 0;

	DataBuf.buf = const_cast <char *> (msg);
	DataBuf.len = size;
	struct sockaddr_in *clientinfo = NULL;

	for (it = this->_contactMap.begin(); it != this->_contactMap.end(); ++it)
	{
		clientinfo = it->second;
		if (clientinfo == NULL)
			continue;
		if (WSASendTo(this->_socket, &DataBuf, 1, &SendBytes, 0, ((SOCKADDR *)clientinfo), sizeof(this->_daddr), NULL, NULL) == SOCKET_ERROR)
		{
			this->_error = CANTWRITE;
		}
		else
			client++;
		this->_error = NOERRORSOCKET;
	}
	return (client);
}

int				UDPServerSocketWindows::SNWriteToClient(const char *msg, unsigned int size, const std::string &ip)
{
	struct sockaddr_in c_addr;
	DWORD	SendBytes;
	WSABUF	DataBuf;

	DataBuf.buf = const_cast <char *> (msg);
	DataBuf.len = size;
	c_addr.sin_family = AF_INET;
	c_addr.sin_port = this->_port;
	c_addr.sin_addr.s_addr = inet_addr(ip.c_str());
	if (WSASendTo(this->_socket, &DataBuf, 1, &SendBytes, 0, ((SOCKADDR *)&c_addr), sizeof((c_addr)), NULL, NULL) == SOCKET_ERROR)
		{
			this->_error = CANTWRITE;
		}
	else
	  this->_error = NOERRORSOCKET;
	return (SendBytes);
}


bool		UDPServerSocketWindows::SNClose(void)
{
	if (closesocket(this->_socket) == SOCKET_ERROR)
		return (false);
	if (WSACleanup() == SOCKET_ERROR)
		return (false);
	return (true);
}

std::string		UDPServerSocketWindows::getHost(void) const
{
	return (this->_host);
}

int			UDPServerSocketWindows::getPort(void) const
{
	return (this->_port);
}

eSocketErr	UDPServerSocketWindows::SNGetLastErr(void) const
{
	return (this->_error);
}

bool		UDPServerSocketWindows::SNAddRead(void)
{
  if (this->_selector)
    {
      static_cast <Selector<SOCKET> *>(this->_selector)->SNAddRead(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		UDPServerSocketWindows::SNAddWrite(void)
{
  if (this->_selector)
    {
      static_cast <Selector<SOCKET> *>(this->_selector)->SNAddWrite(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		UDPServerSocketWindows::SNDelRead(void)
{
  if (this->_selector)
    {
      static_cast <Selector<SOCKET> *>(this->_selector)->SNDelRead(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		UDPServerSocketWindows::SNDelWrite(void)
{
 if (this->_selector)
    {
      static_cast <Selector<SOCKET> *>(this->_selector)->SNDelWrite(this->_socket, this);
      return (true);
    }
  return (false);
}

void		UDPServerSocketWindows::SNSetRead(bool s)
{
	this->_canread = s;
}

void		UDPServerSocketWindows::SNSetWrite(bool s)
{
	this->_canwrite = s;
}

bool		UDPServerSocketWindows::SNGetRead(void) const
{
	return (this->_canread);
}

bool		UDPServerSocketWindows::SNGetWrite(void) const
{
	return (this->_canwrite);
}

char*		UDPServerSocketWindows::getIp(void) const
{
  return (NULL);
}
