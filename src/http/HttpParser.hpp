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
	bool it_cmp(bref::Buffer::const_iterator, bref::Buffer::const_iterator&,
		    bref::Buffer const&) const;

	protected:
	bool spc(bref::Buffer::iterator&, bref::Buffer::const_iterator&) const;
	bool eol(bref::Buffer::iterator&, bref::Buffer::const_iterator&) const;

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
	eState parse(bref::Buffer::iterator&, bref::Buffer::const_iterator&);
};
}

#endif
