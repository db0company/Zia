/*
 * irequest_test.cpp for zia
 * by lenorm_f
 */

#include <iostream>
#include "request.hpp"
#include "request_parser.hpp"
#include "testexcept.hpp"

using namespace zia::http;

// Always define those if you want to use the ASSERT macro
#define N_TESTS 1
#define TEST_NAME "irequest"

int irequest_test() {
	std::string buf = std::string("GET /index.php HTTP/1.1\r\n"
				      "Host: localhost\r\n"
				      "Connection: close\r\n");
	/*IRequest<std::string> *req = request_parser<std::string>::unmarshal(buf);

	std::cout << req->getMethod() << " "
		<< req->getURI() << " "
		<< req->getVersion() << std::endl;*/

	// Test failed: throw an exception containing the name of the test and
	// a reason for failing
	//throw TestExcept(TEST_NAME, {"Test error"});

	// Return the number of tests passed
	return N_TESTS;
}
