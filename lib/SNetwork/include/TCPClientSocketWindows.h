#ifndef TCP_CLIENT_SOCKET_WINDOWS_HH__
#define TCP_CLIENT_SOCKET_WINDOWS_HH__

#include <winsock2.h>
#include "ISelector.h"
#include "ISocket.h"
#include "ATCPClientSocket.h"

class 	TCPClientSocketWindows : public ATCPClientSocket
{
 private:
  TCPClientSocketWindows(void);
 public:
  TCPClientSocketWindows(ISelector* _selector);
  virtual ~TCPClientSocketWindows(void);
  TCPClientSocketWindows(const TCPClientSocketWindows &other);
  TCPClientSocketWindows& operator=(const TCPClientSocketWindows &other);
  virtual bool		SNCreate(std::string const &host, int port);
  void			SNCreateAccept(SOCKET socket, struct sockaddr_in addr);
  virtual int		SNRead(char *msg, unsigned int size);
  virtual int		SNWrite(const char *msg, unsigned int size);
  virtual bool		SNConnect(void);
  virtual bool		SNClose(void);
  virtual eSocketErr	SNGetLastErr(void) const;

  virtual bool		SNAddRead(void);
  virtual bool		SNAddWrite(void);
  virtual bool		SNDelRead(void);
  virtual bool		SNDelWrite(void);

  virtual void		SNSetRead(bool);
  virtual void		SNSetWrite(bool);
  virtual bool		SNGetRead(void) const;
  virtual bool		SNGetWrite(void) const;

  virtual char *	getIp(void) const;
 private:
  ISelector		*_selector;
  SOCKET		_socket;
  eSocketErr		_error;
  bool			_canread;
  bool			_canwrite;
  struct sockaddr_in	_addr;
};

#endif  //TCP_CLIENT_SOCKET_WINDOWS_HH__
