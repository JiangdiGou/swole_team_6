/*!
 ********************************************************************************
 \file    AssertionError.h
 \author  Nolan Taeksang Yoo
 \par     Contact: nolan\@projectexist.net
 \par     Classes: AssertionError, AssertionWarning
 \brief
 Fulfills the Assert requirement. Logs to text file when something goes wrong.
 \remarks
 Nothing should ever catch an AssertionError.
 *******************************************************************************/

#ifndef ASSERTIONERROR_H
#define ASSERTIONERROR_H

#include "../logger/logger.h"

inline void AssertionWarning(std::string m = "Unknown AssertionWarning!")
{
  txtlog *logError = new txtlog("log.txt");
  logError->write("[AssertionWarning] (SEE BELOW LINE!)");
  logError->write(m);
}

class AssertionError : public std::exception
{
public:
  AssertionError(std::string m="Unknown AssertionError!") : msg(m)
  {
	  txtlog *logError = new txtlog("log.txt");
    logError->write("[AssertionError] (SEE BELOW LINE!)");
	  logError->write(m);
  }
  //AssertionError() throw() {}
  const char* what() const throw() { return msg.c_str(); }

private:
  std::string msg;
};

#endif