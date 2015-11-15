#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

class txtlog
{
public:
  //I added these pointless functions so it would compile
  //ignore the and do not use them. ~Conor Lavelle
  txtlog() {};
  txtlog(const txtlog& source) {};
  //end pointless functions

  txtlog(std::string fileName);
  void write(std::string message);

  std::string goFetch(std::string fileName);
  void hammerFile(std::string message, std::string fileName);
private:
  std::fstream logStream;
  std::string fileName;
};
