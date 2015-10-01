//author Nolan Yoo
#include "../Utilities.h"
//a single string argument
template<>
inline void luaRunner::runFile<std::string>(const std::string& fileName, std::string value, int args)
{
  lua_State *local = luaL_newstate();
  std::string trueName = "";

#ifndef _WIN32
  trueName += macAppend;
#endif
  trueName += fileName;
  int fileCall = luaL_loadfile(local, trueName.c_str());

  if(fileCall == 0)//file can actually be ran
  {
    luaL_openlibs(local);

    // start arg structure
    lua_createtable(local, args, 0);

    // set element i to value
    lua_pushnumber(local, 1);
    lua_pushstring(local, value.c_str());
    lua_settable(local, -3);

    // set the name of the array that the script will access
    lua_setglobal(local, "arg");

    fileCall = lua_pcall(local, 0, LUA_MULTRET, 0);
    printError(local, fileCall);
  }

  lua_close(local);
}

//special string case
template<>
inline std::string luaRunner::lua_null<std::string>()
{
  return "<null>";
}

template <>
inline bool luaRunner::lua_get<bool>(const std::string& request)
{
  if(!lua_isboolean(running, -1))
  {
    printError(request, "can't parse as boolean");
  }
  return (bool)lua_toboolean(running, -1);
}

template <>
inline int luaRunner::lua_get<int>(const std::string& request)
{
  if(!lua_isnumber(running, -1))
  {
    printError(request, "can't parse as int");
  }

  float returnMe = lua_tonumber(running, -1);

  if(!isReallyInt(returnMe))
  {
    printError(request, "can't parse as int (decimal portion exists)");
  }
  return (int)returnMe;
}

template <>
inline float luaRunner::lua_get<float>(const std::string& request)
{
  if(!lua_isnumber(running, -1))
  {
    printError(request, "can't parse as float");
  }
  return (float)lua_tonumber(running, -1);
}

template <>
inline std::string luaRunner::lua_get<std::string>(const std::string& request)
{
  if(lua_isstring(running, -1))
  {
    return std::string(lua_tostring(running, -1));
  }
  else
  {
    printError(request, "can't parse as string");
    return "<null>";
  }
}

template <>
inline char luaRunner::lua_get<char>(const std::string& request)
{
  if(lua_isstring(running, -1))
  {
    std::string checkMe = lua_tostring(running, -1);
    if(checkMe.length() > 1)
    {
      printError(request, "can't parse as char (this is more than 1 char)");
    }
    return checkMe[0];
  }
  else
  {
    printError(request, "can't parse as char");
    return '\0';
  }
}
