/*
 * HttpRequestParser.cpp for Zia
 * by lenorm_f
 */

#include "HttpRequestParser.hpp"
#include "HttpLiterals.hpp"
#include "HttpUtils.hpp"

#include <iostream>

static inline std::pair<std::string, std::string> split_on(std::string const &s, char c) {
	std::string s1;
	std::string s2;

	std::string::const_iterator it = s.begin();
	for (bool hc = false; it != s.end(); ++it) {
		if (*it == c)
			hc = true;
		else {
			if (!hc)
				s1 += *it;
			else
				s2 += *it;
		}
	}
#ifdef _WIN32
	return std::pair<std::string, std::string>(s1, s2);
#elif
	return {s1, s2};
#endif
}

namespace http {
// Ctors/DTors
HttpRequestParser::HttpRequestParser() : HttpParser() {
}

HttpRequestParser::~HttpRequestParser() {
}

// Private Functions
void HttpRequestParser::_assign_fields(bref::HttpRequest &req,
					std::string const &name,
					std::vector<std::string> &fields) {
	if (fields.empty())
		return;

	bool hc = fields[0].find('=') != std::string::npos;
	bool hl = !hc && (fields[0].find(';') != std::string::npos
			  || (fields.size() > 1
			      && fields[1].find(';') != std::string::npos));

	if (fields.size() == 1 && !hc) {
		req[name] = bref::BrefValue(fields[0]);
	}
	else if (hc) {
		bref::BrefValueArray a;
		std::vector<std::string>::const_iterator it = fields.begin();
		for (; it != fields.end(); ++it) {
			std::pair<std::string, std::string> p = split_on(*it, '=');
			if (p.second[p.second.length() - 1] == ';')
				p.second = p.second.substr(0, p.second.length() - 1);
			a[p.first] = p.second;
		}
		req[name] = a;
	}
	else if (hl) {
		bref::BrefValueList l;
		std::vector<std::string>::const_iterator it = fields.begin();
		for (; it != fields.end(); ++it) {
			std::string ss = *it;
			if (ss[ss.length() - 1] == ';')
				ss = ss.substr(0, ss.length() - 1);
			l.push_back(ss);
		}
		req[name] = l;
	}

	fields.clear();
}

void HttpRequestParser::_parse_field(bref::HttpRequest &req,
				      std::string const &s,
				      std::vector<bref::Buffer>::const_iterator &it,
				      std::vector<bref::Buffer>::const_iterator const &it_end) {
	std::vector<std::string> _fields;

	for (; it != it_end; ++it) {
		std::string const ss = util::to_string(*it);

		if (ss.empty())
			continue;
		if (0 && ss[ss.length() - 1] == ':') { // RM
			_assign_fields(req, s, _fields);
			return _parse_field(req, ss.substr(0, ss.length() - 1), ++it, it_end);
		}
		else {
			_fields.push_back(ss);
		}
	}
	_assign_fields(req, s, _fields);
}

void HttpRequestParser::_parse_tokens(bref::HttpRequest &req) {
	std::vector<bref::Buffer>::const_iterator it = _tokens.begin();
	std::vector<bref::Buffer>::const_iterator it_end = _tokens.end();
	for (; it != it_end; ++it) {
		std::string const s = util::to_string(*it);

		bool const hv = req.getVersion().Major == 1;
		bref::request_methods::Type const rm = request_methods::of_string(s);
		bool const hm = req.getMethod() != bref::request_methods::UndefinedRequestMethod;

		if (!hm
		    && rm != bref::request_methods::UndefinedRequestMethod)
			req.setMethod(rm);
		else if (!hv && hm
			 && req.getUri().empty())
			req.setUri(s);
		else if (!hv
			 && s.substr(0, 7) == "HTTP/1.")
			req.setVersion(bref::Version(1, static_cast<int>(s[7] - 48)));
		else if (s.length() > 1
			 && s[s.length() - 1] == ':') {
			_parse_field(req, s.substr(0, s.length() - 1), ++it, it_end);
			if (it == it_end)
				break;
		}
	}
}

// Public Functions
bref::HttpRequest HttpRequestParser::forge(bref::Buffer const &buffer) {
	bref::HttpRequest req;

	bool done = false;
	bref::Buffer::const_iterator it = buffer.begin();
	bref::Buffer::const_iterator const it_end = buffer.end();
	while (!done) {
		eState state = HttpParser::parse(it, it_end);
		switch (state) {
			case FEED_ME:
				_parse_tokens(req);
				_tokens.clear();
				_token.clear();
				break;
			case DONE: done = true; break;
			default: break;
		}
	}

	return req;
}

bref::HttpRequest HttpRequestParser::forge(std::string const &b) {
	return forge(util::to_buffer(b));
}
}
