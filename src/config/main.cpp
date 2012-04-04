#include <iostream>

#include "BrefValue.h"

using namespace bref;

int main(int ac, char **av)
{
  BrefValue	a(42);
  BrefValue	empty;

  std::cout << a.asString() << std::endl;
  std::cout << a.asInt() << std::endl;
}
