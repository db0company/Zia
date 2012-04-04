#ifndef __CONFIGURATION_HPP__
# define __CONFIGURATION_HPP__

#include "IConfHelper.h"

using namespace bref;

class		Configuration : public IConfHelper
{
  BrefValue	_value;

public:

  Configuration();
  virtual ~Configuration();

  virtual const BrefValue & findValue(std::string const & key) const;
  virtual const BrefValue & findValue(std::string const & key);
  virtual const BrefValue & findValue(std::string const & key,
				      HttpRequest const & request) const;
};

#endif
