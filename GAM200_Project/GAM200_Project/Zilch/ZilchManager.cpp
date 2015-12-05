/******************************************************************************/
/*!
\file   ZilchManager.cpp
\author Gabriel Neumann
\par    email: g.neumann\@digipen.edu
\brief
ZilchManager To keep Track of Zilch Stuff
All content © 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/******************************************************************************/
#include "ZilchManager.h"

ZilchManager *ZILCHMANAGER;

ZilchManager::ZilchManager(Module* dependencies_, LibraryRef library_,
  Project* project_, ExecutableState* state_)
{
  dependencies = dependencies_;
  library = library_;
  project = project_;
  state = state_;
  ZILCHMANAGER = this;
}
ZilchManager::~ZilchManager()
{
}
void ZilchManager::Initialize()
{
}
void ZilchManager::Update(float dt)
{

}
void ZilchManager::Draw()
{

}