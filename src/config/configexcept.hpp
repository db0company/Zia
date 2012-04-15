#ifndef __CONFIGEXCEPT_H__
#define __CONFIGEXCEPT_H__

#include "baseexcept.hpp"

class ConfigExcept : public BaseExcept {
	public:
	ConfigExcept(std::initializer_list<std::string> l) :
		BaseExcept(l) {}
};

#endif
