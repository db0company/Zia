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
struct error_codes {
	static std::map<bref::status_codes::Type, std::string> literals;
};

struct request_methods {
	static std::map<bref::request_methods::Type, std::string> literals;
};
}

#endif
