/*
 * IModuleManager.hpp for zia
 * by becker_g
 */

#ifndef		IMODULEMANAGER_H__
# define	IMODULEMANAGER_H__

# include	<list>
# include	<string>

# include	"dll.hpp"
# include	"IRequest.hpp"
# include	"IModule.hpp"

namespace zia {
	class IModuleManager {
	public:
	  virtual ~IModuleManager() {}

	  // Get the loaded modules list
	  virtual const std::list<const IModule *> & getModules(void) const = 0;

	  virtual const IModule *	loadModule(zia::filesystem::dll::AHandler *) = 0;
	  virtual const IModule *	unloadModule(const IModule *) = 0;

	  // Connect each module of the list given as first parameter
	  virtual const std::list<const IModule *> connectModules(const std::list<IModule *>&) = 0;

	  virtual bool isConnected(const IModule *) = 0;

	  // Disconnect each module of the list given as first parameter
	  virtual const std::list<const IModule *> disconnectModules(const std::list<IModule *>&) = 0;

	  virtual bool useMethod(const zia::http::method&) = 0;
	  virtual bool execMethod(const zia::http::IRequest *) = 0;
	  virtual const IRequest * getAnswer() = 0;
	};
}

#endif		//! MODULEMANAGER_H__
