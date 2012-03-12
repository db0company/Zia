/*
 * iconfiguration.hpp for zia
 * by le-cor_w
 */

#ifndef __ICONFIGURATION_HPP__
# define __ICONFIGURATION_HPP__

#include <map>
#include <list>
#include <ostream>

namespace zia
{
  namespace config
  {

    enum Data_type
      {
	STRING,
	INT,
	DOUBLE,
      };

    class Node
    {

    public:

      Data_type				_type;
      std::string			_name;
      std::string			_value;
      std::list<Node>			_subnodes;

    public:

      Node() {}
      Node(const std::string &n, const std::string &v) : _name(n), _value(v) {}

      virtual ~Node() {}

      virtual bool			operator==(const std::string &) const;
      virtual Node			&operator=(const Node &);
      virtual Node			&operator=(const std::string &);
      virtual Node			&operator+=(const Node &);
      virtual Node			&operator[](const std::string &);
      virtual const Node		&operator[](const std::string &) const;
      virtual const std::string		&getValue() const;
      virtual const std::string		&getName() const;
      virtual bool			has(const std::string &) const;
      virtual Node			&get(const std::string &);

      virtual void			dump(std::ostream &, int depth = 0, int = 0) const;
    };

    class IConfiguration
    {

    public:

      virtual	~IConfiguration() {}

      virtual	void	setDefault(const Node *) = 0;
      virtual	void	setDefault(const Node &) = 0;
      virtual	Node	&getDefault() const = 0;

      // A few functions providing ways to load configuration from file(s) or existing configuration(s)

      virtual	void	loadDefault() = 0;

      virtual	bool	loadConfig(const std::string &path) = 0;
      virtual	bool	loadConfig(const Node &) = 0;
      virtual	bool	loadConfig(const Node *) = 0;

      virtual	void	saveConfig(Node *dst) const = 0;
      virtual	void	unloadConfig() = 0;
    };
  }
}

#endif /* __ICONFIGURATION_HPP__ */
