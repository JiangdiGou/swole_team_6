/******************************************************************************/
/*!
\file   BindInternal.hpp
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
Our Zilch Bound C++ Library, allows Zilch to call C++ functions, Intializes
Bound Types
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#pragma once


#include "Zilch.hpp"
#include <string>


//using namespace Zilch;

// Declare Internal Library Singleton

inline const Zilch::String StdStringToZeroString(const std::string& aString);
ZilchDeclareRedirectType(std::string, Zilch::String);

ZilchDeclareStaticLibrary(ZLib_Internal);

