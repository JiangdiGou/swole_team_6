#pragma once

#include <ZILCH/Zilch.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "JSONObject.hpp"

namespace GGEngine
{

  //using namespace Zilch;

  // move this to CustomTypedefs.hpp (?)
  class JSONCmd;
  using jcmdVector = std::vector<JSONCmd>;
  using JMODE = Zilch::JsonType::Enum;

  // possible commands
  enum JCMD
  {
    JW_BEGIN,
    JW_KEY,
    JW_VALUE,
    JW_NULL,
    JW_END
  };

  // types JSONCmd is willing to hold
  enum JTYPE
  {
    JT_INT,
    JT_UINT,
    JT_LONG,
    JT_ULONG,
    JT_LONGLONG,
    JT_ULONGLONG,
    JT_DOUBLE,
    JT_STR,
    JT_BOOL,
    JT_NULL,
    JT_KEY,
    JT_ENUM
  };

  // hold anything JSONWriter can write
  struct JSONMorphic
  {
  public:
    JTYPE dataType;
    // the nonsense we might end up holding
    int dataInt = 0;
    unsigned int dataUnsignedInt = 0;
    long dataLong = 0;
    unsigned long dataUnsignedLong = 0;
    long long dataLongLong = 0;
    unsigned long long dataUnsignedLongLong = 0;
    double dataDouble = 0.0;
    std::string dataString = "";
    bool dataBool = false;
    Zilch::JsonType::Enum beginType;

  };

  class JSONCmd
  {
  public:
    JCMD command;
    JSONMorphic data;
  };

  class JSONWriter
  {
  public:
    // Get the resulting Json (only legal if it's completely closed)
    std::string ToString();

    // Start either a Json object or array
    // When inside an object, it's only legal to call this after creating a 'Member'
    // When inside an array, it is always legal to call this
    void Begin(JMODE type);

    // Start a key/member inside of an object (illegal to do at the root or inside an array)
    void Key(std::string name);

    // Write a value to Json (only legal as a member or in an array)
    void Value(int value);
    void Value(unsigned int value);
    void Value(long value);
    void Value(unsigned long value);
    void Value(long long value);
    void Value(unsigned long long value);
    void Value(double value);
    void Value(std::string value);
    void Value(cstr value);
    void Value(bool value);
    void Null();

    // Change a value in Json
    void Update(std::string fullKey, int value);
    void Update(std::string fullKey, unsigned int value);
    void Update(std::string fullKey, long value);
    void Update(std::string fullKey, unsigned long value);
    void Update(std::string fullKey, long long value);
    void Update(std::string fullKey, unsigned long long value);
    void Update(std::string fullKey, double value);
    void Update(std::string fullKey, std::string value);
    void Update(std::string fullKey, cstr value);
    void Update(std::string fullKey, bool value);

    // End a Json object or array
    void End();

    // Clear private data
    void Flush();

  private:
    // private data
    jcmdVector commands;  //also a flat tree

    // private helpers
    void BuildValue(const JSONMorphic* valueContainer, Zilch::JsonBuilder* myBuilder);
    JSONCmd* locateKey(std::string fullKey);
  };

}