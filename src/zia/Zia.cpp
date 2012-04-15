
#include		"Zia.hpp"

namespace http {
	void init_literals();
}

/* ************************************************************************* */
/*                             Coplian Form                                  */
/* ************************************************************************* */

Zia::Zia(void)
  : network() {}

Zia::Zia(Zia const & other)
  : network(other.network) {
  config.LoadDefaultConfig();
}

Zia &		Zia::operator=(Zia const & other) {
  if (&other != this) {
    this->network = other.network;

      // If there is a pointer to something allocated, do this :
      // if (this->SomeThingAllocated)
      //   delete this->SomeThingAllocated;
      // this->SomeThingAllocated = CopyFunc(other.SomeThingAllocated);
  }
  return *this;
}

Zia::~Zia(void) {}

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */

bool			Zia::init(void) {
  http::init_literals();
  if (!(this->network.openConnection()))
    return false;

  return true;
}

bool			Zia::load_config(const std::string &path) {
  return config.LoadFromFile(path);
}

void			Zia::load_config(Configuration &c) {
  config.LoadFromConfiguration(c);
}

bool			Zia::run(void) {
  return true;
}
