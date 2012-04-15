
#include		"ZiaNetwork.hpp"

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "http/HttpRequestParser.hpp"
#include "http/HttpLiterals.hpp"
#include "http/HttpUtils.hpp"
#include		"Selector.hpp"
#include		"debug.h"

/* ************************************************************************* */
/*                             Coplian Form                                  */
/* ************************************************************************* */

ZiaNetwork::ZiaNetwork(void)
  : selector(), listener(), connection(false) {
#ifndef WIN32
  this->selector = new Selector<int>;
  this->listener = new TCPServerSocketUnix(this->selector);
#else
  this->selector = new Selector<SOCKET>;
  this->listener = new TCPServerSocketWindows(this->selector);
#endif
}

ZiaNetwork::ZiaNetwork(ZiaNetwork const & other)
  : selector(other.selector), listener(other.listener),
    connection(other.connection) {
}

ZiaNetwork &		ZiaNetwork::operator=(ZiaNetwork const & other) {
    if (&other != this) {
      //this->onNewClient = other.onNewClient;
      //this->onClientLeave = other.onClientLeave;
      //this->onClientRequest = other.onClientRequest;

      this->selector = other.selector;
      this->listener = other.listener;
      this->connection = other.connection;
      
      // If there is a pointer to something allocated, do this :
      // if (this->SomeThingAllocated)
      //   delete this->SomeThingAllocated;
      // this->SomeThingAllocated = CopyFunc(other.SomeThingAllocated);
    }
  return *this;
}

ZiaNetwork::~ZiaNetwork(void) {
}

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */

bool				ZiaNetwork::openConnection(int port) {
  if (!(this->listener->SNCreate(SERV_ADDR, port))) {
    if (v)
      std::cerr << "Error: Can't Create Listener Socket on port " << port << std::endl;
    return false;
  }
  if (v)
    std::cout << "Server Listening on port " << port << std::endl;
  if (!this->listener->SNListen()) {
    if (v)
      std::cerr << "Error: Can't listen on socket" << std::endl;
    return false;
  }
  this->listener->SNAddRead();
  this->run();
  return true;
}

void				ZiaNetwork::closeConnection(void) {
  
}

bool				ZiaNetwork::isConnected(void) {
  return this->connection;
}

void				ZiaNetwork::onNewClient(void) {

}

void				ZiaNetwork::onClientLeave(void) {

}

void				ZiaNetwork::onClientRequest(ISocket * client,
							    std::string const & request) {
  if (v)
    std::cout << client->getIp() << ": " << request << std::endl;
  http::HttpRequestParser reqp;
  bref::HttpRequest req = reqp.forge(request);
  std::cout << req << std::endl;
}

/* ************************************************************************* */
/*                           Private Tools                                   */
/* ************************************************************************* */

void				ZiaNetwork::run(void) {
  // todo: this must be in a thread!

  while (true) {
      this->listener->SNAddRead();
     if (!this->selector->SNSelect()) {
       if (v)
	 std::cerr << "Error: Select" << std::endl;
       return ;
     }
     this->getNewClient();
     this->readFromClients();
  }
}

void				ZiaNetwork::getNewClient(void) {
  if (this->listener->SNGetRead()) {
      ATCPClientSocket *newClient = NULL;
      if ((newClient = this->listener->SNAccept()) == false)
	return ;
      newClient->SNAddRead();
      newClient->SNAddWrite();
      if (v)
	std::cout << "New connection";
      if (v && newClient->getIp())
	std::cout << " from " << newClient->getIp();
      if (v)
	std::cout << std::endl;
      this->addClient(newClient);
    }
}

void				ZiaNetwork::readFromClients(void) {
  std::list<ISocket *>::iterator	it;

  for (it = this->clients.begin(); it != this->clients.end(); ++it)
    if (!(this->readFromClient(*it)))
      it = this->clients.begin();
}

bool				ZiaNetwork::readFromClient(ISocket * socket) {
  if (socket && socket->SNGetRead() == true)
    {
      char           buff[4096] = {0};
      int	     red = 0;
      if ((red = socket->SNRead(buff, 4095)) <= 0)
	return this->delClient(socket);
      else
	{
	  buff[red + 1] = '\0';
	  this->onClientRequest(socket, buff);
	}
    }
  return true;
}

void				ZiaNetwork::addClient(ATCPClientSocket * socket) {
  if (!socket->getIp()) {
    if (v)
      std::cerr << "Error: Can't resolve client ip adress" << std::endl;
    return ;
  }
  if (v)
    std::cout << "Info: Client "<< socket->getIp() << " added to list"  << std::endl;
  this->clients.push_front(socket);
  this->onNewClient();
}

bool				ZiaNetwork::delClient(ISocket * socket) {
  this->onClientLeave();
  if (v)
    std::cout << "Client leave..." << socket->getIp() << std::endl;
  this->clients.remove(socket);
  return false;
}
