/*
 * HttpRequestParser.hpp for Zia
 * by lenorm_f
 */

#pragma once
#ifndef __HTTPREQUEST_PARSER_H__
#define __HTTPREQUEST_PARSER_H__

#include <HttpRequest.h>
#include "HttpParser.hpp"

namespace http {
class HttpRequestParser : public HttpParser {
	void _assign_fields(bref::HttpRequest&,
			    std::string const&,
			    std::vector<std::string>&);
	void _parse_field(bref::HttpRequest&,
			  std::string const&,
			  std::vector<bref::Buffer>::const_iterator&,
			  std::vector<bref::Buffer>::const_iterator const&);
	void _parse_tokens(bref::HttpRequest&);

	public:
	HttpRequestParser();
	~HttpRequestParser();

	bref::HttpRequest forge(bref::Buffer const&);
	bref::HttpRequest forge(std::string const&);
};
}

#endif
