#include <iostream>
#include <string>
#include <ZILCH/Zilch.hpp>

#include "../Samples/DemoTweakable.hpp"

#include "logger.hpp"
#include "SerializeSupport.hpp"

#include <ostream>
#include <iterator>

void waitForKB()
{
  std::cout << "Press Enter or Return to continue..." << std::endl;
  fseek(stdin, 0, SEEK_END);
  while (getchar() != '\n');
}

using namespace GGEngine;

void Test3()
{
  JSONWriter testWriter;

  //start root
  testWriter.Begin(JMODE::Object);
  {
    testWriter.Key("Root");
    testWriter.Begin(JMODE::Object);
    {
      testWriter.Key("DemoTweakable");
      testWriter.Begin(JMODE::Object);
      {
        testWriter.Key("Merry Xmas");
        testWriter.Value("Falalalalala");
        testWriter.Key("aTweakableVar");
        testWriter.Value(20);
        testWriter.Key("Nonexistent");
        testWriter.Null();
      }
      testWriter.End();
    }
    testWriter.End();
  }
  testWriter.End();
  std::cout << "Saw JSON:\n" << testWriter.ToString() << std::endl;
  testWriter.Update("Root.DemoTweakable.aTweakableVar", 29);
  testWriter.Update("Root.DemoTweakable.Merry Xmas", 777);
  testWriter.Update("Root.DemoTweakable.Nonexistent", true);
  std::cout << "Saw JSON:\n" << testWriter.ToString() << std::endl;

  //testWriter.locateKey("tet");
  waitForKB();
}

void Test2()
{
  JSONParser testParser("json.txt");
  testParser.Init();

  JSONObject subTest1 = testParser.Get("Root.PLAYER.__comments");
  std::cout << "Tried to reparse \"Root.PLAYER.__comments\" with JSONParser." << std::endl;
  std::cout << "Result: " << subTest1.ToString() << std::endl;

  JSONObject subTest2 = testParser.Get("Root.PLAYER.Infinite Lives");
  std::cout << "Tried to reparse \"Root.PLAYER.Infinite Lives\" with JSONParser." << std::endl;
  std::cout << "Result: " << std::boolalpha << subTest2.ToBool() << std::endl;

  JSONObject subTest3 = testParser.Get("Root.PLAYER.Spawn Position 1");
  std::cout << "Tried to reparse \"Root.PLAYER.Spawn Position 1\" with JSONParser." << std::endl;
  std::vector<float> floatVecT3 = subTest3.ToFloatVector();
  
  std::ostringstream floatVecT3Oss;

  floatVecT3Oss << '[';
  if (!floatVecT3.empty())
  {
    //avoid a trailing ","
    std::copy(floatVecT3.begin(), floatVecT3.end() - 1,
              std::ostream_iterator<float>(floatVecT3Oss, ", "));

    floatVecT3Oss << floatVecT3.back();
  }
  floatVecT3Oss << ']';
  std::cout << "Result: " << floatVecT3Oss.str() << std::endl;

  waitForKB();
}

void Test1(std::string nameObj1, bool extendTest)
{
  using namespace Zilch;

  ZilchSetup setup(StartupFlags::None);
  JsonBuilder toJson;

  // start root
  toJson.Begin(JsonType::Enum::Object);
  {
    toJson.Key("Root");
    toJson.Begin(JsonType::Enum::Object);
    {
      // main demo object
      toJson.Key("PLAYER");
      toJson.Begin(JsonType::Enum::Object);
      {
        toJson.Key("__comments");
        toJson.Value("I've got a lovely bunch of coconuts.");
        toJson.Key("Health");
        toJson.Value(10.0f);
        toJson.Key("Health Recharge");
        toJson.Value(0.0f);
        toJson.Key("Stamina");
        toJson.Value(10.0f);
        toJson.Key("Stamina Recharge");
        toJson.Value(1.3f);
        toJson.Key("Movement Speed");
        toJson.Value(4.0f);
        toJson.Key("Lives");
        toJson.Value(3);
        toJson.Key("Infinite Lives");
        toJson.Value(false);
        toJson.Key("Ability GCD");
        toJson.Value(1.0f);
        toJson.Key("Post-Spawn Invulnerability");
        toJson.Value(1.0f);
        toJson.Key("Respawn Time");
        toJson.Value(2.5f);
        toJson.Key("Spawn Position 1");
        toJson.Begin(JsonType::Enum::ArraySingleLine);
        toJson.Value(0.3f);
        toJson.Value(3.0f);
        toJson.Value(0.0f);
        toJson.End();
        toJson.Key("Spawn Position 2");
        toJson.Begin(JsonType::Enum::ArraySingleLine);
        toJson.Value(0.0f);
        toJson.Value(0.0f);
        toJson.Value(0.0f);
        toJson.End();
        toJson.Key("Spawn Position 3");
        toJson.Begin(JsonType::Enum::ArraySingleLine);
        toJson.Value(0.0f);
        toJson.Value(0.0f);
        toJson.Value(0.0f);
        toJson.End();
        toJson.Key("Spawn Position 4");
        toJson.Begin(JsonType::Enum::ArraySingleLine);
        toJson.Value(0.0f);
        toJson.Value(0.0f);
        toJson.Value(0.0f);
        toJson.End();
      }
      toJson.End();

      // something else showing boolean
      toJson.Key("BASIC ATTACK");
      toJson.Begin(JsonType::Enum::Object);
      {
        toJson.Key("happy");
        toJson.Value(true);
      }
      toJson.End();
    }
    toJson.End();
  }
  toJson.End();

  // print as char* to console
  std::cout << toJson.ToString().c_str() << std::endl;
  waitForKB();

  // if we're trying the stuff I don't know well
  if (extendTest)
  {
    txtlog helpJson;

    //brutally hammer the data into json.txt
    helpJson.hammerFile(toJson.ToString().c_str(), "json.txt");

    // Zilch specific helpers
    static const Zero::String Origin("Searching JSON data");
    CompilationErrors errors;
    std::string jsondata = helpJson.goFetch("json.txt");

    // attempt the read
    JsonValue* theWholeTree = JsonReader::ReadIntoTreeFromString(errors, jsondata.c_str(), Origin, nullptr);
    if (theWholeTree == nullptr)
    {
      std::cout << "Nothing was read... :(" << std::endl;
    }
    else
    {
      // go look for the demo object's name
      std::string foundName =
        theWholeTree->GetMember("Root")->
          GetMember("PLAYER")->
            GetMember("__comments")->AsString().c_str();
      std::cout << "Saw comment saying \"" << foundName << "\"" << std::endl;
    }
    waitForKB();
  }
}

int main(int argc, char *argv[])
{
  Test1("DemoTweakable1", true);
  Test2();
  Test3();
  return 0;
}
