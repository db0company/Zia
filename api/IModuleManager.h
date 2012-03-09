/*
 * IModuleManager.h for zia
 * by becker_g
 */

#ifndef		IMODULEMANAGER_H__
# define	IMODULEMANAGER_H__

# include	<list>
# include	<string>

# include	"dll.hpp"
# include	"IModule.h"

namespace zia
{
	class IModuleManager
	{
	public:
		virtual const IModuleManager * getInstance() = 0;

		virtual const std::list<const IModule *> & getModules() const = 0;

		virtual const IModule *	loadModule(const zia::filesystem::dll::AHandler *) = 0;
		virtual const IModule *	unloadModule(const IModule *) = 0;

		virtual std::list<const IModule *> connectModules(const std::list<IModule *>&) = 0;
		virtual bool isconnected(const IModule *) = 0;
		virtual std::list<const IModule *> disconnectModules(const std::list<IModule *>&) = 0;

		virtual bool useMethod(const zia::http::method&) = 0;
		virtual bool execMethod(const zia::http::IRequest *) = 0;
		virtual const IRequest& getAnswer() = 0;
	};
}
#endif		//! MODULEMANAGER_H__