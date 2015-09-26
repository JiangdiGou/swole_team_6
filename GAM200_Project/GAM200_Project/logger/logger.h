//
//  logger.h
//  GAM200_Project
//
//  Created by Nolan Yoo on 9/18/15.
//  Copyright (c) 2015 Nolan Yoo. All rights reserved.
//

#include <fstream>
#include <string>

class txtlog
{
public:
	txtlog(std::string fileName);
	void write(std::string message);
private:
	std::fstream logStream;
	std::string fileName;
	const std::string dateTime();
};