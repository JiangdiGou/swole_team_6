#include "ZilchManager.h"

ZilchManager *ZILCHMANAGER;

ZilchManager::ZilchManager(ZilchInterface* ZilchInter)
{
  ZILCHMANAGER = this;
  Interface = ZilchInter;
}
ZilchManager::~ZilchManager()
{
  delete Interface;
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