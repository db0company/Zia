#include "BrefValue.h"

using namespace bref;

static const std::string	&INVALID_STRING_VALUE = "";
static const int		INVALID_INT_VALUE = 42;
static const bool		INVALID_BOOL_VALUE = false;

// Ctors/Dtors

BrefValue::BrefValue()
  : type_(nullType)
{
}

BrefValue::BrefValue(double value)
  : type_(intType),
    intValue_(static_cast<int>(value))
{
}

BrefValue::BrefValue(bool value)
  : type_(boolType),
    boolValue_(value)
{
}

BrefValue::BrefValue(const std::string &value)
  : type_(stringType),
    stringValue_(value)
{
}

BrefValue::BrefValue(int value)
: type_(intType),
  intValue_(value)
{
}

// Tests

bool			BrefValue::isString() const {
  return (type_ == stringType);
}

bool			BrefValue::isInt() const {
  return (type_ == intType);
}

bool			BrefValue::isBool() const {
  return (type_ == boolType);
}

// Getters

const std::string	&BrefValue::asString() const {
  if (type_ != stringType)
    return INVALID_STRING_VALUE;

  return stringValue_;
}

int			BrefValue::asInt() const {
  if (type_ != intType)
    return INVALID_INT_VALUE;

  return intValue_;
}

bool			BrefValue::asBool() const {
  if (type_ != boolType)
    return INVALID_BOOL_VALUE;

  return boolValue_;
}

bool			BrefValue::hasKey(const std::string &key) const {
  if (type_ != arrayType)
    return false;

  for (BrefValueArray::const_iterator it = arrayValue_.begin();
       it != arrayValue_.end();
       ++it)
    if (it->first == key)
      return true;

  return false;
}

BrefValue		&BrefValue::operator[](const std::string &key) {
  return arrayValue_[key];
  /*
  if (!hasKey(key))
  return VALUE_NOT_FOUND;

  for (BrefValueArray::const_iterator it = arrayValue_.begin();
       it != arrayValue_.end();
       ++it)
    if (it->first == key)
      return it->second;

return VALUE_NOT_FOUND;
  */
}

// Setters

void			BrefValue::setString(const std::string &value) {
  type_ = stringType;
  stringValue_ = value;
}

void			BrefValue::setBool(bool value) {
  type_ = boolType;
  boolValue_ = value;
}

void			BrefValue::setInt(int value) {
  type_ = intType;
  intValue_ = value;
}

// Miscellaneous

void			BrefValue::push(const BrefValue &node) {
  listValue_.push_back(node);
}

void			BrefValue::setNull() {
  type_ = nullType;
}
