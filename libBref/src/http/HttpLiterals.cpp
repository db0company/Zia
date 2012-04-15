/*
 * HttpLiterals.cpp for Zia
 * by lenorm_f
 */

#include <cstdlib>
#include "HttpLiterals.hpp"

std::map<bref::status_codes::Type, std::string> http::status_codes::literals =
std::map<bref::status_codes::Type, std::string>();
std::map<bref::request_methods::Type, std::string> http::request_methods::literals =
std::map<bref::request_methods::Type, std::string>();

namespace http {
// Init Functions
static void init_status_codes(std::map<bref::status_codes::Type, std::string> &str_status_codes) {
	str_status_codes[bref::status_codes::Continue] = "Continue";
	str_status_codes[bref::status_codes::SwitchingProtocols] = "Switching Protocols";
	str_status_codes[bref::status_codes::OK] = "OK";
	str_status_codes[bref::status_codes::Created] = "Created";
	str_status_codes[bref::status_codes::Accepted] = "Accepted";
	str_status_codes[bref::status_codes::NonAuthoritativeInformation] = "Non-Authoritative Information";
	str_status_codes[bref::status_codes::NoContent] = "No Content";
	str_status_codes[bref::status_codes::ResetContent] = "Reset Content";
	str_status_codes[bref::status_codes::PartialContent] = "Partial Content";
	str_status_codes[bref::status_codes::MultipleChoices] = "Multiple Choices";
	str_status_codes[bref::status_codes::MovedPermanently] = "Moved Permanently";
	str_status_codes[bref::status_codes::Found] = "Found";
	str_status_codes[bref::status_codes::SeeOther] = "See Other";
	str_status_codes[bref::status_codes::NotModified] = "Not Modified";
	str_status_codes[bref::status_codes::UseProxy] = "Use Proxy";
	str_status_codes[bref::status_codes::TemporaryRedirect] = "Temporary Redirect";
	str_status_codes[bref::status_codes::BadRequest] = "Bad Request";
	str_status_codes[bref::status_codes::Unauthorized] = "Unauthorized";
	str_status_codes[bref::status_codes::PaymentRequired] = "Payment Required";
	str_status_codes[bref::status_codes::Forbidden] = "Forbidden";
	str_status_codes[bref::status_codes::NotFound] = "Not Found";
	str_status_codes[bref::status_codes::MethodNotAllowed] = "Method Not Allowed";
	str_status_codes[bref::status_codes::NotAcceptable] = "Not Acceptable";
	str_status_codes[bref::status_codes::ProxyAuthenticationRequired] = "Proxy Authentication Required";
	str_status_codes[bref::status_codes::RequestTimeOut] = "Request Time-out";
	str_status_codes[bref::status_codes::Conflict] = "Conflict";
	str_status_codes[bref::status_codes::Gone] = "Gone";
	str_status_codes[bref::status_codes::LengthRequired] = "Length Required";
	str_status_codes[bref::status_codes::PreconditionFailed] = "Precondition Failed";
	str_status_codes[bref::status_codes::RequestEntityTooLarge] = "Request Entity Too Large";
	str_status_codes[bref::status_codes::RequestURITooLarge] = "Request-URI Too Large";
	str_status_codes[bref::status_codes::UnsupportedMediaType] = "Unsupported Media Type";
	str_status_codes[bref::status_codes::RequestedRangeNotSatisfiable] = "Requested range not satisfiable";
	str_status_codes[bref::status_codes::ExpectationFailed] = "Expectation Failed";
	str_status_codes[bref::status_codes::InternalServerError] = "Internal Server Error";
	str_status_codes[bref::status_codes::NotImplemented] = "Not Implemented";
	str_status_codes[bref::status_codes::BadGateway] = "Bad Gateway";
	str_status_codes[bref::status_codes::ServiceUnavailable] = "Service Unavailable";
	str_status_codes[bref::status_codes::GatewayTimeOut] = "Gateway Time-out";
	str_status_codes[bref::status_codes::HTTPVersionNotSupported] = "HTTP Version not supported";
}

static void init_request_methods(std::map<bref::request_methods::Type, std::string> &str_request_methods) {
	str_request_methods[bref::request_methods::Options] = "OPTIONS";
	str_request_methods[bref::request_methods::Get] = "GET";
	str_request_methods[bref::request_methods::Head] = "HEAD";
	str_request_methods[bref::request_methods::Post] = "POST";
	str_request_methods[bref::request_methods::Put] = "PUT";
	str_request_methods[bref::request_methods::Delete] = "DELETE";
	str_request_methods[bref::request_methods::Trace] = "TRACE";
	str_request_methods[bref::request_methods::Connect] = "CONNECT";
}

void init_literals() {
	init_status_codes(status_codes::literals);
	init_request_methods(request_methods::literals);
}

// Static Functions
bref::status_codes::Type status_codes::of_string(std::string const &s) {
	bref::status_codes::Type n = static_cast<bref::status_codes::Type>(::atoi(s.c_str()));
	std::string ss = status_codes::literals[n];
	if (!ss.empty())
		return n;

	std::map<bref::status_codes::Type, std::string>::const_iterator it;
	for (it = status_codes::literals.begin();
	     it != status_codes::literals.end(); ++it)
		if (it->second == s)
			return it->first;

	return bref::status_codes::UndefinedStatusCode;
}

bref::request_methods::Type request_methods::of_string(std::string const &s) {
	std::map<bref::request_methods::Type, std::string>::const_iterator it;
	for (it = request_methods::literals.begin();
	     it != request_methods::literals.end(); ++it)
		if (it->second == s)
			return it->first;

	return bref::request_methods::UndefinedRequestMethod;
}
}
