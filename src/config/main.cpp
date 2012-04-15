#include <iostream>

#include "BrefValue.h"
#include "Configuration.hpp"

using namespace bref;

// Compiling instructions : g++ main.cpp Configuration.cpp BrefValue.cpp ../zia/baseexcept.cpp -I../../bref-api/include/bref/ -lyaml-cpp -std=c++0x -I../tools/ -I../../include/
// Testing instructions : ./a.out .zia-config

BrefValue load_default_config() {
  BrefValue	c;

  c["RootSection"]["DocumentRoot"].setString("/var/www/");
  c["RootSection"]["ListeningPort"].setInt(8080);

  return c;
}
int main(int ac, char **av)
{
  if (ac > 1)
    {
      Configuration		config;
      BrefValue			v = load_default_config();

      config.LoadFromConfiguration(v);

      if (!config.LoadFromFile(av[1]))
	std::cout << "Configuration's loading has failed, default configuration loaded.." << std::endl;
      else
	std::cout << "Configuration's loading sucess" << std::endl;

      BrefValue			c = config.GetConfiguration();

      std::cout << c["VirtualHosts"];
      std::cout << "DocumentRoot for vhost www.example.fr=" << c["VirtualHosts"]["www.example.fr"]["DocumentRoot"];
    }
}
