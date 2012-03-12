
#ifndef		NETWORK_H_
# define	NETWORK_H_

namespace zia {

  class		ANetwork {

/* ************************************************************************* */
/*                             Attributes                                    */
/* ************************************************************************* */
    template <typename T>
    std::function<T> load(std::string const &symbol_name) {
      return std::function<T>(reinterpret_cast<T*>(load(symbol_name)));

 protected:
    void	(*onNewClient)(void);
    void	(*onClientLeave)(void);
    void	(*onClientRequest)(void);

/* ************************************************************************* */
/*                             Constructor                                   */
/* ************************************************************************* */
  protected:
    ANetwork(void (*onNewClient)(void) = 0,
	     void (*onClientLeave)(void) = 0,
	     void (*onClientRequest)(void) = 0)
      : onNewClient(onNewClient),
	onClientLeave(onClientLeave),
	onClientRequest(onClientRequest) {
    }

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */

    // open server network
    // return false on failure, true otherwise
    virtual bool	openConnection(int port = 0) = 0;

    // close connection
    // On failure, just warn, never fail with error
    virtual void	closeConnection(void) = 0;

    // return true if the server is connected,
    // false otherwise
    virtual bool	isConnected(void) = 0;
  };

}

#endif		// !NETWORK_H_
