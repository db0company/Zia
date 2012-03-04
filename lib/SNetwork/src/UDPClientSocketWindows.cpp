#include <winsock2.h>
#include "ISocket.h"
#include "ISelector.h"
#include "Selector.hpp"
#include "UDPClientSocketWindows.h"

UDPClientSocketWindows::UDPClientSocketWindows(void)
{
}

UDPClientSocketWindows::UDPClientSocketWindows(ISelector * s) :
	_selector(s), _canread(false), _canwrite(false), _port(12346), _host("127.0.0.1")
{
	this->_error = NOERRORSOCKET;
}

UDPClientSocketWindows::~UDPClientSocketWindows(void)
{
}

UDPClientSocketWindows::UDPClientSocketWindows(const UDPClientSocketWindows &other)
{
	this->_socket = other._socket;
	this->_error = other._error;
	this->_port = other._port;
	this->_host = other._host;
	this->_selector = other._selector;
	this->_canread = other._canread;
	this->_canwrite = other._canwrite;
}

UDPClientSocketWindows& UDPClientSocketWindows::operator=(const UDPClientSocketWindows &other)
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

bool		UDPClientSocketWindows::SNCreate(std::string const &host, int port)
{
	WSADATA		startupdata;

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
	this->_servaddr.sin_family = AF_INET;
	this->_servaddr.sin_port = htons(this->_port);
	this->_servaddr.sin_addr.s_addr = inet_addr(this->_host.c_str());
	this->_error = NOERRORSOCKET;
	return (true);
}

int		UDPClientSocketWindows::SNRead(char *msg, unsigned int size)
{
	WSABUF	DataBuff;
	DWORD	BytesReceived;
	struct sockaddr_in from;
	DWORD   Flags = 0;
	int	structsize;

	structsize = sizeof(from);
	DataBuff.buf = (msg);
	DataBuff.len = size;
	if (WSARecvFrom(this->_socket, &DataBuff, 1, &BytesReceived, &Flags, (SOCKADDR *)&(from), &structsize, NULL, NULL) == SOCKET_ERROR)
	//	if (WSARecvFrom(this->_socket, &DataBuff, 1, &BytesReceived, &Flags, (SOCKADDR *)&(from), &structsize, NULL, NULL) == SOCKET_ERROR)
	{
		this->_error = CANTREAD;
		return (-1);
	}
	this->_error = NOERRORSOCKET;
	return (BytesReceived);
}

int		UDPClientSocketWindows::SNWrite(const char *msg, unsigned int size)
{
	WSABUF	DataBuff;
	DWORD SendBytes;
	DWORD Flags = 0;

	DataBuff.buf = const_cast <char *> (msg);
	DataBuff.len = size;
	if (WSASendTo(this->_socket, &DataBuff, 1, &SendBytes, Flags, (SOCKADDR *)&(this->_servaddr), sizeof(this->_servaddr), NULL, NULL) == SOCKET_ERROR)
		{
			this->_error = CANTWRITE;
			return (-1);
		}
	this->_error = NOERRORSOCKET;
	return (SendBytes);
}

bool		UDPClientSocketWindows::SNClose(void)
{
	if (closesocket(this->_socket) == SOCKET_ERROR)
		return (false);
	if (WSACleanup() == SOCKET_ERROR)
		return (false);
	return (true);
}

char*			UDPClientSocketWindows::getIp(void) const
{
  return (NULL);
}

std::string		UDPClientSocketWindows::getHost(void) const
{
	return (this->_host);
}

int			UDPClientSocketWindows::getPort(void) const
{
	return (this->_port);
}

eSocketErr	UDPClientSocketWindows::SNGetLastErr(void) const
{
	return (this->_error);
}

bool		UDPClientSocketWindows::SNAddRead(void)
{
  if (this->_selector)
    {
      static_cast <Selector<SOCKET> *>(this->_selector)->SNAddRead(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		UDPClientSocketWindows::SNAddWrite(void)
{
  if (this->_selector)
    {
      static_cast <Selector<SOCKET> *>(this->_selector)->SNAddWrite(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		UDPClientSocketWindows::SNDelRead(void)
{
  if (this->_selector)
    {
      static_cast <Selector<SOCKET> *>(this->_selector)->SNDelRead(this->_socket, this);
      return (true);
    }
  return (false);
}

bool		UDPClientSocketWindows::SNDelWrite(void)
{
  if (this->_selector)
    {
      static_cast <Selector<SOCKET> *>(this->_selector)->SNDelWrite(this->_socket, this);
      return (true);
    }
  return (false);
}

void		UDPClientSocketWindows::SNSetRead(bool s)
{
	this->_canread = s;
}

void		UDPClientSocketWindows::SNSetWrite(bool s)
{
	this->_canwrite = s;
}

bool		UDPClientSocketWindows::SNGetRead(void) const
{
	return (this->_canread);
}

bool		UDPClientSocketWindows::SNGetWrite(void) const
{
	return (this->_canwrite);
}
