/*
 * baseexcept.hpp for zia
 * by lenorm_f
 */

#ifndef __BASEEXCEPT_H__
#define __BASEEXCEPT_H__

#include <string>
#include <stdexcept>

class BaseExcept : std::exception {
	BaseExcept();

	std::string _error;

	public:
	BaseExcept(std::string const&);
	BaseExcept(std::initializer_list<std::string>);
	virtual ~BaseExcept() throw() {}

	char const *what() const throw();
};

#endif
