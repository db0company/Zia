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
class HttpResponseParser : public HttpParser {
	void _assign_fields(bref::HttpResponse&,
			    std::string const&,
			    std::vector<std::string>&);
	void _parse_field(bref::HttpResponse&,
			  std::string const&,
			  std::vector<bref::Buffer>::const_iterator&,
			  std::vector<bref::Buffer>::const_iterator const&);
	void _parse_tokens(bref::HttpResponse&);

	public:
	HttpResponseParser();
	~HttpResponseParser();

	bref::HttpResponse forge(bref::Buffer const&);
	bref::HttpResponse forge(std::string const&);
};
}

#endif
