/*
 * IModule.h for zia
 * by becker_g
 */

#ifndef		IMODULE_H__
# define	IMODULE_H__

# include	<string>

# include	"dll.hpp"

namespace zia
{
	class		IModule
	{
	public :
		virtual ~IModule() {}

		virtual void	load(zia::filesystem::dll::AHandler *) = 0;
		virtual void	unload() = 0;
		virtual bool	supportedMethod(const zia::http::method&) = 0;
		virtual bool	answer(const zia::http::method&, zia::http::IRequest *) = 0;
	};
}
#endif		//!IMODULE_H__