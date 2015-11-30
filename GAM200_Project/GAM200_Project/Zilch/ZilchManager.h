#ifndef ZILCHMANAGER_H
#define ZILCHMANAGER_H

#include "../Engine.h"
#include "ZilchInterface.hpp"

class ZilchManager : public ISystem
{
public:
  ZilchManager(Module* dependencies, LibraryRef library, Project* project, ExecutableState* state);
  ~ZilchManager();

  void Initialize()  override;
  void Update(float dt) override;
  void Draw() override;
  Module* dependencies;
  LibraryRef library;
  Project* project;
  ExecutableState* state;

private:
};

extern ZilchManager *ZILCHMANAGER;
#endif