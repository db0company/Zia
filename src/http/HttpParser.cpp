/*
 * HttpParser.cpp for Zia
 * by lenorm_f
 */

#include "HttpParser.hpp"
#include "HttpUtils.hpp"

#define IS_SPC(x) ((x) == ' ' || (x) == '\t')
#define EOL "\r\n"

namespace http {
// Private Functions
bool HttpParser::it_cmp(bref::Buffer::const_iterator it,
			bref::Buffer::const_iterator &it_end,
			bref::Buffer const &buffer) const {
	bref::Buffer::const_iterator i = buffer.begin();
	for (; i != buffer.end(); ++it, ++i)
		if (it == it_end
		    || *i != *it)
			return false;

	return i == buffer.end();
}

// Protected Functions
bool HttpParser::spc(bref::Buffer::iterator &it,
		     bref:: Buffer::const_iterator &it_end) const {
	if (it == it_end
	    || !IS_SPC(*it))
		return false;

	++it;

	return true;
}

bool HttpParser::eol(bref::Buffer::iterator &it,
		     bref::Buffer::const_iterator &it_end) const {
	bref::Buffer buffer = util::to_buffer(EOL); 
	bool cmp = it_cmp(it, it_end, buffer);

	if (cmp)
		it += buffer.size();

	return (it != it_end
		&& cmp);
}

// Public Functions
HttpParser::eState HttpParser::parse(bref::Buffer::iterator &it,
				     bref::Buffer::const_iterator &it_end) {
	while (it != it_end) {
		if (1);
	}

	return FEED_ME;
}
}
