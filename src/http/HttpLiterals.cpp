/*
 * HttpLiterals.cpp for Zia
 * by lenorm_f
 */

#include "HttpLiterals.hpp"

std::map<bref::status_codes::Type, std::string> http::error_codes::literals =
std::map<bref::status_codes::Type, std::string>();
std::map<bref::request_methods::Type, std::string> http::request_methods::literals =
std::map<bref::request_methods::Type, std::string>();

namespace http {
static void init_error_codes(std::map<bref::status_codes::Type, std::string> &str_error_codes) {
	str_error_codes[bref::status_codes::Continue] = "Continue";
	str_error_codes[bref::status_codes::SwitchingProtocols] = "Switching Protocols";
	str_error_codes[bref::status_codes::OK] = "OK";
	str_error_codes[bref::status_codes::Created] = "Created";
	str_error_codes[bref::status_codes::Accepted] = "Accepted";
	str_error_codes[bref::status_codes::NonAuthoritativeInformation] = "Non-Authoritative Information";
	str_error_codes[bref::status_codes::NoContent] = "No Content";
	str_error_codes[bref::status_codes::ResetContent] = "Reset Content";
	str_error_codes[bref::status_codes::PartialContent] = "Partial Content";
	str_error_codes[bref::status_codes::MultipleChoices] = "Multiple Choices";
	str_error_codes[bref::status_codes::MovedPermanently] = "Moved Permanently";
	str_error_codes[bref::status_codes::Found] = "Found";
	str_error_codes[bref::status_codes::SeeOther] = "See Other";
	str_error_codes[bref::status_codes::NotModified] = "Not Modified";
	str_error_codes[bref::status_codes::UseProxy] = "Use Proxy";
	str_error_codes[bref::status_codes::TemporaryRedirect] = "Temporary Redirect";
	str_error_codes[bref::status_codes::BadRequest] = "Bad Request";
	str_error_codes[bref::status_codes::Unauthorized] = "Unauthorized";
	str_error_codes[bref::status_codes::PaymentRequired] = "Payment Required";
	str_error_codes[bref::status_codes::Forbidden] = "Forbidden";
	str_error_codes[bref::status_codes::NotFound] = "Not Found";
	str_error_codes[bref::status_codes::MethodNotAllowed] = "Method Not Allowed";
	str_error_codes[bref::status_codes::NotAcceptable] = "Not Acceptable";
	str_error_codes[bref::status_codes::ProxyAuthenticationRequired] = "Proxy Authentication Required";
	str_error_codes[bref::status_codes::RequestTimeOut] = "Request Time-out";
	str_error_codes[bref::status_codes::Conflict] = "Conflict";
	str_error_codes[bref::status_codes::Gone] = "Gone";
	str_error_codes[bref::status_codes::LengthRequired] = "Length Required";
	str_error_codes[bref::status_codes::PreconditionFailed] = "Precondition Failed";
	str_error_codes[bref::status_codes::RequestEntityTooLarge] = "Request Entity Too Large";
	str_error_codes[bref::status_codes::RequestURITooLarge] = "Request-URI Too Large";
	str_error_codes[bref::status_codes::UnsupportedMediaType] = "Unsupported Media Type";
	str_error_codes[bref::status_codes::RequestedRangeNotSatisfiable] = "Requested range not satisfiable";
	str_error_codes[bref::status_codes::ExpectationFailed] = "Expectation Failed";
	str_error_codes[bref::status_codes::InternalServerError] = "Internal Server Error";
	str_error_codes[bref::status_codes::NotImplemented] = "Not Implemented";
	str_error_codes[bref::status_codes::BadGateway] = "Bad Gateway";
	str_error_codes[bref::status_codes::ServiceUnavailable] = "Service Unavailable";
	str_error_codes[bref::status_codes::GatewayTimeOut] = "Gateway Time-out";
	str_error_codes[bref::status_codes::HTTPVersionNotSupported] = "HTTP Version not supported";
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
	init_error_codes(error_codes::literals);
	init_request_methods(request_methods::literals);
}
}
