/*!
 ********************************************************************************
 \file    Client.cpp
 \author  Nolan Taeksang Yoo
 \par     Contact: nolan\@projectexist.net
 \par     Classes: LevelDataManager
 \brief
 This is a client for the LevelDataManager and other things, which is a big mess.
 *******************************************************************************/

#define NO_SDK 1
#define ILLEGAL_DEMO 0

#include "lvlTools/levelGenerator.h"
#include "lvlTools/levelEditor.h"

#include "runLua/luaTranslate.h"
#include "runLua/luaRunner.h"
#include "logger/logger.h"

#include "gameComponents/baseObject.h"
#include "gameComponents/objFactory.h"
#include "gameComponents/Tile.h"

#include "Composition.h"

#include "Utilities.h"
#include "_EntryPoint.h"

#include <string>
#include <stdio.h>  /* defines FILENAME_MAX */

using std::string;

void luaRoutine(std::string arg)
{
  luaRunner testLua;
  #ifndef _WIN32
  arg.erase(arg.begin() + arg.find_last_of("/"), arg.end());
  testLua.sendStr(arg + "/");
  #endif
  
  printstr("(Lua Test 1)");
  testLua.runFile("Scripts/hello.lua");
  testLua.stop();
  std::cout<<'\n';

  printstr("(Lua Test 2)");
  testLua.loadFile("Scripts/hello.lua");
  std::string message1 = testLua.get<std::string>("test.candy");
  int message2 = testLua.get<int>("exam");
  printstr(message1);
  std::cout<<message2<<std::endl;
  std::cout<<'\n';

  printstr("(Lua Test 3)");
  testLua.runFile("Scripts/paramTest.lua", "%f %s %f %f", -1.0f, "rocket-powered candy cane", -2.0f, -0.25f);
  testLua.stop();
  std::cout<<'\n';

  printstr("(Lua Test 4)");
  luaTranslate testTranslate = *new luaTranslate();
  Tile testTile = *testTranslate.luaToTile("Scripts/TileArchetypes/Tile_Spikes.lua");
  std::cout<<"The char was "<<testTile.character<<std::endl;
  std::cout<<"The KillSides are: "<<std::endl;
  for(int i = 0; i < 4; i++)
  {
    if(testTile.killSides[i])
    {
      std::cout<<i<<std::endl;
    }
  }
  //std::cout<<'\n';
}

void logRoutine()
{
  printstr("(Log Test 1)");
  txtlog *thisLog = new txtlog("log.txt");
  thisLog->write("log test");
  printstr("Wrote \"log test\" to thisLog.");
  //thisLog->write("ERROR");
}

void factoryRoutine()
{
  printstr("(Factory Test 1)");
  objFactory *makeThings = new objFactory();
  GameObjectComposition* unicorn = makeThings->makeObject("SampleThing");
  std::cout<<"Unicorn's ID: "<<unicorn->GetId()<<std::endl;
  if (ILLEGAL_DEMO)
  {
	  std::cout << "Attempting destruction of illegal object #23.";
	makeThings->destroyObject(23);
  }
}

#ifdef LDM_RUN
int main(int argc, char **argv)
#else
int falseMain3(int argc, char **argv)
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
  logRoutine();
  visLine();
  factoryRoutine();
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