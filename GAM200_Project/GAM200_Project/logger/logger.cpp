//
//  logger.cpp
//  GAM200_Project
//
//  Created by Nolan Yoo on 9/18/15.
//  Copyright (c) 2015 Nolan Yoo. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS

#include "logger.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>

txtlog::txtlog(std::string fileName)
{
#ifdef EDTIOR
	logStream.open(fileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
	this->fileName = fileName;
#endif
}

void txtlog::write(std::string message)
{
#ifdef EDTIOR
	logStream << '[' << this->dateTime() << "] " << message.c_str() << '\n';
	logStream.close();
	logStream.open(fileName.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
#endif
}

const std::string txtlog::dateTime()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d | %X", &tstruct);

	return std::string(buf);
}