/*
 * testexcept.hpp for zia
 * by lenorm_f
 */

#ifndef __TESTEXCEPT_H__
#define __TESTEXCEPT_H__

#include <string>
#include <stdexcept>

#define ASSERT(x, s...) do {\
	if ((x) == false) throw TestExcept{TEST_NAME, { s }}; \
} while (0)

class TestExcept : public std::exception {
	std::string _tst;
	std::string _err;

	public:
	TestExcept(std::string test_name, std::initializer_list<std::string> i) {
		_tst = test_name;
		for (auto &s : i)
			_err += s;
	}

	virtual ~TestExcept() throw() {}

	virtual char const *testName() const {
		return _tst.c_str();
	}

	virtual char const *what() const throw() {
		return _err.c_str();
	}
};

#endif
