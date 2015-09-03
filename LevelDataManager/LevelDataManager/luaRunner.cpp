/* loosely based on:
 https://github.com/EliasD/unnamed_lua_binder/
 http://lua-users.org/wiki/CppLuaDataPassing
 */

#include "luaRunner.h"

void luaRunner::printError(lua_State *L, int status)
{
  //possible that there are no errors to report
  if (status != 0)
  {
    std::cerr << "LUA RUN ERROR:\n" << lua_tostring(L, -1) << std::endl;
    lua_pop(L, 1); //remove printed error
  }
}

void luaRunner::printError(const std::string& source, const std::string& reason)
{
  std::cerr << "LUA RUN ERROR:\n(" << source<<"): " << reason << std::endl;
}

void luaRunner::runFile(const std::string& fileName)
{
  lua_State *local = luaL_newstate();

  int fileCall = luaL_loadfile(local, fileName.c_str());

  if(fileCall == 0)//file can actually be ran
  {
    luaL_openlibs(local);
    fileCall = lua_pcall(local, 0, LUA_MULTRET, 0);
    printError(local, fileCall);
  }

  lua_close(local);
}

void luaRunner::loadFile(const std::string& fileName)
{
  running = luaL_newstate();

  int fileCall = luaL_loadfile(running, fileName.c_str());

  if (fileCall == 0)//file can actually be loaded
  {
    luaL_openlibs(running);
    fileCall = lua_pcall(running, 0, LUA_MULTRET, 0);
    printError(running, fileCall);
  }
  else
  {
    std::cout<<"LUA INIT ERROR:\nfailed to load \""<<fileName<<'\"'<<std::endl;
    running = nullptr;
  }

  if(running)
  {
    luaL_openlibs(running);
  }
}

bool luaRunner::lua_checkstack(const std::string& request)
{
  depth = 0;//start at top of field
  std::string name = "";

  //search through string
  for(int i = 0; i < request.size(); i++)
  {
    if(request.at(i) == '.')//attribute of some sort requested
    {
      if(depth == 0)//top level
      {
        lua_getglobal(running, name.c_str());//get table or object
      }
      else
      {
        lua_getfield(running, -1, name.c_str());//directly get member of table or object
      }

      if(!lua_isnil(running, -1))
      {
        //object or attribute was found; increment depth and clear name
        name = "";
        depth++;
      }
    }
    else
    {
      //add current char to string
      name.push_back(request.at(i));
    }
  }

  if(depth == 0)
  {
    lua_getglobal(running, name.c_str());
  }
  else
  {
    lua_getfield(running, -1, name.c_str());
  }

  if(lua_isnil(running, -1))
  {
    printError(request, name + " not found");
    return false;
  }
  return true;
}

void luaRunner::popTop()
{
  lua_pop(running, lua_gettop(running));
}
