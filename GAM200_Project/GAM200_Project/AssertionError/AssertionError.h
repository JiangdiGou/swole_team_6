//author Nolan Yoo
#include "../logger/logger.h"

class AssertionError : public std::exception
{
public:
  AssertionError(std::string m="Unknown AssertionError!") : msg(m)
  {
	  txtlog *logError = new txtlog("log.txt");
	  logError->write(m);
  }
  //AssertionError() throw() {}
  const char* what() const throw() { return msg.c_str(); }

private:
  std::string msg;
};