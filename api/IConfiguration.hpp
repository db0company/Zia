/*
 * iconfiguration.hpp for zia
 * by le-cor_w
 */

#ifndef __ICONFIGURATION_HPP__
# define __ICONFIGURATION_HPP__

#include <map>
#include <list>
#include <ostream>

namespace zia {
  namespace config {

    enum Data_type {
	STRING,
	INT,
	DOUBLE,
    };

    class Node {

    private:

      Data_type				_type;
      std::string			_name;
      std::string			_value;
      std::list<Node>			_subnodes;

    public:

      Node() {}
      Node(const std::string &n, const std::string &v) : _name(n), _value(v) {}

      virtual ~Node() {}

      // Overload of operator== to provide a keys matching test easily
      virtual bool			operator==(const std::string &) const;

      virtual Node			&operator=(const Node &);
      virtual Node			&operator=(const std::string &);

      // Nodes agregation with replacement if necessary
      virtual Node			&operator+=(const Node &);

      /* Access to the subnode matching key given as the first parameter
	 if the subnode doesn't exist, it will be created */
      virtual Node			&operator[](const std::string &);

      /* Read-only access to the subnode matching key given as the first parameter
	 it requires the subnodes to be existing */
      virtual const Node		&operator[](const std::string &) const;

      /* Return std::string corresponding to the value of the Node */
      virtual const std::string		&getValue() const;

      /* Return std::string corresponding to the Key of the Node */
      virtual const std::string		&getName() const;

      /* Return true if there's a subnode matching the key given in parameter */
      virtual bool			has(const std::string &) const;

      /* Return the subnode matching the key given in parameter */
      virtual Node			&get(const std::string &);

      /* Display the node recursively with the 2nd parameter as a limit for the depth,
	 the third parameter is the number of nodes-levels already displayed : the
	 function stop itself when third parameter == depth */
      virtual void			dump(std::ostream &, int depth = 0, int = 0) const;
    };

    class IConfiguration {

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
