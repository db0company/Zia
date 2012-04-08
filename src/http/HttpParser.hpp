/*
 * HttpParser.hpp for Zia
 * by lenorm_f
 */

#pragma once
#ifndef __HTTPPARSER_H__
#define __HTTPPARSER_H__

#include <Buffer.h>

namespace http {
class HttpParser {
	bool it_cmp(bref::Buffer::const_iterator,
		    bref::Buffer::const_iterator&,
		    bref::Buffer const&) const;
	bref::Buffer::const_iterator::value_type consume(bref::Buffer::const_iterator&, unsigned int = 1);

	protected:
	bref::Buffer _token;
	std::vector<bref::Buffer> _tokens;
	typedef bref::Buffer::const_iterator::value_type token_type;

	bool spc(bref::Buffer::const_iterator&,
		 bref::Buffer::const_iterator&) const;
	bool eol(bref::Buffer::const_iterator&,
		 bref::Buffer::const_iterator&) const;

	public:
	enum eState {
		UNKNOWN = -1,
		DONE = 0,
		FEED_ME,
	};

	public:
	HttpParser();
	~HttpParser();

	void feed(bref::Buffer const&);
	eState parse(bref::Buffer::const_iterator&,
		     bref::Buffer::const_iterator&);
};
}

#endif
