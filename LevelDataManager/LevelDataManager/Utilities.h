#ifndef UTILITIES_H
#define UTILITIES_H

#include <fstream>
#include <iostream>
#include <string>

//meh, hopefully the client remembered to use the "setter" for closing the fstream
//(as long as the levelGenerator instance still exists, we cannot guarantee that its
//member fstream has been deconstructed. period.)
std::string getLineFromFile(int lineNumber, std::string fileName);
bool fileExists(const char *fileName);
void waitForKB();

#endif
