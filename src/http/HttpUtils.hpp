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
}}

#endif
