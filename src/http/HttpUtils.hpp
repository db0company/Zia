/*
 * HttpUtils.hpp for Zia
 * by lenorm_f
 */

#pragma once
#ifndef __HTTPUTILS_H__
#define __HTTPUTILS_H__

#include <string>
#include <Buffer.h>

namespace http { namespace util {
static inline std::string to_string(bref::Buffer const &buffer) {
	std::string s;

	bref::Buffer::const_iterator it;
	for (it = buffer.begin(); it != buffer.end(); ++it)
		s += *it;

	return s;
}

static inline bref::Buffer to_buffer(std::string const &s) {
	bref::Buffer buffer;

	std::string::const_iterator it;
	for (it = s.begin(); it != s.end(); ++it)
		buffer.push_back(*it);

	return buffer;
}

static inline void queue_to_buffer(bref::Buffer &b, std::string const &s) {
	for (std::string::const_iterator it = s.begin();
	     it != s.end();
	     ++it)
		b.push_back(*it);
}

static inline void queue_pair_to_buffer(bref::Buffer &b,
					std::string const &sa,
					std::string const &sb,
					std::string const &sep = ": ") {
	std::string s = sa;
	s += sep;
	s += sb;

	queue_to_buffer(b, s);
}
}}

#endif
