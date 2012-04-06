/*
 * HttpResponse.cpp for Zia
 * by lenorm_f
 */

#include <stdio.h>
#include <HttpResponse.h>

namespace bref {

	static std::map<status_codes::Type, std::string> str_error_codes;
	void init_error_codes() {
		extern std::map<status_codes::Type, std::string> str_error_codes;

		str_error_codes[status_codes::Continue] = "Continue";
		str_error_codes[status_codes::SwitchingProtocols] = "Switching Protocols";
		str_error_codes[status_codes::OK] = "OK";
		str_error_codes[status_codes::Created] = "Created";
		str_error_codes[status_codes::Accepted] = "Accepted";
		str_error_codes[status_codes::NonAuthoritativeInformation] = "Non-Authoritative Information";
		str_error_codes[status_codes::NoContent] = "No Content";
		str_error_codes[status_codes::ResetContent] = "Reset Content";
		str_error_codes[status_codes::PartialContent] = "Partial Content";
		str_error_codes[status_codes::MultipleChoices] = "Multiple Choices";
		str_error_codes[status_codes::MovedPermanently] = "Moved Permanently";
		str_error_codes[status_codes::Found] = "Found";
		str_error_codes[status_codes::SeeOther] = "See Other";
		str_error_codes[status_codes::NotModified] = "Not Modified";
		str_error_codes[status_codes::UseProxy] = "Use Proxy";
		str_error_codes[status_codes::TemporaryRedirect] = "Temporary Redirect";
		str_error_codes[status_codes::BadRequest] = "Bad Request";
		str_error_codes[status_codes::Unauthorized] = "Unauthorized";
		str_error_codes[status_codes::PaymentRequired] = "Payment Required";
		str_error_codes[status_codes::Forbidden] = "Forbidden";
		str_error_codes[status_codes::NotFound] = "Not Found";
		str_error_codes[status_codes::MethodNotAllowed] = "Method Not Allowed";
		str_error_codes[status_codes::NotAcceptable] = "Not Acceptable";
		str_error_codes[status_codes::ProxyAuthenticationRequired] = "Proxy Authentication Required";
		str_error_codes[status_codes::RequestTimeOut] = "Request Time-out";
		str_error_codes[status_codes::Conflict] = "Conflict";
		str_error_codes[status_codes::Gone] = "Gone";
		str_error_codes[status_codes::LengthRequired] = "Length Required";
		str_error_codes[status_codes::PreconditionFailed] = "Precondition Failed";
		str_error_codes[status_codes::RequestEntityTooLarge] = "Request Entity Too Large";
		str_error_codes[status_codes::RequestURITooLarge] = "Request-URI Too Large";
		str_error_codes[status_codes::UnsupportedMediaType] = "Unsupported Media Type";
		str_error_codes[status_codes::RequestedRangeNotSatisfiable] = "Requested range not satisfiable";
		str_error_codes[status_codes::ExpectationFailed] = "Expectation Failed";
		str_error_codes[status_codes::InternalServerError] = "Internal Server Error";
		str_error_codes[status_codes::NotImplemented] = "Not Implemented";
		str_error_codes[status_codes::BadGateway] = "Bad Gateway";
		str_error_codes[status_codes::ServiceUnavailable] = "Service Unavailable";
		str_error_codes[status_codes::GatewayTimeOut] = "Gateway Time-out";
		str_error_codes[status_codes::HTTPVersionNotSupported] = "HTTP Version not supported";
	}
}

namespace bref {
// CTors/DTors
HttpResponse::HttpResponse() {
	statusCode_ = status_codes::Undefined;

	if (str_error_codes.empty())
		init_error_codes();
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
	extern std::map<status_codes::Type, std::string> str_error_codes;

	Buffer b;
	char buffer[256];

	::snprintf(buffer, sizeof(buffer),
		   "HTTP/%d.%d %d %s\r\n",
		   version_.Major, version_.Minor,
		   static_cast<int>(statusCode_),
		   str_error_codes[statusCode_].c_str());
	for (unsigned int i = 0; i < sizeof(buffer) && buffer[i]; ++i)
		b.push_back(buffer[i]);

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
