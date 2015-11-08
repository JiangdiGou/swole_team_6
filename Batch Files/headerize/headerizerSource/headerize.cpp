//Headerize
#include <dirent.h>
#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>

#define LINELENGTH 75
std::string insertNewLines(std::string string, unsigned maxLength);

int main(int argc,  char** argv)
{
  if(argc < 4)
  {
    std::cout << "ERROR: Insufficient parameters!" << std::endl;
	  std::cout << "USAGE: headerize.exe [-d and/or -r] FIRSTNAME LASTNAME EMAIL" << std::endl;
	  std::cout << "-D: I want to be prompted to set the description/brief for each file" << std::endl;
	  std::cout << "-R: I want to be prompted to set the remarks for each file" << std::endl;
	  std::cout << "WARNING: This program does not do thorough input checking" << std::endl;
  	std::cout << "Will behave stupidly but not dangerously if wrong params." << std::endl;
    std::cin.get();
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
  
    std::cout << std::endl << "Headerizing files in Input directory" << std::endl;
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
        //Checks if this already has a header generated by this and deletes it so you can run multiple times
        if(line.size() >= 12 && std::string(line, 2, 11) ==  std::string("~EndHeader~"))
        {
          std::cout << "Noticed ~EndHeader~ in " << *it << ". Discarding old header." << std::endl;
          allText.clear();
        }
        else
        {
		      allText.append(line);
		      allText.append("\n");
        }
		  }
	  }
	  else
      std::cout << "Failed to open input file " << ("input/" + (*it)).c_str() << std::endl;
	  
	  //Puts the header in
    std::ofstream currentFile;
    currentFile.open( ("output/" + (*it)).c_str() );
    std::cout << "Creating " << ("output/" + (*it)).c_str() << std::endl;
		
    currentFile << "/*****************************************************************************/" << std::endl;
    currentFile << "/*!" << std::endl;
    currentFile << "\\file    " << *it << std::endl;
      
    if(authorFirstname && authorLastname)
      currentFile << "\\author  " << authorFirstname << " " << authorLastname << std::endl;
    else
      currentFile << "\\author  " << std::endl;
      
    if(email)
      currentFile << "\\par     Contact: " << email << std::endl;
    else
      currentFile << "\\par     Contact: " << std::endl;
      
    currentFile << "\\brief "<< std::endl;
	  
	  //If you want to manually set the description
	  if(setDescription)
	  {
	    std::string description;
	    std::cout << "Enter description/brief for file " << *it << std::endl;
		  std::getline(std::cin, description);
      description = insertNewLines(description, LINELENGTH);
		  currentFile << "  " << description << std::endl;
	  }
	  else
	    currentFile << std::endl;
    
    currentFile <<"\\remarks " << std::endl;
	  //If you want to manually set the remarks
	  if(setRemarks)
	  {
	    std::string remarks;
	    std::cout << "Enter remarks for file " << *it << std::endl;
		  std::getline(std::cin, remarks);
      remarks = insertNewLines(remarks, LINELENGTH);
		  currentFile << "  " << remarks << std::endl;
	  }
	  else
	    currentFile << std::endl;
	 
      currentFile << std::endl << "All content © 2015 DigiPen (USA) Corporation, all rights reserved." << std::endl;
      currentFile << "*/" << std::endl;
      currentFile << "/*****************************************************************************/" << std::endl;
      currentFile << "//~EndHeader~" << std::endl;

	  //Puts all the code in
	  currentFile << allText;
	  
    currentFile.close();
    }
  }
}

//This is like cs120 word wrap basically 
std::string insertNewLines(std::string string, unsigned maxLength)
{
  unsigned index = 0, previousIndex = 0;
  if(string.size() < maxLength)
    return string;
 
  std::string result = std::string(string);
  
  //Loops through string and adds in new lines and stuff as needed 
  for(index = 0; index < result.size(); ++index)
  {
    //If its time to new line 
    if(index > 0 && index == (maxLength + previousIndex))
    {
      //back up until youre not breaking a word 
      while(result[index] != ' ')
      {
        if(index == 0)
          break;
        else
          --index;
      }  
      
      //Adds the new line 
      result.insert(index, 1, '\n');
      previousIndex = index;
      ++index;
      
      //Add spaces to make it look indented 
      if(result.size() >= index + 1 && result[index + 1] == ' ')
      {
        result.insert(index, 2, ' ');
        index += 2;
      }
      else   
      {
        result.insert(index, 1, ' ');
        ++index;
      }
    }
  }

  return result;  
}
