#include "levelEditor.h"
#include "Utilities.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>

using std::string;
using std::vector;

levelEditor::levelEditor()
{
  levelEditor::validCommands.push_back("help");//prints available commands or help on specific command*/
  levelEditor::validCommands.push_back("print");//prints level
  levelEditor::validCommands.push_back("ent");//changes entity
  levelEditor::validCommands.push_back("tile");//changes tile

  levelEditor::validCommands.push_back("save");//saves file
  levelEditor::validCommands.push_back("quit");//quits loop
}

void levelEditor::loadLevelFrom(std::string fileName)
{
  string garbage;
  string levelName;//at line 2
  int arrayX;      //        4
  int arrayY;      //        5
  char**  tileMap;
  char**  entityMap;

  //get line count
  int lineCount;
  std::ifstream tempfile(fileName);
  std::string line;
  for (lineCount = 0; std::getline(tempfile, line); ++lineCount)
    ;//empty for, use for counting only
  tempfile.close();

  //get level name property
  levelName = getLineFromFile(2, fileName);
  //std::cout << levelName;

  //width of tileMap
  garbage = getLineFromFile(4, fileName);
  arrayX = std::stoi(garbage);

  //height of tileMap
  garbage = getLineFromFile(5, fileName);
  arrayY = std::stoi(garbage);

  //load arrays
  tileMap = new char*[arrayY];
  for (int i = 0; i < arrayY; i++)
  {
    tileMap[i] = new char[arrayX];
    garbage = getLineFromFile(5 + i + 2, fileName);
    strcpy(tileMap[i], garbage.c_str());
  }

  entityMap = new char*[arrayY];
  for (int i = 0; i < arrayY; i++)
  {
    entityMap[i] = new char[arrayX];
    garbage = getLineFromFile(5 + i + 1 + 2 + arrayY, fileName);
    strcpy(entityMap[i], garbage.c_str());
  }

  this->gameLevel.levelName = levelName;
  this->gameLevel.levelWidth = arrayX;
  this->gameLevel.levelHeight = arrayY;
  this->gameLevel.tileMap = tileMap;
  this->gameLevel.entityMap = entityMap;
  //this->gameLevel.printLevel();
}

void levelEditor::editingRoutine()
{
  while(true)
  {
    string input;
    vector<string> uiCmds;

    std::cout<<"Type a command. (Use \"help\" to see list of valid commands.)"<<std::endl;
    std::getline(std::cin, input);
    input.append(" ");

    //getting commands
    std::stringstream toSplit(input);
    std::string cmd;
    int cmdCount = 0;
    while (std::getline(toSplit, cmd, ' '))
    {
      uiCmds.push_back(cmd);
      cmdCount++;
    }
    /*command test*/
    /*for (std::vector<string>::const_iterator i = uiCmds.begin(); i != uiCmds.end(); ++i)
    {
      std::cout << *i << ' ';
    }*/

    string mainCmd = uiCmds[0];

    //mainCmd pathing
    if (mainCmd.compare("help") == 0)
    {
      if(cmdCount != 2 || !vectorHas(validCommands, uiCmds[1]))
      {
        std::cout<<"Invalid command to get help with."<<std::endl;
        continue;
      }
      cmdHelp(uiCmds[1]);
    }
  }
}

void levelEditor::cmdHelp(std::string command)
{

}

void levelEditor::saveLevelTo(std::string fileName)
{
}