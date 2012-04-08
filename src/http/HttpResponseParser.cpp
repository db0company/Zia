/*
 * HttpResponseParser.cpp for Zia
 * by lenorm_f
 */

#include <cstring>
#include "HttpResponseParser.hpp"
#include "HttpUtils.hpp"

#include <iostream>

namespace http {
// Ctors/DTors
HttpResponseParser::HttpResponseParser() : HttpParser() {
}

HttpResponseParser::~HttpResponseParser() {
}

// Private Functions
void HttpResponseParser::_parse_tokens(bref::HttpResponse &resp) {
	std::vector<bref::Buffer>::const_iterator it = _tokens.begin();
	for (; it != _tokens.end(); ++it) {
		std::string s = util::to_string(*it);

		if (!::strncmp(s.c_str(), "HTTP/1.", 7))
			resp.setVersion(bref::Version(1, static_cast<int>(s[7] - 48)));
	}
}

// Public Functions
bref::HttpResponse HttpResponseParser::forge(bref::Buffer const &buffer) {
	bref::HttpResponse resp;

	bool done = false;
	bref::Buffer::const_iterator it = buffer.begin();
	bref::Buffer::const_iterator it_end = buffer.end();
	while (!done) {
		eState state = HttpParser::parse(it, it_end);
		switch (state) {
			case FEED_ME:
				_parse_tokens(resp);
				_tokens.clear();
				_token.clear();
				break;
			case DONE: done = true; break;
			default: break;
		}
	}

	return resp;
}

bref::HttpResponse HttpResponseParser::forge(std::string const &b) {
	return forge(util::to_buffer(b));
}
}
