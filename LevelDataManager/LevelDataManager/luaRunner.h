#include <string>
#include <iostream>

extern "C"
{
  #include "luaLib/lua.h"
  #include "luaLib/lualib.h"
  #include "luaLib/lauxlib.h"
}

class luaRunner
{
public:
  void printError(lua_State *L, int status);
  void runFile(std::string);
};