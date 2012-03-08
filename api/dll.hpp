/*
 * dll.hpp for zia
 * by lenorm_f
 */

#ifndef __DLL_H__
#define __DLL_H__

#include <string>
#include <functional>

namespace zia { namespace filesystem {
	class dll {
		public:
		enum eResType {
			RES_UNKNOWN = -1,
			RES_LAZY = 0,
			RES_NOW,
		};

		class AHandler {
			public:
			virtual ~AHandler() {}

			virtual void *getHandler() const = 0;

			virtual std::string const &getName() const = 0;

			virtual void *load(std::string const &symbol_name) = 0;
			template <typename T>
			std::function<T> load(std::string const &symbol_name) {
				return std::function<T>(reinterpret_cast<T*>(load(symbol_name)));
			}
		};

		public:
		static AHandler *load(std::string const &dl_name, eResType symbols_resolution = RES_LAZY);
		static void unload(AHandler*);
	};
}}

#endif
