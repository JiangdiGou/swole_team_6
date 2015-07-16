#include "Utilities.h"

std::string getLineFromFile(int lineNumber, std::string fileName)
{
  std::string garbage;
  std::fstream fileStream(fileName.c_str());

  fileStream.seekg(0);//don't trust the client. especially since I wrote the damn thing

  for (int i = 0; i < lineNumber; i++)
  {
    //go nuts, maybe it'll work
    std::getline(fileStream, garbage);
  }

  return garbage;
}

bool fileExists(const char* fileName)
{
  std::ifstream infile(fileName);
  return infile.good();
}

void waitForKB()
{
  std::cout << "Press Enter or Return to continue..." << std::endl;
  fseek(stdin, 0, SEEK_END);
  while (getchar() != '\n');
}
