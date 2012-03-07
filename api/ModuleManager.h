#ifndef		MODULEMANAGER_H__
# define	MODULEMANAGER_H__

# include	<map>

# include	"IModule.h"

class ModuleManager
{
/* ************************************************************************* */
/*                             Attributes                                    */
/* ************************************************************************* */
private:
	std::map<const char *, const IModule *>	_modules;

public:
/* ************************************************************************* */
/*                             Coplian Form                                  */
/* ************************************************************************* */
	ModuleManager(void);
	ModuleManager(const ModuleManager&);
	ModuleManager &	operator=(const ModuleManager&);
	~ModuleManager(void);


/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */
	void	addModule(const char *);
	void	deleteModule(const char *);
	void	
};

#endif		//! MODULEMANAGER_H__