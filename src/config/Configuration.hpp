#ifndef __CONFIGURATION_HPP__
# define __CONFIGURATION_HPP__

#include <fstream>
#include <yaml-cpp/yaml.h>
#include <IConfHelper.h>

#include "configexcept.hpp"

using namespace bref;

class		Configuration : public IConfHelper
{
  BrefValue	_value;

public:

  Configuration();
  virtual ~Configuration();

  virtual const		BrefValue & findValue(std::string const & key) const;
  virtual const		BrefValue & findValue(std::string const & key,
				      HttpRequest const & request) const;

  virtual bool		LoadFromFile(const std::string &input_file);
  virtual BrefValue	&GetConfiguration();
};

std::ostream &operator <<(std::ostream &out, BrefValue &v);

#endif
