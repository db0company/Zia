#ifndef __UTILS_HPP__
# define __UTILS_HPP__

#include <string>
#include <sstream>
#include <iostream>

namespace utils
{
  template<typename T>
  T convert_to(std::string const &s) {
    T _n;
    std::stringstream ss(s, std::ios_base::in);

    ss >> _n;

    return _n;
  }

  template<typename T>
  std::string to_string(const T &Value) {
    std::ostringstream oss;
    oss << Value;

    return oss.str();
  }

  std::pair<std::string, int> file_contents(std::string const&);
}

#endif