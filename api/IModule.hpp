/*
 * IModule.h for zia
 * by becker_g
 */

#ifndef		IMODULE_H__
# define	IMODULE_H__

# include	<string>

# include	"dll.hpp"

namespace zia {
  class		IModule  {
  public :

    virtual ~IModule() {}

    /* Load a dynamic library corresponding to the module implementation :
       see api/dll.hpp for further explanations about the AHandler type */
    virtual void	load(zia::filesystem::dll::AHandler *) = 0;

    /* Unload the loaded dynamic library */
    virtual void	unload(void) = 0;

    /* Return true if the method given as the 1st parameter is overloaded by the
       module */
    virtual bool	supportedMethod(const zia::http::method &) = 0;

    /* The answer method takes a IRequest * as the second parameter, it will
       include the answer provided by the module if necessary :
       return true if modified else false */
    virtual bool	answer(const zia::http::method &,
			       zia::http::IRequest *) = 0;
  };
}

#endif		//!IMODULE_H__
