/*
 * request.hpp for zia
 * by lenorm_f
 */

#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <irequest.hpp>
#include "buffer.hpp"

class Request : public zia::http::IRequest {
	zia::http::IBuffer *_buffer;

	public:
	Request() {
		_buffer = 0;
	}
	Request(std::string const &s) {
		_buffer = new Buffer(s);
	}
	Request(zia::http::IBuffer *b) {
		_buffer = b;
	}
	~Request() {}

	zia::http::IBuffer *getBuffer() const {
		return _buffer;
	}

	void setBuffer(zia::http::IBuffer *buffer) {
		_buffer = buffer;
	}

	zia::http::method getMethod() const {
		return zia::http::method::METHOD_UNKNOWN;
	}
	std::string const &getURI() const {
		return std::string("");
	}
	zia::http::version getVersion() const {
		return zia::http::version::VERSION_UNKNOWN;
	}

	std::string const &getHeaderContent(char const *header) {
		return std::string("");
	}
	std::list<std::string> getHeaders() const {
		return {""};
	}
	std::list<std::string> getHeadersName() const {
		return {""};
	}
	std::list<std::string> getHeadersContent() const {
		return {""};
	}
};

#endif
