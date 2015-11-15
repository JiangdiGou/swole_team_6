#include "logger.hpp"

// Prepare a file for writing
txtlog::txtlog(std::string fileName)
{
	logStream.open(fileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
	this->fileName = fileName;
}

// Write to the prepared file
void txtlog::write(std::string message)
{
	logStream << message.c_str() << '\n';
	logStream.close();
	logStream.open(fileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
}

// Fetch the contents of a file
std::string txtlog::goFetch(std::string fileName)
{
  std::ifstream fromFile(fileName);
  std::stringstream buffer;
  buffer << fromFile.rdbuf();
  return buffer.str();
}

// Brutally hammer a string into the filesystem at the requested fileName
void txtlog::hammerFile(std::string message, std::string fileName)
{
  logStream.open(fileName.c_str(), std::fstream::out);
  logStream << message << '\n';
  logStream.close();

}