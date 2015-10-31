#ifndef EXTRALOGGERINLINE_H
#define EXTRALOGGERINLINE_H

template <class T>
CConsoleLogger& operator<<(CConsoleLogger& localArg, const T &arg)
{
  std::ostringstream stream;
  stream << arg;
  std::string str = stream.str();
  localArg.printf(str.c_str());
  return localArg;
}

#endif