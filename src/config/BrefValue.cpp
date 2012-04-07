#include "BrefValue.h"

using namespace bref;

static const std::string	&INVALID_STRING_VALUE = "";
static const int		INVALID_INT_VALUE = 42;
static const bool		INVALID_BOOL_VALUE = false;
static const BrefValueList	INVALID_LIST_VALUE;
static const BrefValueArray	INVALID_ARRAY_VALUE;
static BrefValue		VALUE_NOT_FOUND = BrefValue();

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

BrefValue::BrefValue(const BrefValueList &vl)
: type_(listType),
  listValue_(vl)
{
}

BrefValue::BrefValue(const BrefValueArray &va)
: type_(arrayType),
  arrayValue_(va)
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

bool			BrefValue::isList() const {
  return (type_ == listType);
}

bool			BrefValue::isArray() const {
  return (type_ == arrayType);
}
// Getters

const std::string	&BrefValue::asString() const {
  if (!isString())
    return INVALID_STRING_VALUE;

  return stringValue_;
}

int			BrefValue::asInt() const {
  if (!isInt())
    return INVALID_INT_VALUE;

  return intValue_;
}

bool			BrefValue::asBool() const {
  if (!isBool())
    return INVALID_BOOL_VALUE;

  return boolValue_;
}

const BrefValueList	&BrefValue::asList() const {
  if (!isList())
    return INVALID_LIST_VALUE;

  return listValue_;
}

const BrefValueArray	&BrefValue::asArray() const {
  if (!isArray())
    return INVALID_ARRAY_VALUE;

  return arrayValue_;
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
  if (type_ != listType) {
    if (type_ != nullType)
      listValue_.push_back(*this);
    type_ = listType;
  }

  listValue_.push_back(node);
}

void			BrefValue::setNull() {
  type_ = nullType;
}
