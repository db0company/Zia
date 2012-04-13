/*
 * HttpParser.cpp for Zia
 * by lenorm_f
 */

#include "HttpParser.hpp"
#include "HttpUtils.hpp"

#define IS_SPC(x) ((x) == ' ' || (x) == '\t')
#define EOL "\r\n"

namespace http {
// CTors/DTors
HttpParser::HttpParser() {
}

HttpParser::~HttpParser() {
}

// Private Functions
bool HttpParser::it_cmp(bref::Buffer::const_iterator it,
			bref::Buffer::const_iterator const &it_end,
			bref::Buffer const &buffer) const {
	bref::Buffer::const_iterator i = buffer.begin();
	for (; i != buffer.end(); ++it, ++i)
		if (it == it_end
		    || *i != *it)
			return false;

	return (i == buffer.end());
}

HttpParser::token_type HttpParser::consume(bref::Buffer::const_iterator &it,
					   unsigned int n) {
	HttpParser::token_type c;

	for (unsigned int i = 0; i < n; ++i) {
		if (i == n - 1)
			c = *it;
		_token.push_back(*it++);
	}

	return c;
}

// Protected Functions
bool HttpParser::spc(bref::Buffer::const_iterator &it,
		     bref:: Buffer::const_iterator const &it_end) const {
	if (it == it_end
	    || !IS_SPC(*it))
		return false;

	++it;

	return true;
}

bool HttpParser::eol(bref::Buffer::const_iterator &it,
		     bref::Buffer::const_iterator const &it_end) const {
	bref::Buffer buffer = util::to_buffer(EOL); 
	bool cmp = it_cmp(it, it_end, buffer);

	if (cmp)
		it += buffer.size();

	return cmp;
}

// Public Functions
HttpParser::eState HttpParser::parse(bref::Buffer::const_iterator &it,
				     bref::Buffer::const_iterator const &it_end) {
	HttpParser::token_type c;
	while (it != it_end) {
		if (eol(it, it_end)) {
			_tokens.push_back(_token);
			_token.clear();
			return FEED_ME;
		}
		else if (!spc(it, it_end)) {
			c = consume(it);
		}
		else {
			_tokens.push_back(_token);
			_token.clear();
		}
	}

	return DONE;
}
}
