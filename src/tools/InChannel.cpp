
#include		"InChannel.hpp"

/* ************************************************************************* */
/*                             Coplian Form                                  */
/* ************************************************************************* */

InChannel::InChannel(void)
  : in(InChannel::IN_STDIN), file() {
}

InChannel::~InChannel(void) {
  this->file.close();
}

/* ************************************************************************* */
/*                             Getters/Setters                               */
/* ************************************************************************* */

InChannel::eIn		InChannel::getIn(void) const {
  return this->in;
}

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */

bool			InChannel::setInFile(std::string const & filename) {
  this->file.close();
  this->file.open(filename.c_str(), std::ios::in);
  if (!this->file.is_open()) {
    this->in = InChannel::IN_STDIN;
    return false;
  }
  this->in = InChannel::IN_FILE;
  return true;
}

void			InChannel::setInStd(void) {
  this->file.close();
  this->in = InChannel::IN_STDIN;
}

bool			InChannel::getNextLine(std::string & str) {
  if (this->in == InChannel::IN_STDIN) {
    if (!(getline(std::cin, str)))
      return false;
  } else {
    if (!(getline(this->file, str)))
      return false;
  }
  return true;
}

