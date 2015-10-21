//author Nolan Yoo

#include "../logger/logger.h"
#include "luaRunner.h"
#include "../Utilities.h"

void luaRunner::sendStr(std::string arg)
{
  macAppend = arg;
}

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
  //lua_State *local = luaL_newstate();
  running = luaL_newstate();
  std::string trueName = "";

#ifndef _WIN32
  trueName += macAppend;
#endif
  trueName += fileName;
  int fileCall = luaL_loadfile(running, trueName.c_str());

  if(fileCall == 0)//file can actually be ran
  {
    luaL_openlibs(running);
    fileCall = lua_pcall(running, 0, LUA_MULTRET, 0);
    printError(running, fileCall);
  }

  //lua_close(running);
}

void luaRunner::stop()
{
  lua_close(running);
}

void luaRunner::loadFile(const std::string& fileName)
{
  running = luaL_newstate();
  std::string trueName = "";

#ifndef _WIN32
  trueName += macAppend;
#endif
  trueName += fileName;
  int fileCall = luaL_loadfile(running, trueName.c_str());

  if (fileCall == 0)//file can actually be loaded
  {
    luaL_openlibs(running);
    fileCall = lua_pcall(running, 0, LUA_MULTRET, 0);
    printError(running, fileCall);
  }
  else
  {
    std::cout<<"LUA INIT ERROR:\nfailed to load \""<<trueName<<'\"'<<std::endl;
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

lua_State* luaRunner::getState()
{
  return this->running;
}

std::vector<multiType> luaRunner::getTable(std::string tableName)
{
  std::vector<multiType> returnMe;

  lua_getglobal(running, tableName.c_str());
  lua_pushnil(running);

  while(lua_next(running, -2))
  //for (lua_pushnil(running); lua_next(running, -2); lua_pop(running, 1))
  {
    printstr("trying something...");
    multiType pushMe = *new multiType();
    if(lua_isnumber(running, -1))
    {
      float checkMe = lua_tonumber(running, -1);
      if(isReallyInt(checkMe))
      {
        pushMe.integer = (int)checkMe;
        pushMe.wrapperType = ISINT;
        returnMe.push_back(pushMe);
      }
      else
      {
        pushMe.shortDec = checkMe;
        pushMe.wrapperType = ISFLOAT;
        returnMe.push_back(pushMe);
      }
    }

    else if(lua_isstring(running, -1))
    {
      pushMe.word = lua_tostring(running, -1);
      pushMe.wrapperType = ISSTRING;
      returnMe.push_back(pushMe);
    }
    lua_pop(running, 1);
  }
  return returnMe;
}

void luaRunner::popTop()
{
  lua_pop(running, lua_gettop(running));
}
