#include "Configuration.hpp"

using namespace bref;

static const BrefValue VALUE_NOT_FOUND;

// Ctors/Dtors
Configuration::Configuration() {
}

Configuration::~Configuration() {
}

// Miscellaneous

const BrefValue		&Configuration::findValue(const std::string &key) {
  return VALUE_NOT_FOUND;
}

const BrefValue		&Configuration::findValue(const std::string &key) const {
  if (_value.hasKey(key))
    return _value[key];

  return VALUE_NOT_FOUND;
}

const BrefValue		&Configuration::findValue(const std::string &key,
						  const HttpRequest &request) const {

  // TODO : Deeper search in data tree depending on request parameters

  return findValue(key);
}


