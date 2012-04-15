/*
 * baseexcept.cpp for zia
 * by lenorm_f
 */

#include "baseexcept.hpp"

BaseExcept::BaseExcept(std::string const &s) {
	_error = s;
}

BaseExcept::BaseExcept(std::initializer_list<std::string> l) {
	int n;

	n = 0;
	for (auto i = begin(l); i != end(l); ++i, ++n) {
		if (n > 0)
			_error += " ";
		_error += *i;
	}
}

char const *BaseExcept::what() const throw() {
	return _error.c_str();
}
