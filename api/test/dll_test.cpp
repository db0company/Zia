/*
 * dll_test.cpp for zia
 * by lenorm_f
 */

#include <dlfcn.h>
#include <dll.hpp>
#include "testexcept.hpp"

using namespace zia::filesystem;

#define N_TESTS 1
#define TEST_NAME "dll"

class Handler : public dll::AHandler {
	void *_handler;
	std::string _name;

	public:
	Handler(void *handler, std::string const &dl_name) {
		_handler = handler;
		_name = dl_name;
	}
	~Handler() {}

	void *getHandler() const {
		return _handler;
	}

	std::string const &getName() const {
		return _name;
	}

	void *load(std::string const &symbol_name) {
		return ::dlsym(_handler, symbol_name.c_str());
	}
};

dll::AHandler *dll::load(std::string const &dl_name, eResType res_type) {
	void *handler;

	handler = ::dlopen(dl_name.c_str(), res_type == RES_LAZY ? RTLD_LAZY : RTLD_NOW);
	ASSERT(handler != 0, "Unable to open dl ", dl_name.c_str(), ": ", ::dlerror());

	return new Handler(handler, dl_name);
}

void dll::unload(AHandler *handler) {
	ASSERT(handler != 0, "NULL handler on dl unload");

	::dlclose(handler->getHandler());
}

int dll_test() {
	std::string dl_path("/lib/libc-2.15.so");
	dll::AHandler *handler = dll::load(dl_path, dll::eResType::RES_LAZY);
	std::function<int(char const*)> f = handler->load<int(char const*)>("puts");

	f("dll_test");

	dll::unload(handler);

	return N_TESTS;
}
