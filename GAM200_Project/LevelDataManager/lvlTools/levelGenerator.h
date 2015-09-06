/******************************************************************************/
/*!
 \file   levelGenerator.h
 \author Nolan Yoo
 \par    email: n.yoo\@digipen.edu
 \par    Component: LevelDataManager
 \brief
 This is the interface for the levelGenerator class.
 */
/******************************************************************************/

#ifndef LEVELGENERATOR_H
#define LEVELGENERATOR_H

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using std::string;
using std::fstream;

//TODO: DECONSTRUCTOR (the default constructor works fine!)
class levelGenerator
{
private:
  string lastFileName;//DO NOT MAKE A SETTER
  fstream editingLevelFile;
  int desiredWidth;
  int desiredHeight;
  char**  holdingArray;

public:


  //Select a file for the owned pointer to open
  void selectLevelFile();

  //Creates a file using the fileName
  //UNCAUGHT EXCEPTION if file already exists
  void createEmptyFile(std::string fileName);

  //Writes "[LevelName]" and the given LevelName to the file.
  void writeLevelName(std::string levelName);

  //Writes "[ArraySpecs]" and the TileMap parameters to the file
  void writeLevelSize();

  //Writes "[TileMap]" and the actual TileMap itself
  void writeTileMap();

  //Writes "[EntityMap]" and the actual EntityMap itself
  void writeEntityMap();

  //attempt to open a file for editing
  //UNCAUGHT EXCEPTION if file can't be opened
  void openForEditing(std::string fileName);

  //Ask the keyboard for a fileName so we can create a file
  //CALLS createEmptyFile()
  //RETURNS the fileName the keyboard gave us
  std::string promptCreateEmptyFile();

  //Asks the keyboard for a levelName to write it to the file
  //CALLS writeLevelName()
  void promptWriteLevelName();

  //width and height of level
  void promptWriteLevelSize();

  //Is the open file empty?
  //EFFECTIVELY POWER-CYCLES THE STREAM
  bool openFileEmpty();

  void prepareLevelArray();

  /*getters and setters for single variables*/
  void closeFstream();//you'd better reopen it later...
  std::string getFileName();
};

#endif
