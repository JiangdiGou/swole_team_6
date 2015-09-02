/******************************************************************************/
/*!
 \file   levelEditor.cpp
 \author Nolan Yoo
 \par    email: n.yoo\@digipen.edu
 \par    Component: LevelDataManager
 \brief
 This is the implementation of the LevelEditor, which is a big mess.
 */
/******************************************************************************/

#include "levelEditor.h"
#include "Utilities.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <stdio.h>

using std::string;
using std::vector;

levelEditor::levelEditor()
{
  levelEditor::validCommands.push_back("help");//prints available commands or help on specific command*/
  levelEditor::validCommands.push_back("print");//prints level
  levelEditor::validCommands.push_back("tile");//changes entity
  levelEditor::validCommands.push_back("ent");//changes tile

  levelEditor::validCommands.push_back("save");//saves file
  levelEditor::validCommands.push_back("quit");//quits loop

  levelEditor::numCommands = levelEditor::validCommands.size();
}

void levelEditor::loadLevelFrom(std::string fileName)
{
  this->fileName = fileName;
  this->gameLevel.loadLevelFrom(fileName);
}

void levelEditor::editingRoutine()
{
  while(true)
  {
    visLine();
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
    visLine();
    string mainCmd = uiCmds[0];

    //mainCmd pathing
    if (mainCmd.compare("help") == 0)
    {
      if(cmdCount == 1)
      {
        this->cmdHelp();
        continue;
      }
      else if(cmdCount != 2 || !vectorHas(validCommands, uiCmds[1]))
      {
        std::cout<<"Invalid command to get help with."<<std::endl;
        continue;
      }
      this->cmdHelp(uiCmds[1]);
    }
    else if(mainCmd.compare("print") == 0)
    {
      this->gameLevel.printLevel();
      continue;
    }
    else if(mainCmd.compare("tile") == 0)
    {
      //"ent" char int int
      if(cmdCount != 4)
      {
        printstr("\"tile\" command requires 4 arguments.");
        continue;
      }

      char newTile;
      int x;
      int y;

      try
      {
        newTile = uiCmds[1].c_str()[0];
        x = std::stoi(uiCmds[2]) - 1;
        y = std::stoi(uiCmds[3]) - 1;
      }
      catch (const std::invalid_argument)
      {
        std::cout<<uiCmds[2]<<" or "<<uiCmds[3]<<" wasn't a valid x/y value."<<std::endl;
        continue;
      }

      this->cmdSingle(newTile, x, y, true);
      continue;
    }
    else if(mainCmd.compare("ent") == 0)
    {
      //"ent" char int int
      if(cmdCount != 4)
      {
        printstr("\"ent\" command requires 4 arguments.");
        continue;
      }

      char newTile;
      int x;
      int y;

      try
      {
        newTile = uiCmds[1].c_str()[0];
        x = std::stoi(uiCmds[2]) - 1;
        y = std::stoi(uiCmds[3]) - 1;
      }
      catch (const std::invalid_argument)
      {
        std::cout<<uiCmds[2]<<" or "<<uiCmds[3]<<" wasn't a valid x/y value."<<std::endl;
        continue;
      }

      this->cmdSingle(newTile, x, y, false);
      continue;
    }

    else if(mainCmd.compare("save") == 0)
    {
      this->saveLevel();
    }
  }
}

void levelEditor::cmdHelp()
{
  std::cout<<"Valid commands:"<<std::endl;
  for(int i = 0; i < numCommands; i++)
  {
    std::cout<<this->validCommands[i]<<std::endl;
  }
}

void levelEditor::cmdHelp(std::string command)
{
  if (command.compare("help") == 0)
  {
    std::cout<<"Shows list of commands or gets help with a specific command."<<std::endl;
  }
  else if (command.compare("print") == 0)
  {
    std::cout<<"Prints out the level."<<std::endl;
  }
  else
  {
    std::cout<<"COMMAND IS NOT DOCUMENTED."<<std::endl;
  }
}

//mode is true for a tile, false for an entity!
bool levelEditor::cmdSingle(char tile, int x, int y, bool mode)
{
  bool success;
  if(mode)
  {
    success = this->gameLevel.changeTile(tile, x, y);
  }
  else
  {
    success = this->gameLevel.changeEntity(tile, x, y);
  }

  if(success)
  {
    this->gameLevel.printLevel();
  }
  else
  {
    printstr("Change to level could not be made.");
  }

  return success;
}

void levelEditor::saveLevel()
{
  remove(fileName.c_str());
  std::fstream levelFile;
  levelFile.open(fileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);

  string dataHeader = "[LevelName]\n";
  levelFile << dataHeader;
  levelFile << this->gameLevel.levelName << '\n';

  dataHeader = "[ArraySpecs]\n";
  levelFile << dataHeader;
  levelFile << this->gameLevel.levelWidth << '\n';
  levelFile << this->gameLevel.levelHeight << '\n';

  dataHeader = "[TileMap]\n";
  levelFile << dataHeader;
  for (int i = 0; i < this->gameLevel.levelHeight; i++)
  {
    for (int j = 0; j < this->gameLevel.levelWidth; j++)
    {
      levelFile << this->gameLevel.tileMap[i][j];
    }
    levelFile << '\n';
  }

  dataHeader = "[EntityMap]\n";
  levelFile << dataHeader;
  for (int i = 0; i < this->gameLevel.levelHeight; i++)
  {
    for (int j = 0; j < this->gameLevel.levelWidth; j++)
    {
      levelFile << this->gameLevel.entityMap[i][j];
    }
    levelFile << '\n';
  }
}