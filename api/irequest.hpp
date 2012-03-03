/*
 * irequest.hpp for zia
 * by lenorm_f
 */

#ifndef __IREQUEST_H__
#define __IREQUEST_H__

#include <list>
#include <string>
#include "httpdef.hpp"

namespace zia { namespace http {
	class IBuffer;

	class IRequest {
		public:
		virtual ~IRequest() {}

		// Get the buffer associated to the request
		virtual IBuffer *getBuffer() const = 0;

		// Assign a buffer to the request
		virtual void setBuffer(IBuffer *buffer) = 0;

		// A few simple getters for the HTTP request attributes
		// Request-Line = Method SP Request-URI SP HTTP-Version CRLF
		virtual method getMethod() const = 0;
		virtual std::string const &getURI() const = 0;
		virtual version getVersion() const = 0;

		// Get a particular entity-body, associated with a header name
		virtual std::string const &getHeaderContent(char const *header) = 0;
		virtual std::list<std::string> getHeaders() const = 0;
		virtual std::list<std::string> getHeadersName() const = 0;
		virtual std::list<std::string> getHeadersContent() const = 0;
	};
}}

#endif
