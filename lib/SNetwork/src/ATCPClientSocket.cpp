#include <iostream>
#include <string>
#include "ISocket.h"
#include "ATCPClientSocket.h"

ATCPClientSocket::ATCPClientSocket() :
	_host("127.0.0.1"), _port(4241)
{
}

ATCPClientSocket::~ATCPClientSocket()
{
}

std::string		ATCPClientSocket::getHost(void) const
{
	return (this->_host);
}

int			ATCPClientSocket::getPort(void) const
{
	return (this->_port);
}
