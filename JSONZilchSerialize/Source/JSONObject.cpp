#include "JSONObject.hpp"

namespace GGEngine
{
  // expects to be initialized from JsonValue
  JSONObject::JSONObject(Zilch::JsonValue *conversion)
  {
    this->wrappedValue = conversion;
  }

  Zilch::JsonValue * JSONObject::getStorage()
  {
    return this->wrappedValue;
  }

  JSONObject JSONObject::GetMember(std::string name)
  {
    Zilch::JsonValue *wrapMe = this->wrappedValue->GetMember(name.c_str());
    return JSONObject(wrapMe);
  }

  // converter functions, self-explanatory
  bool JSONObject::ToBool()
  {
    return wrappedValue->AsBool();
  }

  std::string JSONObject::ToString()
  {
    return wrappedValue->AsString().c_str();
  }

  double JSONObject::ToDouble()
  {
    return wrappedValue->AsDouble();
  }

  float JSONObject::ToFloat()
  {
    return wrappedValue->AsFloat();
  }

  long long JSONObject::ToLongLong()
  {
    return wrappedValue->AsLongLong();
  }

  int JSONObject::ToInt()
  {
    return wrappedValue->AsInteger();;
  }

  std::vector<bool> JSONObject::ToBoolVector()
  {
    std::vector<bool> returnMe;
    Zilch::OwnedArray<Zilch::JsonValue *> elements = this->wrappedValue->ArrayElements;
    int len = elements.size();

    for (int i = 0; i < len; i++)
    {
      returnMe.push_back(elements[i]->AsBool());
    }

    return returnMe;
  }

  std::vector<std::string> JSONObject::ToStringVector()
  {
    std::vector<std::string> returnMe;
    Zilch::OwnedArray<Zilch::JsonValue *> elements = this->wrappedValue->ArrayElements;
    int len = elements.size();

    for (int i = 0; i < len; i++)
    {
      returnMe.push_back(elements[i]->AsString().c_str());
    }

    return returnMe;
  }

  std::vector<double> JSONObject::ToDoubleVector()
  {
    std::vector<double> returnMe;
    Zilch::OwnedArray<Zilch::JsonValue *> elements = this->wrappedValue->ArrayElements;
    int len = elements.size();

    for (int i = 0; i < len; i++)
    {
      returnMe.push_back(elements[i]->AsDouble());
    }

    return returnMe;
  }

  std::vector<float> JSONObject::ToFloatVector()
  {
    std::vector<float> returnMe;
    Zilch::OwnedArray<Zilch::JsonValue *> elements = this->wrappedValue->ArrayElements;
    int len = elements.size();

    for (int i = 0; i < len; i++)
    {
      returnMe.push_back(elements[i]->AsFloat());
    }

    return returnMe;
  }

  std::vector<long long> JSONObject::ToLongLongVector()
  {
    std::vector<long long> returnMe;
    Zilch::OwnedArray<Zilch::JsonValue *> elements = this->wrappedValue->ArrayElements;
    int len = elements.size();

    for (int i = 0; i < len; i++)
    {
      returnMe.push_back(elements[i]->AsLongLong());
    }

    return returnMe;
  }

  std::vector<int> JSONObject::ToIntVector()
  {
    std::vector<int> returnMe;
    Zilch::OwnedArray<Zilch::JsonValue *> elements = this->wrappedValue->ArrayElements;
    int len = elements.size();

    for (int i = 0; i < len; i++)
    {
      returnMe.push_back(elements[i]->AsInteger());
    }

    return returnMe;
  }

  // splits up a string according to a delimiter into a stringVector
  stringVector splitUp(const std::string& splitMe, char delim)
  {
    stringVector result;
    std::string copySplit(splitMe);

    size_t pos = 0;
    std::string part;

    // push portions up until the delimiter
    while ((pos = copySplit.find(delim)) != std::string::npos)
    {
      part = copySplit.substr(0, pos);
      copySplit.erase(0, pos + 1);
      result.push_back(part);
    }

    // if there's something left just push it
    if (copySplit.length() != 0)
    {
      result.push_back(copySplit);
    }

    return result;
  }

}