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

#include "levelGenerator.h"
#include "levelEditor.h"
#include "Utilities.h"

#include <stdio.h>  /* defines FILENAME_MAX */
#ifdef _WIN32
  #include <direct.h>
  #define GetCurrentDir _getcwd
#else
  #include <unistd.h>
  #define GetCurrentDir getcwd
#endif

using std::string;

int main(void)
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
    printstr("Lua test run.");
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