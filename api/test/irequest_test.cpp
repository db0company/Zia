/*
 * irequest_test.cpp for zia
 * by lenorm_f
 */

#include <irequest.hpp>
#include "request.hpp"
#include "testexcept.hpp"

using namespace zia::http;

#define N_TESTS 1
#define TEST_NAME "irequest"

int irequest_test() {
	IRequest *req = new Request();

	// Test failed: throw an exception containing the name of the test and
	// a reason for failing
	//throw TestExcept(TEST_NAME, {"Test error"});

	// Return the number of tests passed
	return N_TESTS;
}
