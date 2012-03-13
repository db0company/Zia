
#ifndef		NETWORK_H_
# define	NETWORK_H_

namespace zia {
  namespace network {

    class	IClient {
    };

    class	ANetwork {

    protected:
      std::list<IClient *>	clients;

    protected:
      void	(*onNewClient)(IClient *);
      void	(*onClientLeave)(IClient *);
      void	(*onClientRequest)(IClient *);

    protected:
      ANetwork(void (*onNewClient)(void) = 0,
	       void (*onClientLeave)(void) = 0,
	       void (*onClientRequest)(void) = 0)
	: onNewClient(onNewClient),
	  onClientLeave(onClientLeave),
	  onClientRequest(onClientRequest) {
      }

      // open server network
      // return false on failure, true otherwise
      virtual bool	openConnection(int port = 0) = 0;
      
      // close server network
      virtual void	closeConnection(void) = 0;
      
      // return true if the server is connected,
      // false otherwise
      virtual bool	isConnected(void) = 0;
    };
    
  }
}  
#endif		// !NETWORK_H_
