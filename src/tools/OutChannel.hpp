
#ifndef			OUTCHANNEL_H_
# define		OUTCHANNEL_H_

# include		<string>
# include		<iostream>
# include		<fstream>

class			OutChannel {
 public:
  enum			eOut {
    OUT_STDOUT,
    OUT_FILE
  };

  enum			eEndl {
    ENDLINE,
    NO_ENDLINE
  };

/* ************************************************************************* */
/*                             Attributes                                    */
/* ************************************************************************* */
 private:
  eOut				out;
  std::ofstream			file;

/* ************************************************************************* */
/*                             Coplian Form                                  */
/* ************************************************************************* */
 public:
  OutChannel(void);
  OutChannel(OutChannel const &);
  OutChannel &		operator=(OutChannel const &);
  ~OutChannel(void);

/* ************************************************************************* */
/*                             Getters/Setters                               */
/* ************************************************************************* */
 public:
  eOut			getOut(void) const;

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */
 public:
  bool			setOutFile(std::string const &,
				   bool trunc = true);
  void			setOutStd(void);

  template <class T>
  void			put(T const & t, eEndl endline = NO_ENDLINE) {
    if (endline == ENDLINE)
      (this->out == OUT_STDOUT ? std::cout : this->file) << t << std::endl;
    else
      (this->out == OUT_STDOUT ? std::cout : this->file) << t;
  }

  template <class T>
  OutChannel &		operator<<(T const & t) {
    this->put(t);
    return (*this);
  }

  template <class T>
  bool			putError(T const & t, eEndl endline = ENDLINE) {
    if (endline == ENDLINE)
      (this->out == OUT_STDOUT ? std::cerr : this->file) << t << std::endl;
    else
      (this->out == OUT_STDOUT ? std::cerr : this->file) << t;
    return (false);
  }
  // void			putNextLine(std::string const &);
  // void			putError(std::string const &);
};

#endif			// !OUTCHANNEL_H_

