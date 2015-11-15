#include "JSONParser.hpp"

namespace GGEngine
{
  using namespace Zilch;

  JSONParser::JSONParser()
  {
  }

  JSONParser::JSONParser(const std::string& fileName)
  {
    this->JsonLocation = std::string(fileName);
  }

  // link the parser to Zilch and use the data from constructor-specified file
  void JSONParser::Init()
  {
    this->active = true;

    // zilch requirements
    ZilchSetup setup(StartupFlags::None);
    static const Zero::String Origin("Searching JSON data");
    CompilationErrors errors;

    // attempt file read
    std::ifstream fromFile(this->JsonLocation);
    std::stringstream buffer;
    buffer << fromFile.rdbuf();

    // string read file
    std::string readData = buffer.str();

    // attempt the conversion to JsonValue and member variable
    JsonValue* theWholeTree = JsonReader::ReadIntoTreeFromString(errors, readData.c_str(), Origin, nullptr);
    this->JsonData = new JSONObject(theWholeTree);
  }


  //! @todo: implement in entirety
  void JSONParser::Reload(const std::string& fileName)
  {
    this->JsonLocation = std::string(fileName);
    this->Init();
  }

  // gets a JSONObject from a JSONParser
  JSONObject JSONParser::Get(const std::string& request)
  {
    JsonValue *seeker = this->JsonData->getStorage();
    stringVector splitRequest = splitUp(request.c_str(), '.');

    // continuously get members whilst the syntax demands it
    for (stringVector::iterator iter = splitRequest.begin(); iter != splitRequest.end(); ++iter)
    {
      seeker = seeker->GetMember(iter->c_str());
    }
    return *(new JSONObject(seeker));
  }
  JSONObject * JSONParser::Storage()
  {
    return this->JsonData;
  }
}
