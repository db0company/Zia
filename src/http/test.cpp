/*
 * test.cpp for Zia
 * by lenorm_f
 */

// g++ -std=c++0x -Wall -Wextra -I../../bref-api/include/bref *.cpp ../config/BrefValue.cpp

#include <iostream>
#include <HttpRequest.h>
#include <HttpResponse.h>
#include "HttpResponseParser.hpp"
#include "HttpUtils.hpp"

// Important: call this function
namespace http {
	void init_literals();
}

std::ostream &operator<<(std::ostream &os, bref::HttpRequest const &req) {
	os << "Request: " << static_cast<int>(req.getMethod())
		<< " " << req.getUri()
		<< " HTTP/" << req.getVersion().Major
		<< "." << req.getVersion().Minor;

	return os;
}

std::ostream &operator<<(std::ostream &os, bref::HttpResponse const &rep) {
	os << "Response: " << http::util::to_string(rep.getRawData());

	return os;
}

int main() {
	bref::HttpRequest req;
	bref::HttpResponse rep;
	http::HttpResponseParser repp;

	http::init_literals();

	req.setVersion(bref::Version(1, 1));
	req.setUri("/index.php");
	req.setMethod(bref::request_methods::Get);

	bref::BrefValueList vl{
		std::string("meow~"),
		std::string("qwerty"),
	};
	bref::BrefValueArray va{
		{std::string("a"), std::string("1")},
		{std::string("b"), std::string("2")},
	};

	rep.setVersion(bref::Version(1, 1));
	rep.setStatus(bref::status_codes::OK);
	rep.setReason("Oui.");
	rep["Connection"] = bref::BrefValue(std::string("Close"));
	rep["X-Powered-By"] = vl;
	rep["Random"] = va;

	std::cout << req << std::endl
		<< rep << std::endl;

	std::cout << repp.forge(rep.getRawData()) << std::endl;
}
