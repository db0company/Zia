/*
 * file_contents.cpp for zia
 * by lenorm_f
 */

#include <fstream>
#include "utils.hpp"

namespace utils {
std::pair<std::string, int> file_contents(std::string const &path) {
	int length;
	char *buffer;
	std::string s;
	std::ifstream is;

	is.open(path, std::ios::binary );
	if (!is)
		return std::pair<std::string, int>("", -1);

	is.seekg(0, std::ios::end);
	length = is.tellg();
	is.seekg(0, std::ios::beg);

	buffer = new char[length];
	is.read(buffer,length);
	is.close();

	s.assign(buffer);

	delete[] buffer;

	return std::pair<std::string, int>(s, length);
}
}
