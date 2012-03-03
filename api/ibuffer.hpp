/*
 * ibuffer.hpp for zia
 * by lenorm_f
 */

#ifndef __IBUFFER_H__
#define __IBUFFER_H__

namespace zia { namespace http {
	class IBuffer {
		public:
		virtual ~IBuffer() {}

		// Append data to the internal buffer
		virtual void feed(std::string const &data) = 0;
		// Remove data from the internal buffer
		virtual void remove(std::string::iterator &begin, std::string::iterator &end) = 0;
		// Empty the buffer
		virtual void clear() = 0;
	};
}}

#endif
