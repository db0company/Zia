/*
 * HttpResponseParser.cpp for Zia
 * by lenorm_f
 */

#include "HttpResponseParser.hpp"
#include "HttpUtils.hpp"

namespace http {
bref::HttpResponse HttpResponseParser::forge(std::string const &s) {
	bref::Buffer buffer = util::to_buffer(s);
	bref::HttpResponse resp;

	bool done = false;
	bref::Buffer::iterator it = buffer.begin();
	bref::Buffer::const_iterator it_end = buffer.end();
	while (!done) {
		eState state = HttpParser::parse(it, it_end);
		switch (state) {
			case FEED_ME: break;
			case DONE: done = true; break;
			default: break;
		}
	}

	return resp;
}
}
