#pragma once

#include <ZILCH/Zilch.hpp>
#include <string>
#include <vector>

#include <fstream>
#include <sstream>

#include "JSONObject.hpp"

namespace GGEngine
{

  class JSONParser
  {
  public:
    JSONParser();
    JSONParser(const std::string& fileName);
    void Init();

    // file management functions
    void Reload(const std::string& fileName);

    // seeking functions
    JSONObject Get(const std::string& request);

    // other helpers
    JSONObject* Storage();
  private:
    // private data
    bool active = false;
    std::string JsonLocation;
    JSONObject* JsonData;
  };

}