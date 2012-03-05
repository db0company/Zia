#ifndef __TCP_SERVER_SOCKET_UNIX_HH__
#define __TCP_SERVER_SOCKET_UNIX_HH__

#include <iostream>
#include <string>
#include <stdint.h>
#include "ISocket.h"
#include "ATCPServerSocket.h"
#include "ATCPClientSocket.h"
#include "TCPClientSocketUnix.h"

class 	TCPServerSocketUnix : public ATCPServerSocket
{
 private:
  TCPServerSocketUnix(void);
public:
  TCPServerSocketUnix(ISelector *);
  virtual ~TCPServerSocketUnix();
  TCPServerSocketUnix(const TCPServerSocketUnix &other);
  TCPServerSocketUnix& operator=(const TCPServerSocketUnix &other);
  virtual bool				SNCreate(std::string const &host, int port);
  virtual int				SNRead(char *msg, uint32_t size);
  virtual int				SNWrite(const char *msg, uint32_t size);
  virtual bool				SNListen(void);
  virtual TCPClientSocketUnix		*SNAccept(void);
  virtual bool				SNClose(void);
  virtual eSocketErr			SNGetLastErr(void) const;

  virtual bool				SNAddRead(void);
  virtual bool				SNAddWrite(void);
  virtual bool				SNDelRead(void);
  virtual bool				SNDelWrite(void);

  virtual void				SNSetRead(bool);
  virtual void				SNSetWrite(bool);
  virtual bool				SNGetRead(void) const;
  virtual bool				SNGetWrite(void) const;

  virtual char				*getIp(void) const;
protected:
  ISelector				*_selector;
  int					_socket;
  eSocketErr				_error;
  bool					_canread;
  bool					_canwrite;
};


#endif //__TCP_SERVER_SOCKET_UNIX_HH__
