
#include		"Zia.hpp"

namespace http {
	void init_literals();
}

/* ************************************************************************* */
/*                             Coplian Form                                  */
/* ************************************************************************* */

Zia::Zia(std::string const &path)
	: network(&config) {
	config.LoadDefaultConfig();
	if (!path.empty())
		config.LoadFromFile(path);
}

Zia::Zia(Zia const &other)
  : network(other.network) {
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
	int const port = config.GetConfiguration()["ZiaConfig"]["ListeningPort"].asInt();

	http::init_literals();
	if (!(this->network.openConnection(port)))
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
