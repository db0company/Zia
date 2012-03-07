#ifndef		IMODULE_H__
# define	IMODULE_H__

#include	<string>

class		IModule
{
public :
	virtual IModule&	operator=(const IModule&) = 0;


/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */
	virtual void	load() = 0;
	virtual void	loadMethod(const std::string&) = 0;
	virtual void	unloadMethod(const std::string&) = 0;

	virtual	bool	enable() = 0;
	virtual	bool	disable() = 0;
};

#endif		//!IMODULE_H__