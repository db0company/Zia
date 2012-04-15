#ifndef			ZIA_H_
# define		ZIA_H_

# include		"network/ZiaNetwork.hpp"
#include		"config/Configuration.hpp"

class			Zia
{
/* ************************************************************************* */
/*                             Attributes                                    */
/* ************************************************************************* */
 private:
  ZiaNetwork			network;
  Configuration			config;

/* ************************************************************************* */
/*                             Coplian Form                                  */
/* ************************************************************************* */
 public:
  Zia(std::string const& = "");
  Zia(Zia const &);
  Zia &			operator=(Zia const &);
  ~Zia(void);

/* ************************************************************************* */
/*                             Member Functions                              */
/* ************************************************************************* */
 public:
  bool				init(void);
  bool				run(void);
  bool				load_config(const std::string &);
  void				load_config(Configuration &);
};

#endif			// !ZIA_H_

