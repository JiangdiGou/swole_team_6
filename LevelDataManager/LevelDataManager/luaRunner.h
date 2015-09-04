#include <string>
#include <iostream>

#ifdef _WIN32
  #pragma comment(lib, "luaWin/lua53.lib")
#endif

#include "luaLib/lua.hpp"

class luaRunner
{
public:
  void printError(lua_State *L, int status);
  void printError(const std::string& source, const std::string& reason);

  void runFile(const std::string& fileName);
  template<typename T>
  void runFile(const std::string& fileName, T value, int args = 1)
  {
    return;
  }
  void loadFile(const std::string& fileName);

  bool lua_checkstack(const std::string& request);

  //wrapper for lua_get (on a good day)
  template<typename T>
  T get(const std::string& request)
  {
    if(!running)
    {
      return lua_null<T>();
    }

    T result;

    if(lua_checkstack(request))
    {
      result = lua_get<T>(request);
    }
    else
    {
      result = lua_null<T>();
    }

    lua_pop(running, depth + 1);//pop the whole current stack
    return result;
  }

  template<typename T>
  T lua_null()
  {
    return 0;//OK null for most cases
  }

  template<typename T>
  T lua_get(const std::string& request)
  {
    return 0;//for unusable objects
  }

  void popTop();

private:
  lua_State* running;
  std::string fileName;
  int depth;
};

#include "luaRunnerInline.h"