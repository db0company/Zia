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
}

#endif
