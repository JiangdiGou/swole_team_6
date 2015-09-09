/******************************************************************************/
/*!
 \file   Client.cpp
 \author Nolan Yoo
 \par    email: n.yoo\@digipen.edu
 \par    Component: LevelDataManager
 \brief
 This is a client for the LevelDataManager, which is a big mess.
 */
/******************************************************************************/

#define NO_SDK 1

#include "lvlTools/levelGenerator.h"
#include "lvlTools/levelEditor.h"
#include "Utilities.h"
#include "runLua/luaRunner.h"

#include <string>
#include <stdio.h>  /* defines FILENAME_MAX */

using std::string;

void luaRoutine(std::string arg)
{
  luaRunner testLua;

  printstr("(Lua Test 1)");
  testLua.runFile("Scripts/hello.lua");
  arg.erase(arg.begin() + arg.find_last_of("/"), arg.end());
  testLua.sendStr(arg + "/");
  std::cout<<'\n';

  printstr("(Lua Test 2)");
  testLua.loadFile("Scripts/hello.lua");
  std::string message1 = testLua.get<std::string>("test.candy");
  int message2 = testLua.get<int>("exam");
  printstr(message1);
  std::cout<<message2<<std::endl;
  std::cout<<'\n';

  printstr("(Lua Test 3)");
  testLua.runFile<std::string>("Scripts/paramTest.lua", "Lua argument test");
  //std::cout<<'\n';
}

#ifdef _WIN32
int potato(void)
#else
int main(int arc, char **argv)
#endif
{
  /* RUNNING RUNNING DIRECTORY ROUTINE */
  char cCurrentPath[FILENAME_MAX];
  if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
  {
    return errno;
  }
  cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* for safety */
  std::cout<<"The current working directory is: "<<cCurrentPath<<'\n';
  visLine();
  /* END RUNNING DIRECTORY ROUTINE */

  /* RUNNING LUA ROUTINE*/
  if(luaTest())
  {
    luaRoutine(argv[0]);
  }
  else
  {
    printstr("Lua test broke.");
  }
  visLine();
  /* END RUNNING LUA ROUTINE*/

  levelGenerator test;
  string fileName;
  string getSpecLineTest;
  bool fileCheck;

  //Create an empty file and save its name
  fileName = test.promptCreateEmptyFile();

  //Wait for Keyboard press
  waitForKB();

  //Open the file for editing
  test.openForEditing(fileName);

  //Is the file empty?
  fileCheck = test.openFileEmpty();
  if (fileCheck)
  {
    std::cout << "File is empty. Ready to write." << std::endl;
    test.promptWriteLevelName();
    //promptWriteLevelSize also writes initial maps
    test.promptWriteLevelSize();

    test.closeFstream();
    /*TEST CODE WORKED
    getSpecLineTest = getLineFromFile(4, fileName);
    std::cout << "Line test result: " << getSpecLineTest << std::endl;*/
  }

  waitForKB();

  levelEditor test2;
  test2.loadLevelFrom(fileName);
  test2.editingRoutine();

  //Wait for Keyboard press
  waitForKB();

  //
  std::cout << "Killing client..." << std::endl;
  return 0;
}