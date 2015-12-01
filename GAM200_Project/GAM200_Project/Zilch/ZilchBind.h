//All content © 2014 DigiPen (USA) Corporation, all rights reserved.
//*****************************************************************************/
/*!
\file   ZilchBind.h
\author Joshua T. Fisher
\par    email: j.fisher\@digipen.edu
\par    DigiPen login: j.fisher
\par    Course: GAM 200
\date   10/25/2014
\brief
This file contains the functions needed to bind Zilch scripts to our engine.

*/
/******************************************************************************/
#pragma once

#ifndef YTE_Zilch_ZilchBind_h
#define YTE_Zilch_ZilchBind_h

#include "../Component.h"
#include <unordered_map>
#include "Zilch.hpp"

class ZilchBinder;

struct GetComponentUserData
{
  Zilch::BoundType* Type;
  ZilchBinder* ZilchBinder;
};

class ZilchBinder : public Zilch::EventHandler {
public:
  void ZilchParsedType(Zilch::ParseEvent *event);
  //void ZilchComponentFactories(std::unordered_map<Zilch::BoundType*, std::unique_ptr<YTE::Core::StringComponentFactory> > *currComponentFactories);
  void Compile(bool isZcc);
      
  ZilchBinder(bool isZcc);
  ~ZilchBinder();

  //Zilch::Debugger debugger;
  Zilch::Project mProject;
  Zilch::Module mDependencies;
  Zilch::LibraryRef mLibrary;
  Zilch::ExecutableState *mState;
  bool hasRegisteredYteTypes;

private:
  std::unordered_map<Zilch::BoundType*, GetComponentUserData> mZilchFactoryData;
};

// sender->RegisterListener(string eventName, Class& receiver, MemberFunction callback)
// sender.RegisterListener(eventName : String, callbackWithReceiver : Delegate)
void RegisterListener(Zilch::Call& call, Zilch::ExceptionReport& report);
#endif