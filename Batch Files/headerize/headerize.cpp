//Headerize
#include <dirent.h>
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>

int main(int argc,  char** argv)
{
  if(argc < 4)
  {
    std::cout << "ERROR: Insufficient parameters!" << std::endl;
	std::cout << "USAGE: headerize.exe [-d and/or -r] FIRSTNAME LASTNAME EMAIL" << std::endl;
	std::cout << "-D: I want to be prompted to set the description for each file" << std::endl;
	std::cout << "-R: I want to be prompted to set the remarks for each file" << std::endl;
	std::cout << "WARNING: I've done very little stupid input checking" << std::endl;
	std::cout << "Behavior undefined (and pos dangerous) for any form except given above" << std::endl;
  }
  else
  {
    dirent* pDir;
    DIR* dir = opendir("input");
    char* authorFirstname = NULL, *authorLastname = NULL, *email = NULL;
    std::list<std::string> files = std::list<std::string>();
	int i;
	bool setDescription = false, setRemarks = false;
	
	//Checks for switches 
	for(i = 1; i < argc - 3; ++i)
    {
     if(strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "-D") == 0)
	   setDescription = true;
	 else if(strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "-R") == 0)
	   setRemarks = true;
    }   
   
    //Saves in necessary command line params
    authorFirstname = argv[i];
	authorLastname = argv[i+1];
    email = argv[i+2];

	//Reads through input dir and 
    while((pDir = readdir(dir)))
      files.push_back(pDir->d_name);
    
	//The first two thigns i grab are junk idc about. So pop em off here
    files.pop_front();
    files.pop_front();
  
  
    std::cout << "Headerizing files in Input " << std::endl;
    for(std::list<std::string>::iterator it = files.begin(); it != files.end(); ++it)
    {
	  //Reads the entire contents of a file. It wont let me insert at beginning so, I'll make a new 
	  //file with header at beginning and rest at end. This reads all actual code in the file
	  std::ifstream headerlessFile (("input/" + (*it)).c_str());
	  std::string line, allText;
	  if(headerlessFile.is_open())
	  {
	    while(getline(headerlessFile, line))
		{
		   allText.append(line);
		   allText.append("\n");
		}
	  }
	  else
	  {
        std::cout << "Failed to open input file " << ("input/" + (*it)).c_str() << std::endl;
	  }
	  
	  //Puts the header in
      std::ofstream currentFile;
      currentFile.open( ("output/" + (*it)).c_str() );
      std::cout << ("output/" + (*it)).c_str() << std::endl;
		
      currentFile << "/*****************************************************************************/" << std::endl;
      currentFile << "/*!" << std::endl;
      currentFile << "\\file       " << *it << std::endl;
      
      if(authorFirstname && authorLastname)
        currentFile << "\\author  " << authorFirstname << " " << authorLastname << std::endl;
      else
        currentFile << "\\author  " << std::endl;
      
      if(email)
        currentFile << "\\par        Contact: " << email << std::endl;
      else
        currentFile << "\\par        Contact: " << std::endl;
      
      currentFile << "\\brief "<< std::endl;
	  
	  //If you want to manually set the description
	  if(setDescription)
	  {
	    char* description;
	    std::cout << "Enter description for file " << *it << std::endl;
		std::cin.getline(description, 512);
		currentFile << "     " << description << std::endl;
	  }
	  else
	    std::cout << std::endl;
	  
      currentFile <<"\\remarks " << std::endl;
	  
	  //If you want to manually set the remarks
	  if(setRemarks)
	  {
	    char* remarks;
	    std::cout << "Enter remarks for file " << *it << std::endl;
		std::cin >> remarks;
		std::cin.getline(remarks, 512);
		currentFile << "     " << remarks << std::endl;
	  }
	  else
	    std::cout << std::endl;
	 
      currentFile << "All content © 2015 DigiPen (USA) Corporation, all rights reserved." << std::endl;
      currentFile << "/*****************************************************************************/" << std::endl;

	  //Puts all the code in
	  currentFile << allText;
	  
      currentFile.close();
    }
  }
}
