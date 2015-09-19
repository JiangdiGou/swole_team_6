//
//  logger.cpp
//  GAM200_Project
//
//  Created by Nolan Yoo on 9/18/15.
//  Copyright (c) 2015 Nolan Yoo. All rights reserved.
//

#include "logger.h"

txtlog::txtlog(std::string fileName)
{
  logStream.open(fileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
  this->fileName = fileName;
}

void txtlog::write(std::string message)
{
  logStream << message.c_str() << '\n';
  logStream.close();
  logStream.open(fileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
}