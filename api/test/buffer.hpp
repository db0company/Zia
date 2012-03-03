/*
 * buffer.hpp for zia
 * by lenorm_f
 */

#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <string>
#include <ibuffer.hpp>

class Buffer : public zia::http::IBuffer {
	std::string _buffer;

	public:
	Buffer(std::string const &s) {
		_buffer = s;
	}
	~Buffer() {}

	void feed(std::string const &data) {
		_buffer += data;
	}
	void remove(std::string::iterator &begin, std::string::iterator &end) {
		_buffer.erase(begin, end);
	}
	void clear() {
		_buffer.clear();
	}
};

#endif
