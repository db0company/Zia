#include <iostream>
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "http/HttpRequestParser.hpp"
#include "http/HttpLiterals.hpp"
#include "http/HttpUtils.hpp"

std::ostream &operator<<(std::ostream &os, bref::HttpRequest const &req) {
	os << "Request: " << http::request_methods::literals[req.getMethod()]
		<< " " << req.getUri()
		<< " HTTP/" << req.getVersion().Major
		<< "." << req.getVersion().Minor
		<< std::endl;

	bref::HttpRequest::const_iterator i = req.begin();
	for (; i != req.end(); ++i) {
		if (i != req.begin())
			os << std::endl;
		os << i->first << ":";
		bref::BrefValue::confType conf_type = i->second.getType();
		if (conf_type == bref::BrefValue::stringType) {
			os << i->second.asString();
		}
		else if (conf_type == bref::BrefValue::listType) {
			bref::BrefValueList const &l = i->second.asList();
			bref::BrefValueList::const_iterator it = l.begin();
			for (; it != l.end(); ++it) {
				if (it != l.begin())
					os << ";";
				os << it->asString();
			}
		}
		else if (conf_type == bref::BrefValue::arrayType) {
			bref::BrefValueArray const &ar = i->second.asArray();
			bref::BrefValueArray::const_iterator it = ar.begin();
			for (; it != ar.end(); ++it) {
				if (it != ar.begin())
					os << ";";
				os << it->first << "=" << it->second.asString();
			}
		}
	}

	return os;
}
