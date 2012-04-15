#include <iostream>

#include "BrefValue.h"
#include "Configuration.hpp"

using namespace bref;

// Compiling instructions : g++ main.cpp Configuration.cpp BrefValue.cpp ../zia/baseexcept.cpp -I../../bref-api/include/bref/ -lyaml-cpp -std=c++0x -I../tools/ -I../../include/
// Testing instructions : ./a.out .zia-config

int main(int ac, char **av)
{
  if (ac > 1)
    {
      Configuration		config;

      if (!config.LoadFromFile(av[1]))
	{
	  std::cerr << "Configuration loading has failed, aborting.." << std::endl;
	  exit(1);
	}

      std::cout << "Configuration's loading sucess" << std::endl;

      BrefValue			c = config.GetConfiguration();

      std::cout << c["RootSection"] << std::endl;
    }
}
