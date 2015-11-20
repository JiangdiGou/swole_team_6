/******************************************************************************/
/*!
 \file   Utilities.cpp
 \author Nolan Yoo
 \par    email: n.yoo\@digipen.edu
 \par    Component: LevelDataManager
 \brief
 This is the implementation for Utilities, which does some random crap.
 */
/******************************************************************************/

#include "Utilities.h"
//#include "Cursed/action_math_utility.h"
//random crap indeed...
Vector3D::Vector3D(glm::vec3 &attemptCopy):
  x(float(attemptCopy.x)),
  y(float(attemptCopy.y)),
  z(float(attemptCopy.z))
{
  /*
  this->x = float(attemptCopy.x);
  this->y = float(attemptCopy.y);
  this->z = float(attemptCopy.z);
  */
}

std::ostream& operator<<(std::ostream &out, const Vector3D &v)
{
  out << '(' << v.x << ", " << v.y << ", " << v.z << ')';
  return out;
}

std::string whereExec()
{
  char cCurrentPath[FILENAME_MAX];
  if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
  {
    throw std::runtime_error("cannot locate myself");
  }
  cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';
  return std::string(cCurrentPath);
}

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

bool isReallyInt(float checkMe)
{
  while(checkMe > 0)
  {
    checkMe -= 1.0f;
  }
  if(checkMe == 0.0f)
  {
    return true;
  }
  return false;
}

void visLine()
{
  std::cout<<"=========="<<std::endl;
}

void printstr(std::string toPrint)
{
  std::cout<< toPrint <<std::endl;
}

void waitForKB()
{
  std::cout << "Press Enter or Return to continue..." << std::endl;
  fseek(stdin, 0, SEEK_END);
  while (getchar() != '\n');
}

bool luaTest()
{
  try
  {
    lua_State *L = luaL_newstate();
    lua_close(L);
  }
  catch(...)
  {
    //SOMETHING was caught.
    return false;
  }
  return true;
}
