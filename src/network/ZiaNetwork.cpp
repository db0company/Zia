
#include		"ZiaNetwork.hpp"

#include		"Selector.hpp"

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
      std::cerr << "Error: Can't Create Listener Socket on port " << port << std::endl;
      return false;
    }
  std::cout << "Server Listening on port " << port << std::endl;
  if (!this->listener->SNListen()) {
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

void				ZiaNetwork::onNewClient(void)
{

}

void				ZiaNetwork::onClientLeave(void)
{

}

void				ZiaNetwork::onClientRequest(void)
{

}

/* ************************************************************************* */
/*                           Private Tools                                   */
/* ************************************************************************* */

void				ZiaNetwork::run(void) {
  // todo: this must be in a thread!

  while (true) {
      this->listener->SNAddRead();
      if (!this->selector->SNSelect()) {
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
      std::cout << "New connection";
      if (newClient->getIp())
	std::cout << " from " << newClient->getIp();
      std::cout << std::endl;
      this->addClient(newClient);
    }
}

void				ZiaNetwork::readFromClients(void) {
  std::list<ISocket *>::iterator	it;

  for (it = this->clients.begin(); it != this->clients.end(); ++it)
    if (!(this->readFromClient(*it)))
      it = this->clients.begin();
  //  for_each(this->clients.begin(), this->clients.end(), bind(&ZiaNetwork::readFromClient, _1));

}

bool				ZiaNetwork::readFromClient(ISocket * socket) {
  if (socket && socket->SNGetRead() == true)
    {
      char           buff[512] = {0};
      if (socket->SNRead(buff, 514) <= 0)
	return (this->delClient(socket));
      else
	{
	  this->onNewClient();
	  std::cout << socket->getIp() << ": " << buff << std::endl;
	}
    }
  return (true);
}

void				ZiaNetwork::addClient(ATCPClientSocket * socket) {
  if (!socket->getIp()) {
      std::cerr << "Error: Can't resolve client ip adress" << std::endl;
      return ;
    }
  std::cout << "Info: Client "<< socket->getIp() << " added to list"  << std::endl;
  this->clients.push_front(socket);
  this->onNewClient();
}

bool				ZiaNetwork::delClient(ISocket * socket)
{
  this->onClientLeave();
  std::cout << "Client leave..." << socket->getIp() << std::endl;
  this->clients.remove(socket);
  return (false);
}
