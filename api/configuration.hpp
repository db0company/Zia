/*
 * configuration.hpp for zia
 * by le-cor_w
 */

#ifndef __CONFIGURATION_HPP__
# define __CONFIGURATION_HPP__

#include <map>
#include <list>
#include <ostream>

namespace zia
{
  namespace api
  {
    namespace config
    {

      enum Format
	{
	  INI,
	  XML,
	  JSON,
	};

      class Node
      {

      public:

	std::string			_value;
	std::list<std::string>		_values;

	std::map<std::string, Node>	_subnodes;

      public:

	virtual ~Node() {}

	virtual Node		&operator=(const Node &) = 0;
	virtual Node		&operator=(const std::string &) = 0;
	virtual Node		&operator+=(const Node &) = 0;
	virtual Node		&operator[](const std::string &) = 0;
	virtual const Node	&operator[](const std::string &) const = 0;
	virtual std::string	&getValue() const = 0;
	virtual bool		has(const std::string &) const = 0;
	virtual Node		&get(const std::string &) const = 0;
	virtual void		dump(std::ostream &, int depth = -1) const = 0;
      };

      class Config
      {
	Node				_datas;

      public:

	virtual void	setDefault(const Node *) = 0;
	virtual void	setDefault(const Node &) = 0;

	virtual Node	&setDefault() const = 0;

	virtual void	loadDefault() = 0;
	virtual	bool	loadConfig(const std::string &path, Format = zia::api::config::INI) = 0;
	virtual	bool	loadConfig(const Node &) = 0;
	virtual	bool	loadConfig(const Node *) = 0;

	virtual void	saveConfig(Node *dst) const = 0;

	virtual void	unloadConfig() = 0;
      };
    }
  }
}

#endif /* __CONFIGURATION_HPP__ */
