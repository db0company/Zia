#include "AUDPServerSocket.h"

AUDPServerSocket::AUDPServerSocket()
{
}

AUDPServerSocket::~AUDPServerSocket(void)
{
}

bool				AUDPServerSocket::SNAddClient(std::string const &ip, int port)
{
	struct sockaddr_in *addr;

	if (this->_contactMap.find(ip) != this->_contactMap.end())
		return (false);
	addr = new sockaddr_in;
	addr->sin_family = AF_INET;
	addr->sin_port = port;
	addr->sin_addr.s_addr = inet_addr(ip.c_str());
	this->_contactMap[ip] = addr;
	return (true);
}

bool				AUDPServerSocket::SNDelClient(std::string const &ip)
{
	if (this->_contactMap.empty() || (this->_contactMap.find(ip) == this->_contactMap.end()))
		return (false);
	this->_contactMap.erase(ip);
	return (true);
}
