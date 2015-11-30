#ifndef ZILCHMANAGER_H
#define ZILCHMANAGER_H

#include "../Engine.h"
#include "ZilchInterface.hpp"

class ZilchManager : public ISystem
{
public:
  ZilchManager(ZilchInterface* ZilchInter);
  ~ZilchManager();

  void Initialize()  override;
  void Update(float dt) override;
  void Draw() override;
  ZilchInterface* Interface;

private:
};

extern ZilchManager *ZILCHMANAGER;
#endif