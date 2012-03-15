/*
 * IModule.h for zia
 * by lepage_b
 * modified by 
 */

#ifndef		NETWORK_H_
# define	NETWORK_H_

namespace zia {
  namespace network {

    class	IClient {
      virtual ~IClient() {};
    };

    class	INetwork {
      virtual ~INetwork() {};

     protected:
      // open server network
      // return false on failure, true otherwise
      virtual bool	openConnection(int port = 0) = 0;
      
      // close server network
      virtual void	closeConnection(void) = 0;
      
      // return true if the server is connected,
      // false otherwise
      virtual bool	isConnected(void) = 0;

      // Called when a client connect to the server
      virtual void	onNewClient(void) = 0;

      // Called when a client disconnect
      virtual void	onClientLeave(void) = 0;

      // Called when a client has something to read
      virtual void	onClientRequest(void) = 0;
    };
    
  }
}  
#endif		// !NETWORK_H_
