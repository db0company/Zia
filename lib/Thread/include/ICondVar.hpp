
#ifndef		__ICONDVAR_HPP__
# define	__ICONDVAR_HPP__

class		ICondVar
{
public:
  virtual bool	wait() = 0;
  virtual void	signal() = 0;
  virtual void	broadcast() = 0;
};

#endif		/*__ICONDVAR_HPP__*/
