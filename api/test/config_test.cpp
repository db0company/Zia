/*
 * configuration_test for zia
 * by le-cor_w
 */

#include <assert.h>
#include <iostream>
#include <algorithm>
#include "api/configuration.hpp"

namespace zia
{
  namespace config
  {
    bool	Node::operator==(const std::string &key) const {
      return _name == key;
    }

    Node	&Node::operator=(const Node &other) {
      _value = other._value;
      _name = other._name;

      _subnodes = other._subnodes;

      return *this;
    }

    Node	&Node::operator=(const std::string &value) {
      _value = value;

      return *this;
    }

    Node	&Node::operator+=(const Node &other) {
      std::list<Node>::iterator it = _subnodes.begin();

      for (; it != _subnodes.end(); ++it)
	{
	  // TODO : Node agregation
	}
    }

    const Node &Node::operator[](const std::string &key) const {
      std::list<Node>::const_iterator it = find(_subnodes.begin(), _subnodes.end(), key);

      if (it != _subnodes.end())
	return *it;

      // TODO : Handling the non-existence of the subnode "key"
    }

    Node	&Node::operator[](const std::string &key) {
      if (!has(key))
	_subnodes.push_back(Node(key, ""));
      std::list<Node>::iterator it = find(_subnodes.begin(), _subnodes.end(), key);

      return *it;
    }

    const std::string &Node::getValue() const {
      return _value;
    }

    const std::string &Node::getName() const {
      return _name;
    }

    bool Node::has(const std::string &key) const {
      return (find(_subnodes.begin(), _subnodes.end(), key) != _subnodes.end());
    }

    Node	&Node::get(const std::string &key) {
      std::list<Node>::iterator it = find(_subnodes.begin(), _subnodes.end(), key);

      if (it != _subnodes.end())
	return *it;

      // TODO : Handling the non-existence of the subnode "key"
    }

    void	Node::dump(std::ostream &stream, int depth, int already_computed) const {
      if (depth <= 0)
	return;

      std::list<Node>::const_iterator it = _subnodes.begin();

      for (int i = already_computed; i; --i)
	stream << "\t";

      if (!_name.empty())
	stream << _name << ": ";

      if (!_value.empty())
	stream << _value;

      if (!_name.empty())
	stream << std::endl;

      for (; it != _subnodes.end(); ++it)
	it->dump(stream, depth - 1, already_computed + 1);
    }
  }
}

int main()
{
  zia::config::Node config;

  config["Name"] = "Zia";
  config["Properties"]["Port"] = "8080";
  config["Properties"]["Timeout"] = "10";

  config.dump(std::cout, 5);
}
