/*
 * HttpResponseParser.hpp for Zia
 * by lenorm_f
 */

#pragma once
#ifndef __HTTPRESPONSE_PARSER_H__
#define __HTTPRESPONSE_PARSER_H__

#include <HttpResponse.h>
#include "HttpParser.hpp"

namespace http {
struct HttpResponseParser : public HttpParser {
	bref::HttpResponse forge(std::string const&);
};
}

#endif
