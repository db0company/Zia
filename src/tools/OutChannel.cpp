
#include		"OutChannel.hpp"

/* ************************************************************************* */
/*                             Coplian Form                                  */
/* ************************************************************************* */

OutChannel::OutChannel(void)
  : out(OutChannel::OUT_STDOUT), file() {
}

OutChannel::~OutChannel(void) {
  this->file.close();
}

/* ************************************************************************* */
/*                             Getters/Setters                               */
/* ************************************************************************* */

OutChannel::eOut	OutChannel::getOut(void) const {
  return this->out;
}

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */

bool			OutChannel::setOutFile(std::string const & filename,
					       bool trunc) {
  this->file.close();
  this->file.open(filename.c_str(), (trunc ? std::ios::out | std::ios::trunc : std::ios::out));
  if (!this->file.is_open()) {
    this->out = OutChannel::OUT_STDOUT;
    return false;
  }
  this->out = OutChannel::OUT_FILE;
  return true;
}

void			OutChannel::setOutStd(void) {
  this->file.close();
  this->out = OutChannel::OUT_STDOUT;
}

