
#ifndef				ZIANETWORK_H_
# define			ZIANETWORK_H_

# include			<list>
# include			<algorithm>
# include			<boost/bind.hpp>

# include			"conf.h"
# include			"network.hpp"

# ifdef _WIN32
#  intclude			"TCPServerSocketWindows.h"
# else
#  include			"TCPServerSocketUnix.h"
# endif

class				ZiaNetwork : public zia::ANetwork
{

/* ************************************************************************* */
/*                             Attributes                                    */
/* ************************************************************************* */
 private:
  ISelector *			selector;
  ATCPServerSocket *		listener;
  bool				connection;
  std::list<ISocket *>		clients;

/* ************************************************************************* */
/*                             Coplian Form                                  */
/* ************************************************************************* */
 public:
  ZiaNetwork(void);
  ZiaNetwork(ZiaNetwork const &);
  ZiaNetwork &			operator=(ZiaNetwork const &);
  ~ZiaNetwork(void);

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */
 public:
  bool			openConnection(int port = CONF_DEFAULT_PORT);
  void			closeConnection(void);
  bool			isConnected(void);

/* ************************************************************************* */
/*                           Private Tools                                   */
/* ************************************************************************* */
 private:
  void			run(void);
  void			getNewClient(void);
  void			readFromClients(void);
  bool			readFromClient(ISocket *);
  void			addClient(ATCPClientSocket *);
  bool			delClient(ISocket *);
};

#endif				// !ZIANETWORK_H_

