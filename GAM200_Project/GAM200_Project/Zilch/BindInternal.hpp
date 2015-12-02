#pragma once


#include "Zilch.hpp"
#include <string>


//using namespace Zilch;

// Declare Internal Library Singleton


ZilchDeclareRedirectType(std::string, Zilch::String);

ZilchDeclareStaticLibrary(ZLib_Internal);

