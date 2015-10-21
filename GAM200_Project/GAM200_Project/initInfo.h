#ifndef LUAINIT_H
#define LUAINIT_H

#include "runLua/luaTranslate.h"
#include "runLua/luaRunner.h"

void luaInitFile();

class initInfo
{
public:
  initInfo();
  std::string windowTitle;
  int clientWidth;
  int clientHeight;
  int FPSlimit;

  std::string atlasPNG;
  std::string atlasINFO;
};

extern initInfo * INITINFO;

#endif // LUAINIT_H
