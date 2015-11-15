#pragma once

#include <ZILCH/Zilch.hpp>
#include <string>
#include <iostream>
#include <vector>

namespace GGEngine
{
  //using namespace Zilch;

  using stringVector = std::vector<std::string>;

  class JSONObject
  {
  public:
    JSONObject(Zilch::JsonValue *conversion);

    Zilch::JsonValue* getStorage();
    JSONObject GetMember(std::string name);

    // converters
    //! @todo: add more of these
    bool ToBool();
    std::string ToString();
    double ToDouble();
    float ToFloat();
    long long ToLongLong();
    int ToInt();

    std::vector<bool> ToBoolVector();
    std::vector<std::string> ToStringVector();
    std::vector<double> ToDoubleVector();
    std::vector<float> ToFloatVector();
    std::vector<long long> ToLongLongVector();
    std::vector<int> ToIntVector();

  private:
    Zilch::JsonValue* wrappedValue;
  };

  stringVector splitUp(const std::string& splitMe, char delim);
}
