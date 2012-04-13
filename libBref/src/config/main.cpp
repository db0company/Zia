#include <iostream>

#include "BrefValue.h"
#include "Configuration.hpp"

using namespace bref;

int main(int ac, char **av)
{
  BrefValue	a(42);

  std::cout << a.asString() << std::endl;
  std::cout << a.asInt() << std::endl;

  Configuration	config;

  //config.LoadFromFile(".zia-config");

  BrefValue	doc_root = config.findValue("DocumentRoot");

  if (doc_root.isString() && doc_root.asString().empty())
    std::cout << "Document Root found : " << doc_root.asString() << std::endl;
  else
    std::cout << "Document Root not found" << std::endl;
}
