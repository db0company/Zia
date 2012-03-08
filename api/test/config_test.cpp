/*
 * configuration_test for zia
 * by le-cor_w
 */

#include <assert.h>
#include <iostream>
#include "api/configuration.hpp"

int main()
{
  zia::api::config::Node config;

  config["Name"] = "Zia";
  config["Properties"]["Port"] = "8080";
  config["Properties"]["Timeout"] = "10";

  config.dump(std::cout, 5);
}
