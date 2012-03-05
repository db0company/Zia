#ifndef __ISocket__
#define __ISocket__

#include <iostream>
#include <string>

#define SERV_ADDR "127.0.0.1"

enum	eSocketErr
  {
    SOCKETCREAT,
    CONNECTIONLOST,
    CANTWRITE,
    CANTREAD,
    ALREADYBIND,
    ALREADY_READ,
    ALREADY_WRITE,
    CANTGETHOST,
    CONNECTIONERR,
    CLOSEERR,
    CANTACCEPT,
    CANTLISTEN,
	WSASTARTUP,
    NOERRORSOCKET
  };

class 	ISocket
{
public:
  virtual ~ISocket(){}
  virtual bool		SNCreate(std::string const &host, int port) = 0;
  virtual int		SNRead(char *msg, unsigned int size) = 0;
  virtual int		SNWrite(const char *msg, unsigned int size) = 0;
  virtual bool		SNClose(void) = 0;
  virtual eSocketErr	SNGetLastErr(void) const = 0;

  virtual bool		SNAddRead(void) = 0;
  virtual bool		SNAddWrite(void) = 0;
  virtual bool		SNDelRead(void) = 0;
  virtual bool		SNDelWrite(void) = 0;

  virtual void		SNSetRead(bool) = 0;
  virtual void		SNSetWrite(bool) = 0;
  virtual bool		SNGetRead(void) const = 0;
  virtual bool		SNGetWrite(void) const = 0;

  virtual char		*getIp(void) const = 0;
};

#endif //__ISocket__
