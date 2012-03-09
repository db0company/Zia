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
	/* ************************************************************************* */
	/*                             Member Functions                              */
	/* ************************************************************************* */
		virtual void	connection() = 0;
		virtual void	deconnexion() = 0;
		virtual void	load(zia::filesystem::dll::AHandler *) = 0;
		virtual void	unload() = 0;
		virtual void	loadMethod(const zia::http::method&) = 0;
		virtual void	unloadMethod(const zia::http::method&) = 0;
		virtual void	answer(const zia::http::method&) = 0;
		virtual void	send() = 0;
	};
}
#endif		//!IMODULE_H__