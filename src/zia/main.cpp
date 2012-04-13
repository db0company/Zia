
#include	<cstdlib>
#include	<cstdio>
#include	<string>
#include	<iostream>
#include	"zia.h"

#ifdef _WIN32
_Uint32t v = 0;
#elif
uint v = 0;
#endif

static bool	usage(std::string filename) {
  std::cerr << "usage: " << filename << " [-v]" << std::endl;
  return (false);
}

static bool	verbose(int argc, char ** argv) {
#ifdef _WIN32
#elif
  int           c;

  while ((c = getopt(argc, argv, "v")) != EOF)
    {
      if (c == 'v')
	++v;
      else
	return (usage(*argv));
    }
#endif
  return (true);
}

int		main(int argc, char ** argv) {
  if (!(verbose(argc, argv)))
    return (EXIT_FAILURE);
  return (zia_main() ? EXIT_SUCCESS : EXIT_FAILURE);
}
