
#include	"zia/Zia.hpp"

#define DEFAULT_CONFIG_FILE "zia.conf"

bool		zia_main(void)
{
  Zia		zia(DEFAULT_CONFIG_FILE);

  return (zia.init()
	  && zia.run());
}
