#include <fstream>
#include <string>
#include <vector>
#include <tr1/functional>

#include "Configuration.hpp"
#include "yaml-cpp/yaml.h"

using namespace bref;

static const BrefValue VALUE_NOT_FOUND;

// Ctors/Dtors
Configuration::Configuration() : _value(BrefValue()) {
}

Configuration::~Configuration() {
}

// Miscellaneous

const BrefValue		&Configuration::findValue(const std::string &key) const {
  if (_value.isArray() && _value.hasKey(key))
    {
      BrefValueArray datas = _value.asArray();

      for (BrefValueArray::const_iterator it = datas.begin();
	   it != datas.end();
	   ++it)
	{
	  if (it->first == key)
	    return it->second;
	}
    }

  return VALUE_NOT_FOUND;
}

const BrefValue		&Configuration::findValue(const std::string &key,
						  const HttpRequest &request) const {

  // TODO : Deeper search in data tree depending on request parameters

  return findValue(key);
}

std::ostream &operator <<(std::ostream &out, BrefValue &v) {
  if (v.isString())
    out << v.asString() << std::endl;
  else if (v.isInt())
    out << v.asInt() << std::endl;
  else if (v.isBool())
    out << std::boolalpha << v.asBool();
  else if (v.isArray())
    {
      BrefValueArray ar = v.asArray();

      for (BrefValueArray::iterator it = ar.begin();
	   it != ar.end();
	   ++it)
	{
	  out << it->first << " : " << it->second;
	}
    }
  else if (v.isList())
    {
      out << std::endl;
      BrefValueList li = v.asList();

      for (BrefValueList::iterator it = li.begin();
	   it != li.end();
	   ++it)
	{
	  out << *it;
	}
    }
  else if (v.isNull())
    out << std::endl;

  return out;
}

void operator>>(const YAML::Node& node, BrefValue &v) {

  try
    {
      std::string	name;
      std::string	value;

      if (node.Type() == YAML::NodeType::Scalar)
	{
	  node >> value;
	  v = BrefValue(value);
	  return;
	}

      const YAML::Node *node_name =   node.FindValue("name");
      const YAML::Node *node_values =   node.FindValue("value");

      if (!node_name)
	throw ConfigExcept{"Node \"Name\" must be defined"};
      if (!node_values)
	throw ConfigExcept{"Node \"Values\" must be defined"};

      if (node_name->Type() != YAML::NodeType::Scalar)
	return;

      *node_name >> name;
      v[name] = BrefValue();

      if (node_values->Type() != YAML::NodeType::Scalar)
	{
	  for (YAML::Iterator it = node_values->begin();
	       it != node_values->end();
	       ++it)
	    {
	      BrefValue t = BrefValue();

	      *it >> t;
	      v[name].push(t);
	    }
	}
      else
	{
	  *node_values >> value;
	  v[name] = BrefValue(value);
	}
    }
  catch (std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      throw ConfigExcept{"Configuration file doesn't respect YAML standards, aborting and loading default configuration"};
    }
}

bool			Configuration::LoadFromFile(const std::string &input_file) {

  try
    {
      std::ifstream fin(input_file.c_str());

      if (!fin.is_open())
	return false;

      BrefValue		tmp;

      YAML::Parser parser(fin);
      YAML::Node doc;
      parser.GetNextDocument(doc);

      BrefValueList li;

      for (unsigned i = 0;
	   i < doc.size();
	   i++)
	{
	  doc[i] >> tmp;
	}

      _value = tmp;
      return true;
    }
  catch (std::exception &c)
    {
      return false;
    }
}

BrefValue		&Configuration::GetConfiguration() {
  return _value;
}
