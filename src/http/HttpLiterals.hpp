/*
 * HttpLiterals.hpp for Zia
 * by lenorm_f
 */

#pragma once
#ifndef __HTTPLITERALS_H__
#define __HTTPLITERALS_H__

#include <map>
#include <string>
#include <HttpConstants.h>

namespace http {
struct status_codes {
	static std::map<bref::status_codes::Type, std::string> literals;
	static bref::status_codes::Type of_string(std::string const&);
};

struct request_methods {
	static std::map<bref::request_methods::Type, std::string> literals;
	static bref::request_methods::Type of_string(std::string const&);
};
}

#endif
