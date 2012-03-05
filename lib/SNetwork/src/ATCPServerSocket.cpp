#include <iostream>
#include <string>
#include "ISocket.h"
#include "ATCPServerSocket.h"

ATCPServerSocket::ATCPServerSocket(void) :
	_host("127.0.0.1"), _port(4241)
{
}

ATCPServerSocket::~ATCPServerSocket(void)
{
}

std::string		ATCPServerSocket::getHost(void) const
{
	return (this->_host);
}

int				ATCPServerSocket::getPort(void) const
{
	return (this->_port);
}
