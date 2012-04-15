/*
 * http_pipeline.cpp for zia
 * by lenorm_f
 */

#include <functional>
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "http/HttpLiterals.hpp"
#include "tools/utils.hpp"

#define BIND_HANDLER(addr) std::bind(addr, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)

typedef std::function<bool(bref::HttpRequest const&,
			   bref::HttpResponse&,
			   std::string&)>
	RequestHanderFunctor;

static std::string _rnd_buffer;

static void custom_rep(bref::HttpResponse &rep,
		       std::string &body = _rnd_buffer,
		       bref::status_codes::Type err = bref::status_codes::UndefinedStatusCode) {
	rep.setStatus(bref::status_codes::NotFound);

	if (err == bref::status_codes::UndefinedStatusCode)
		rep["Content-Length"] = bref::BrefValue(std::string("0"));
	else {
		std::string const err_path = std::string("errors/") +
			utils::to_string(static_cast<int>(err))
			+ std::string(".html");
		std::pair<std::string, int> fp = utils::file_contents(err_path);
		body = fp.first;
		rep["Content-Length"] = bref::BrefValue(utils::to_string(fp.second));
	}
}

static bool request_handler_get(bref::HttpRequest const &req,
				bref::HttpResponse &rep,
				std::string &body) {
	std::pair<std::string, int> fp = utils::file_contents(req.getUri().substr(1));

	if (fp.second < 0)
		custom_rep(rep,
			   body,
			   bref::status_codes::NotFound);
	else {
		rep.setStatus(bref::status_codes::OK);
		body = fp.first;
		rep["Content-Length"] = bref::BrefValue(utils::to_string(fp.second));
	}

	rep["Connection"] = bref::BrefValue(std::string("close"));
	rep["Content-Type"] = bref::BrefValue(std::string("text/html; charset=UTF-8"));

	return false;
}

bool http_pipeline(bref::HttpRequest const &req,
		   bref::HttpResponse &rep,
		   std::string &body) {
	static std::map<bref::request_methods::Type, RequestHanderFunctor> _handlers{
		{bref::request_methods::Get, BIND_HANDLER(&request_handler_get)},
	};

	bool chunked = false;
	if (req.getVersion().Major != 1
	    || (req.getVersion().Minor != 0 && req.getVersion().Minor != 1))
		rep.setStatus(bref::status_codes::HTTPVersionNotSupported);
	else if (_handlers.find(req.getMethod()) == _handlers.end())
		rep.setStatus(bref::status_codes::NotImplemented);
	else
		chunked = _handlers[req.getMethod()](req, rep, body);

	rep.setVersion({1, 1});
	rep["Server"] = bref::BrefValue(std::string("Zia"));

	return chunked;
}
