/*
 * test.cpp for Zia
 * by lenorm_f
 */

// g++ -std=c++0x -Wall -Wextra -I../../bref-api/include/bref *.cpp ../config/BrefValue.cpp

#include <iostream>
#include <HttpRequest.h>
#include <HttpResponse.h>
#include "HttpRequestParser.hpp"
#include "HttpLiterals.hpp"
#include "HttpUtils.hpp"

#define TEST_REQUEST ("GET / HTTP/1.1\r\n" \
		      "User-Agent: Opera/9.80 (X11; Linux x86_64; U; en) Presto/2.10.229 Version/11.62\r\n" \
		      "Host: localhost:8080\r\n" \
		      "Accept: text/html, application/xml;q=0.9, application/xhtml+xml, image/png, image/webp, image/jpeg, image/gif, image/x-xbitmap, */*;q=0.1\r\n" \
		      "Accept-Language: en-US,en;q=0.9\r\n" \
		      "Accept-Encoding: gzip, deflate\r\n" \
		      "Connection: Keep-Alive\r\n" \
		      "\r\n")

// Important: call this function
namespace http {
	void init_literals();
}

std::ostream &operator<<(std::ostream &os, bref::HttpRequest const &req) {
	os << "Request: " << http::request_methods::literals[req.getMethod()]
		<< " " << req.getUri()
		<< " HTTP/" << req.getVersion().Major
		<< "." << req.getVersion().Minor
		<< std::endl;

	bref::HttpRequest::const_iterator i = req.begin();
	for (; i != req.end(); ++i) {
		if (i != req.begin())
			os << std::endl;
		os << i->first << ":";
		bref::BrefValue::confType conf_type = i->second.getType();
		if (conf_type == bref::BrefValue::stringType) {
			os << i->second.asString();
		}
		else if (conf_type == bref::BrefValue::listType) {
			bref::BrefValueList const &l = i->second.asList();
			bref::BrefValueList::const_iterator it = l.begin();
			for (; it != l.end(); ++it) {
				if (it != l.begin())
					os << ";";
				os << it->asString();
			}
		}
		else if (conf_type == bref::BrefValue::arrayType) {
			bref::BrefValueArray const &ar = i->second.asArray();
			bref::BrefValueArray::const_iterator it = ar.begin();
			for (; it != ar.end(); ++it) {
				if (it != ar.begin())
					os << ";";
				os << it->first << "=" << it->second.asString();
			}
		}
	}

	return os;
}

std::ostream &operator<<(std::ostream &os, bref::HttpResponse const &rep) {
	os << "Response: " << http::util::to_string(rep.getRawData());

	return os;
}

int main() {
	bref::HttpRequest req;
	bref::HttpResponse rep;
	http::HttpRequestParser reqp;

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

	std::cout << reqp.forge(TEST_REQUEST) << std::endl;
}
