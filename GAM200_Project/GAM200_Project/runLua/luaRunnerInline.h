//author Nolan Yoo
#include "../Utilities.h"
#include <cstdarg>


//variadically take some arguments
inline void luaRunner::runFile(const std::string& fileName, const char* format,...)
{
  va_list args;
  va_start(args, format);

  lua_State *local = luaL_newstate();
  std::string trueName = "";


  float num;
  std::vector<char> argTypes = {};

#ifndef _WIN32
  trueName += macAppend;
#endif
  trueName += fileName;
  int fileCall = luaL_loadfile(local, trueName.c_str());

  if(fileCall == 0)//file can actually be ran
  {
    luaL_openlibs(local);

    //Saves a bunch of F's and S'es into a vector 
    const char * head = format;
    while (*head)
    {
      if ((*head) == '%')
      {
        ++head;
        argTypes.push_back(*head);
      }
      ++head;

    }

    int count = argTypes.size();
    //std::cout << count << std::endl;

    // start arg table structure
    lua_createtable(local, count, 0);

    for (std::vector<char>::iterator it = argTypes.begin(); it != argTypes.end(); ++it)
    {
      //std::cout << "Trying to push " << (*it) << std::endl;
      //Pushes Index
      lua_pushnumber(local, it - argTypes.begin() + 1);

      //Pushes float if f or string if s
      if ((*it) == 'f' || (*it) == 'F')
      {
        num = va_arg(args, double);
        //std::cout << "Pushing float " << num << std::endl;
        lua_pushnumber(local, num);
      }
      else if ((*it) == 's' || (*it) == 'S')
      {
        char * sStr = (va_arg(args, char *));
        //std::cout << "Pushing string " << sStr << std::endl;
        lua_pushstring(local, sStr);
      }
      lua_settable(local, -3);
    }
    va_end(args);
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
