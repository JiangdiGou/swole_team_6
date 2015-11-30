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