/*!
 ********************************************************************************
 \file    Client.cpp
 \author  Nolan Taeksang Yoo
 \par     Contact: nolan\@projectexist.net
 \par     Classes: LevelDataManager, <Others>
 \brief
 This is a client for the LevelDataManager and other things, which is a big mess.
 \remarks
 Only runs with LDM_RUN.
 All content © 2015 DigiPen (USA) Corporation, all rights reserved.
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
  /*
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
  */
  //std::cout<<'\n';
}

void logRoutine()
{
  /*
  printstr("(Log Test 1)");
  txtlog *thisLog = new txtlog("log.txt");
  thisLog->write("log test");
  printstr("Wrote \"log test\" to thisLog.");
  //thisLog->write("ERROR");
  */
}

void factoryRoutine()
{
  /*
  printstr("(Factory Test 1)");
  objFactory *makeThings = new objFactory();
  GameObjectComposition* unicorn = makeThings->makeObject("SampleThing");
  std::cout<<"Unicorn's ID: "<<unicorn->GetId()<<std::endl;
  if (ILLEGAL_DEMO)
  {
	  std::cout << "Attempting destruction of illegal object #23.";
	makeThings->destroyObject(23);
  }
  */
}