/*
 * request.hpp for zia
 * by lenorm_f
 */

#ifndef __REQUEST_H__
#define __REQUEST_H__

#include <map>
#include <string>
#include <irequest.hpp>

class Request : public zia::http::IRequest<std::string> {
	typedef zia::http::IRequest<std::string> StringRequest;

	std::string _buffer;

	zia::http::method _method;
	std::string _uri;
	zia::http::version _version;

	std::map<std::string, std::string> _headers;

	public:
	Request() {
	}
	Request(std::string const &s) {
		_buffer = s;
	}
	Request(StringRequest *b) {
		_buffer = b->getBuffer();
	}
	~Request() {}

	std::string const &getBuffer() const {
		return _buffer;
	}

	zia::http::method getMethod() const {
		return _method;
	}
	std::string const &getURI() const {
		return _uri;
	}
	zia::http::version getVersion() const {
		return _version;
	}

	std::string getHeaderContent(std::string const &header) {
		return _headers[header];
	}

	std::list<std::pair<std::string, std::string>> getHeaders() const {
		std::list<std::pair<std::string, std::string>> _headers_list;

		for (auto &p : _headers)
			_headers_list.push_back(p);

		return _headers_list;
	}
	std::list<std::string> getHeadersName() const {
		std::list<std::string> _headers_list;

		for (auto &p : _headers)
			_headers_list.push_back(p.first);

		return _headers_list;
	}
	std::list<std::string> getHeadersContent() const {
		std::list<std::string> _headers_list;

		for (auto &p : _headers)
			_headers_list.push_back(p.second);

		return _headers_list;
	}

	void setBuffer(std::string const &buffer) {
		_buffer = buffer;
	}

	void setMethod(zia::http::method new_method) {
		_method = new_method;
	}
	void setURI(std::string const &new_uri) {
		_uri = new_uri;
	}
	void setVersion(zia::http::version new_version) {
		_version = new_version;
	}

	void setHeaderContent(std::string const &header_name,
			      std::string const &content) {
		_headers[header_name] = content;
	}

	void addHeader(std::string const &header_name,
		       std::string const &content) {
		_headers[header_name] = content;
	}

	void removeHeader(std::string const &header_name) {
		_headers.erase(header_name);
	}
};

#endif
