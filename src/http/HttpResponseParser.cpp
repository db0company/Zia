/*
 * HttpResponseParser.cpp for Zia
 * by lenorm_f
 */

#include <cstring>
#include "HttpResponseParser.hpp"
#include "HttpLiterals.hpp"
#include "HttpUtils.hpp"

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

	return {s1, s2};
}

namespace http {
// Ctors/DTors
HttpResponseParser::HttpResponseParser() : HttpParser() {
}

HttpResponseParser::~HttpResponseParser() {
}

// Private Functions
void HttpResponseParser::_assign_fields(bref::HttpResponse &resp,
					std::string const &name,
					std::vector<std::string> &fields) {
	if (fields.empty())
		return;

	bool hc = ::strchr(fields[0].c_str(), '=') != 0;
	bool hl = !hc && (::strchr(fields[0].c_str(), ';') != 0
			  || (fields.size() > 1
			      && ::strchr(fields[1].c_str(), ';') != 0));

	if (fields.size() == 1 && !hc) {
		resp[name] = bref::BrefValue(fields[0]);
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
		resp[name] = a;
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
		resp[name] = l;
	}

	fields.clear();
}

void HttpResponseParser::_parse_field(bref::HttpResponse &resp,
				      std::string const &s,
				      std::vector<bref::Buffer>::const_iterator &it,
				      std::vector<bref::Buffer>::const_iterator const &it_end) {
	std::vector<std::string> _fields;

	for (; it != it_end; ++it) {
		std::string const ss = util::to_string(*it);

		if (ss.empty())
			continue;
		if (ss[ss.length() - 1] == ':') {
			_assign_fields(resp, s, _fields);
			return _parse_field(resp, ss.substr(0, ss.length() - 1), ++it, it_end);
		}
		else {
			_fields.push_back(ss);
		}
	}
	_assign_fields(resp, s, _fields);
}

void HttpResponseParser::_parse_tokens(bref::HttpResponse &resp) {
	std::vector<bref::Buffer>::const_iterator it = _tokens.begin();
	std::vector<bref::Buffer>::const_iterator it_end = _tokens.end();
	for (; it != it_end; ++it) {
		std::string const s = util::to_string(*it);
		bref::status_codes::Type const sc = status_codes::of_string(s);

		if (resp.getVersion().Major == 0
		    && !::strncmp(s.c_str(), "HTTP/1.", 7))
			resp.setVersion(bref::Version(1, static_cast<int>(s[7] - 48)));
		else if (resp.getStatus() == bref::status_codes::UndefinedStatusCode
			 && sc != bref::status_codes::UndefinedStatusCode)
			resp.setStatus(sc);
		else if (s.length() > 1
			 && s[s.length() - 1] == ':') {
			_parse_field(resp, s.substr(0, s.length() - 1), ++it, it_end);
			if (it == it_end)
				break;
		}
	}
}

// Public Functions
bref::HttpResponse HttpResponseParser::forge(bref::Buffer const &buffer) {
	bref::HttpResponse resp;

	bool done = false;
	bref::Buffer::const_iterator it = buffer.begin();
	bref::Buffer::const_iterator const it_end = buffer.end();
	while (!done) {
		eState state = HttpParser::parse(it, it_end);
		switch (state) {
			case FEED_ME:
				_parse_tokens(resp);
				_tokens.clear();
				_token.clear();
				break;
			case DONE: done = true; break;
			default: break;
		}
	}

	return resp;
}

bref::HttpResponse HttpResponseParser::forge(std::string const &b) {
	return forge(util::to_buffer(b));
}
}
