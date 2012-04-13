
#ifndef				ZIANETWORK_H_
# define			ZIANETWORK_H_

# include			<list>
# include			<algorithm>

# include			"v.h"
# include			"conf.h"

# ifdef _WIN32
#  include			"TCPServerSocketWindows.h"
# else
#  include			"TCPServerSocketUnix.h"
# endif

class				ZiaNetwork
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
  void			onNewClient(void);
  void			onClientLeave(void);
  void			onClientRequest(ISocket *, std::string const &);

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

