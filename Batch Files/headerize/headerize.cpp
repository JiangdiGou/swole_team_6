//Headerize
#include <dirent.h>
#include <iostream>
#include <list>
#include <string>
#include <fstream>

int main(int argc,  char** argv)
{
  if(argc < 2)
  {
    std::cout << "Please specify input directory" << std::endl;
  }
  else
  {
    std::cout << "Headerizing files in " << argv[1] << std::endl;
  
    DIR* dir;
    dirent* pDir;
    char* author = NULL, *email = NULL;
    std::list<std::string> files = std::list<std::string>();
  
    dir = opendir(argv[1]); 
    author = argv[2];
    email = argv[3];

    while((pDir = readdir(dir)))
      files.push_back(pDir->d_name);
    
    files.pop_front();
    files.pop_front();
  
    std::cout << "Ok, I will headerize the following files... " << std::endl;
    for(std::list<std::string>::iterator it = files.begin(); it != files.end(); ++it)
      std::cout << *it << std::endl;
    
    for(std::list<std::string>::iterator it = files.begin(); it != files.end(); ++it)
    {
      std::ofstream currentFile;
      currentFile.open( ("input/" + (*it)).c_str() );
      std::cout << ("input/" + (*it)).c_str() << std::endl;
      
      currentFile << "/*****************************************************************************/" << std::endl;
      currentFile << "/*!" << std::endl;
      currentFile << "\\file       " << *it << std::endl;
      
      if(author)
        currentFile << "\\author  " << author << std::endl;
      else
        currentFile << "\\author  " << std::endl;
      
      if(email)
        currentFile << "\\par        Contact: " << email << std::endl;
      else
        currentFile << "\\par        Contact: " << std::endl;
      
      currentFile << "\\brief " << std::endl << std::endl;
      currentFile <<"\\remarks " << std::endl << std::endl;
      currentFile << "All content © 2015 DigiPen (USA) Corporation, all rights reserved." << std::endl;
      currentFile << "/*****************************************************************************/" << std::endl;

      currentFile.close();
    }
  }
}
