#ifndef __TCP_SERVER_SOCKET_WINDOWS_HH__
#define __TCP_SERVER_SOCKET_WINDOWS_HH__

#include <iostream>
#include <string>
#include <winsock2.h>
#include "ISocket.h"
#include "ATCPServerSocket.h"
#include "ATCPClientSocket.h"
#include "TCPClientSocketWindows.h"

class 	TCPServerSocketWindows : public ATCPServerSocket
{
 private:
  TCPServerSocketWindows(void);
public:
  TCPServerSocketWindows(ISelector *);
  virtual ~TCPServerSocketWindows();
  TCPServerSocketWindows(const TCPServerSocketWindows &other);
  TCPServerSocketWindows& operator=(const TCPServerSocketWindows &other);
  virtual bool				SNCreate(std::string const &host, int port);
  virtual int				SNRead(char *msg, unsigned int size);
  virtual int				SNWrite(const char *msg, unsigned int size);
  virtual bool				SNListen(void);
  virtual TCPClientSocketWindows		*SNAccept(void);
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
  virtual char *			getIp(void) const;
protected:
  ISelector				*_selector;
  SOCKET					_socket;
  eSocketErr				_error;
  bool					_canread;
  bool					_canwrite;
};


#endif //__TCP_SERVER_SOCKET_WINDOWS_HH__
