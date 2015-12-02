#pragma once


#include "Zilch.hpp"
#include <string>


//using namespace Zilch;

// Declare Internal Library Singleton

inline const Zilch::String StdStringToZeroString(const std::string& aString);
ZilchDeclareRedirectType(std::string, Zilch::String);

ZilchDeclareStaticLibrary(ZLib_Internal);

