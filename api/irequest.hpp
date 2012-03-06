/*
 * irequest.hpp for zia
 * by lenorm_f
 */

#ifndef __IREQUEST_H__
#define __IREQUEST_H__

#include <list>
#include "httpdef.hpp"

namespace zia { namespace http {
	template <typename T>
	class IRequest {
		typedef T buffer_type;

		public:
		virtual ~IRequest() {}

		// Get the buffer associated to the request
		virtual buffer_type const &getBuffer() const = 0;

		// A few simple getters for the HTTP request attributes
		virtual method getMethod() const = 0;
		virtual buffer_type const &getURI() const = 0;
		virtual version getVersion() const = 0;

		// Get a particular entity-body, associated with a header name
		virtual buffer_type getHeaderContent(buffer_type const &header_name) = 0;
		// Get a list of all the headers added to the request, along
		// with their value
		virtual std::list<std::pair<buffer_type, buffer_type> > getHeaders() const = 0;
		// Get a list of all the headers added to the request
		virtual std::list<buffer_type> getHeadersName() const = 0;
		// Get a list of all the headers' values of the request
		virtual std::list<buffer_type> getHeadersContent() const = 0;

		// Assign a new buffer to the request
		virtual void setBuffer(buffer_type const &buffer) = 0;

		// Set the method of the request
		virtual void setMethod(method new_method) = 0;
		// Set the URI of the request
		virtual void setURI(buffer_type const &new_uri) = 0;
		// Set the version of the HTTP request
		virtual void setVersion(version new_version) = 0;

		// Modify the body of the request
		virtual void setHeaderContent(buffer_type const &header_name,
					      buffer_type const &content) = 0;

		// Add a header to the request
		virtual void addHeader(buffer_type const &header_name,
				       buffer_type const &content) = 0;

		// Remove a header from the request
		virtual void removeHeader(buffer_type const &header_name) = 0;
	};
}}

#endif
