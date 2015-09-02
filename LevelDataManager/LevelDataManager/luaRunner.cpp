#include "luaRunner.h"

void luaRunner::printError(lua_State *L, int status)
{
  if (status!=0)
  {
    std::cerr << "LUA RUN ERROR:\n" << lua_tostring(L, -1) << std::endl;
    lua_pop(L, 1); // remove error message
  }
}

void luaRunner::runFile(std::string fileName)
{
  lua_State *L = luaL_newstate();

  luaL_openlibs(L);

  int s = luaL_loadfile(L, fileName.c_str());

  if(s == 0)//file can actually be loaded
  {
    s = lua_pcall(L, 0, LUA_MULTRET, 0);
    printError(L, s);
  }
  
  lua_close(L);
  std::cerr << std::endl;
}