/*
 * IModule.h for zia
 * by becker_g
 * modified by lepage_b
 */

#ifndef		IMODULE_H__
# define	IMODULE_H__

# include	<string>

# include	"dll.hpp"

namespace zia {
  class		IModule  {

  public:
    virtual ~IModule() {}

    //		DYNAMIC LIBRARY FUNCTIONS		//

    // Load a dynamic library corresponding to the module implementation :
    // see api/dll.hpp for further explanations about the AHandler type
    virtual void	load(zia::filesystem::dll::AHandler *) = 0;

    // Unload the loaded dynamic library
    virtual void	unload(void) = 0;

    //			TOOLS				//

    // Return true if the method given as the 1st parameter is overloaded by the
    // module
    virtual bool	supportedMethod(const zia::http::method &) = 0;


    //		MODULES INTERACTIONS STEP BY STEP		//

    // Called when the module is loaded
    // return true if the module must be used,
    // false otherwise
    virtual bool		onModuleLoad(void) = 0;
    // Called when the module is unload
    virtual void		onModuleUnLoad(void) = 0;
    
    // Called on a new connection from a client
    virtual void		onClientConnection(IClient *) = 0;
    // Called when a client disconnect
    virtual void		onClientDisconnection(IClient *) = 0;

    // Called before the header is read (empty request)
    virtual void		beforeReadHeader(zia::http::IRequest *) = 0;

    // Called after the header is read (request is filled with header infos only)
    virtual void		afterReadHeader(zia::http::IRequest *) = 0;

    // Called before the content is read (request is filled with the header infos only)
    virtual void		beforeReadContent(zia::http::IRequest *) = 0;

    // Called before the content is read (request is filled with the header infos only)
    virtual void		afterReadContent(zia::http::IRequest *) = 0;

    // Called when the method must be executed
    // return true if the module is executing this method all
    // by itself (in this case, the core server must NOT execute
    // anything else for this method), false otherwise
    virtual bool		letMeDoThisMethod(const zia::http::method &) = 0;

    // Called before the executin of the method
    // execute something before the default behavior
    virtual void		execBeforeMethod(const zia::http::method &,
						 zia::http::IRequest *) = 0;

    // Called after the execution of the method
    // execute something after the default behavior
    virtual void		execAfterMethod(const zia::http::method &,
						zia::http::IRequest *) = 0;
    
    // Called when the answer is forge
    // return a complete answer if the module is forging the
    // answer all by itself, a NULL pointer otherwise
    virtual const IRequest *	letMeDoTheAnswer(void) = 0;

    // Called after the answer is forged and modify it or not
    virtual void		modifyAnswer(IRequest *) = 0;
  };
}

#endif		//!IMODULE_H__
