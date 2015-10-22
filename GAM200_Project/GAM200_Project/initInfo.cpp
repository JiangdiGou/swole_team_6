#include "initInfo.h"

void luaInitFile()
{
  initInfo *constructGlobal = new initInfo();
  luaRunner iniFile;
  iniFile.runFile("Scripts/ini.lua");
  INITINFO->windowTitle = iniFile.get<std::string>("init.windowTitle");
  INITINFO->clientWidth = iniFile.get<int>("init.clientWidth");
  INITINFO->clientHeight = iniFile.get<int>("init.clientHeight");
  INITINFO->FPSlimit = iniFile.get<int>("init.FPSlimit");
  INITINFO->atlasPNG = iniFile.get<std::string>("init.atlasPNG");
  INITINFO->atlasINFO = iniFile.get<std::string>("init.atlasINFO");
  iniFile.stop();
}

initInfo::initInfo()
{
  INITINFO = this;
}