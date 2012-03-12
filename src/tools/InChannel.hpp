
#ifndef			INCHANNEL_H_
# define		INCHANNEL_H_

# include		<string>
# include		<iostream>
# include		<fstream>

class			InChannel {
public:
  enum			eIn {
      IN_STDIN,
      IN_FILE
    };

/* ************************************************************************* */
/*                             Attributes                                    */
/* ************************************************************************* */
 private:
  eIn			in;
public:
  std::fstream		file;

/* ************************************************************************* */
/*                             Coplian Form                                  */
/* ************************************************************************* */
 public:
  InChannel(void);
  ~InChannel(void);

/* ************************************************************************* */
/*                             Getters/Setters                               */
/* ************************************************************************* */
 public:
  eIn				getIn(void) const;

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */
 public:
  bool				setInFile(std::string const &);
  void				setInStd(void);

public:
  bool				getNextLine(std::string &);
  // todo
  // std::string			getNextWord(void);
  // int				getNextNumber(void);
  // char				getNextChar(void);
  // double			getNextDouble(void);
};

#endif			// !INCHANNEL_H_

