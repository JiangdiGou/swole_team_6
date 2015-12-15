//
//  logger.h
//  GAM200_Project
//
//  Created by Nolan Yoo on 9/18/15.
//  All content 2015 © DigiPen (USA) Corporation, all rights reserved.
//


#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

class txtlog
{
public:
  //I added these pointless functions so it would compile
  //ignore the and do not use them. 
  txtlog() {};
  txtlog(const txtlog& source) {};

	txtlog(std::string fileName);
	void write(std::string message);
private:
	std::fstream logStream;
	std::string fileName;
	const std::string dateTime();
};

#endif