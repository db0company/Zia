/*
 * HttpResponse.cpp for Zia
 * by lenorm_f
 */

#include <stdio.h>
#include <HttpResponse.h>
#include "HttpLiterals.hpp"
#include "HttpUtils.hpp"

namespace bref {
// CTors/DTors
HttpResponse::HttpResponse() {
	statusCode_ = status_codes::UndefinedStatusCode;
}

HttpResponse::~HttpResponse() {
}

// Getters
Version const &HttpResponse::getVersion() const {
	return version_;
}

status_codes::Type HttpResponse::getStatus() const {
	return statusCode_;
}

std::string const &HttpResponse::getReason() const {
	return reason_;
}

Buffer HttpResponse::getRawData() const {
	Buffer b;
	char buffer[256];

	::snprintf(buffer, sizeof(buffer),
		   "HTTP/%d.%d %d %s\r\n",
		   version_.Major, version_.Minor,
		   statusCode_,
		   http::status_codes::literals[statusCode_].c_str());
	for (unsigned int i = 0; i < sizeof(buffer) && buffer[i]; ++i)
		b.push_back(buffer[i]);
	HttpResponse::const_iterator it = this->begin();
	for (;it != this->end(); ++it) {
		if (it->second.isString()) {
			http::util::queue_pair_to_buffer(b,
							 it->first,
							 it->second.asString());
		}
		else if (it->second.isArray()) {
			http::util::queue_pair_to_buffer(b,
						    it->first,
						    ": ", "");
			bref::BrefValueArray const &a = it->second.asArray();
			bref::BrefValueArray::const_iterator jt = a.begin();
			for (; jt != a.end(); ++jt) {
				if (jt != a.begin())
					http::util::queue_to_buffer(b, "; ");
				http::util::queue_pair_to_buffer(b,
								 jt->first,
								 jt->second.asString(),
								 "=");
			}
		}
		else if (it->second.isList()) {
			http::util::queue_pair_to_buffer(b,
						    it->first,
						    ": ", "");
			bref::BrefValueList const &l = it->second.asList();
			bref::BrefValueList::const_iterator jt = l.begin();
			for (; jt != l.end(); ++jt) {
				if (jt != l.begin())
					http::util::queue_to_buffer(b, "; ");
				http::util::queue_to_buffer(b, jt->asString());
			}
		}
		http::util::queue_to_buffer(b, "\r\n");
	}

	return b;
}

// Setters
void HttpResponse::setVersion(Version const &version) {
	version_ = version;
}

void HttpResponse::setStatus(status_codes::Type code) {
	statusCode_ = code;
}

void HttpResponse::setReason(std::string const &reason) {
	reason_ = reason;
}
}