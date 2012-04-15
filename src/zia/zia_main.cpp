
//#include	"zia.h"
#include	"zia/Zia.hpp"

bool		zia_main(void)
{
  Zia		zia;

  return (zia.init()
	  && zia.run());
}
