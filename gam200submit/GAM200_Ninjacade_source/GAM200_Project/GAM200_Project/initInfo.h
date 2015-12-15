/******************************************************************************/
/*!
\author Nolan Yoo
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/

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
  bool showConsole;

  bool playTheme;

  std::string atlasPNG;
  std::string atlasINFO;
};

extern initInfo * INITINFO;

#endif // LUAINIT_H
