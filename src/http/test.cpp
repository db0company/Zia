/*
 * test.cpp for Zia
 * by lenorm_f
 */

// g++ -Wall -Wextra -I../../bref-api/include/bref test.cpp HttpRequest.cpp HttpResponse.cpp

#include <iostream>
#include <HttpRequest.h>
#include <HttpResponse.h>

template <typename T>
std::string to_string(T const&) {
	return std::string();
}

template <>
std::string to_string(bref::Buffer const &buffer) {
	std::string s;

	bref::Buffer::const_iterator it;
	for (it = buffer.begin(); it != buffer.end(); ++it)
		s += *it;

	return s;
}

int main() {
	bref::HttpRequest req;
	bref::HttpResponse rep;

	req.setVersion(bref::Version(1, 1));
	req.setUri("/index.php");
	req.setMethod(bref::request_methods::Get);

	std::cout << "Request: " << static_cast<int>(req.getMethod())
		<< " " << req.getUri()
		<< " HTTP/" << req.getVersion().Major
		<< "." << req.getVersion().Minor
		<< std::endl;

	rep.setVersion(bref::Version(1, 1));
	rep.setStatus(bref::status_codes::OK);
	rep.setReason("Oui.");

	std::cout << "Response: " << to_string(rep.getRawData())
		<< std::endl;
}
