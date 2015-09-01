/******************************************************************************/
/*!
 \file   Utilities.cpp
 \author Nolan Yoo
 \par    email: n.yoo\@digipen.edu
 \par    Component: LevelDataManager
 \brief
 This is the interface (and some implementations) for Utilities.
 */
/******************************************************************************/

#ifndef UTILITIES_H
#define UTILITIES_H

#include <fstream>
#include <iostream>
#include <string>
#include <iterator>
#include <vector>

//meh, hopefully the client remembered to use the "setter" for closing the fstream
//(as long as the levelGenerator instance still exists, we cannot guarantee that its
//member fstream has been deconstructed. period.)
std::string getLineFromFile(int lineNumber, std::string fileName);
bool fileExists(const char *fileName);

template<typename T>
bool vectorHas(std::vector<T> vector, T value)
{
  return std::find(std::begin(vector), std::end(vector), value) != std::end(vector);
}

void visLine();
void waitForKB();

#endif
