/*
 * HttpResponse.cpp for Zia
 * by lenorm_f
 */

#include <stdio.h>
#include <HttpResponse.h>
#include "HttpLiterals.hpp"

namespace bref {
// CTors/DTors
HttpResponse::HttpResponse() {
	statusCode_ = status_codes::UndefinedStatusCode;
}

HttpResponse::~HttpResponse() {
}

// Getters
Version const &HttpResponse::getVersion() const {
	return version_;
}

status_codes::Type HttpResponse::getStatus() const {
	return statusCode_;
}

std::string const &HttpResponse::getReason() const {
	return reason_;
}

Buffer HttpResponse::getRawData() const {
	Buffer b;
	char buffer[256];

	::snprintf(buffer, sizeof(buffer),
		   "HTTP/%d.%d %d %s\r\n",
		   version_.Major, version_.Minor,
		   statusCode_,
		   http::error_codes::literals[statusCode_].c_str());
	for (unsigned int i = 0; i < sizeof(buffer) && buffer[i]; ++i)
		b.push_back(buffer[i]);
	HttpResponse::const_iterator it = this->begin();
	for (;it != this->end(); ++it) {
		std::string s = it->first;
		s += ": ";
		s += it->second.asString();
		for (std::string::const_iterator jt = s.begin(); jt != s.end(); ++jt)
			b.push_back(*jt);
		b.push_back('\r');
		b.push_back('\n');
	}

	return b;
}

// Setters
void HttpResponse::setVersion(Version const &version) {
	version_ = version;
}

void HttpResponse::setStatus(status_codes::Type code) {
	statusCode_ = code;
}

void HttpResponse::setReason(std::string const &reason) {
	reason_ = reason;
}
}
