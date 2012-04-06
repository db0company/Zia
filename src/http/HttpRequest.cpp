/*
 * HttpRequest.cpp for Zia
 * by lenorm_f
 */

#include <HttpRequest.h>

namespace bref {
// CTors/DTors
HttpRequest::HttpRequest() {
	method_ = request_methods::Get;
}

HttpRequest::~HttpRequest() {
}

// Getters
request_methods::Type HttpRequest::getMethod() const {
	return method_;
}

std::string const &HttpRequest::getUri() const {
	return uri_;
}

Version const &HttpRequest::getVersion() const {
	return version_;
}

// Setters
void HttpRequest::setMethod(request_methods::Type method) {
	method_ = method;
}

void HttpRequest::setUri(std::string const &uri) {
	uri_ = uri;
}

void HttpRequest::setVersion(Version const &version) {
	version_ = version;
}
}
