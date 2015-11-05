/*!
 ********************************************************************************
 \file    extraLoggerInline.h
 \author  Nolan Taeksang Yoo
 \par     Contact: nolan\@projectexist.net
 \par     Classes: CConsoleLogger
 \brief
 Allows use of operator<< with a CConsoleLogger.
 \remarks
 All content © 2015 DigiPen (USA) Corporation, all rights reserved.
 *******************************************************************************/

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