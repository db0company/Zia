
#include	<cstdlib>
#include	<cstdio>
#include	<string>
#include	<iostream>
#include	"zia.h"

uint v = 0;

static bool	usage(std::string filename) {
  std::cerr << "usage: " << filename << " [-v]" << std::endl;
  return (false);
}

static bool	verbose(int argc, char ** argv) {
  int           c;

  while ((c = getopt(argc, argv, "v")) != EOF)
    {
      if (c == 'v')
	++v;
      else
	return (usage(*argv));
    }
  return (true);
}

int		main(int argc, char ** argv) {
  if (!(verbose(argc, argv)))
    return (EXIT_FAILURE);
  return (zia_main() ? EXIT_SUCCESS : EXIT_FAILURE);
}
