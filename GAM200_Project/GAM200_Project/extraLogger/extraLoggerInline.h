#ifndef EXTRALOGGERINLINE_H
#define EXTRALOGGERINLINE_H

template <class T>
CConsoleLogger& operator<<(CConsoleLogger& localArg, const T &arg)
{
  std::stringbuf garbage;
  std::ostream fakeStream(&garbage);
  fakeStream << arg;
	std::string printable = garbage.str();
  localArg.printf(printable.c_str());
  return localArg;
}

#endif