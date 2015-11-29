#include "ZilchComponent.h"

OurZilchComponent::OurZilchComponent(std::string scriptName)
{
  ZilchInterface* Inter = ZILCHMANAGER->Interface;
  classScript = scriptName;
  zilchClass = Inter->GetBoundType(classScript);
  initFunc = Inter->GetFunction(zilchClass, "Initialize", ZilchTypeId(void));
  updateFunc = Inter->GetFunction(zilchClass, "OnUpdate", ZilchTypeId(void));
  OnCollideStart = Inter->GetFunction(zilchClass, "OnCollideStart", ZilchTypeId(void));
  OnCollidePersist = Inter->GetFunction(zilchClass, "OnCollidePersist", ZilchTypeId(void));
  OnCollideEnd = Inter->GetFunction(zilchClass, "OnCollideEnd", ZilchTypeId(void));
  OnCustomEvent = Inter->GetFunction(zilchClass, "OnCustomEvent", ZilchTypeId(void));
  OnMouseLeftDown = Inter->GetFunction(zilchClass, "OnMouseLeftDown", ZilchTypeId(void));
  OnMouseRightDown = Inter->GetFunction(zilchClass, "OnMouseRightDown", ZilchTypeId(void));
  OnMouseLeftUp = Inter->GetFunction(zilchClass, "OnMouseLeftUp", ZilchTypeId(void));
  OnMouseRightUp = Inter->GetFunction(zilchClass, "OnMouseRightUp", ZilchTypeId(void));
  Destroy = Inter->GetFunction(zilchClass, "Destroy", ZilchTypeId(void));
}
OurZilchComponent::~OurZilchComponent()
{

}
void OurZilchComponent::Initialize()
{
  ZilchInterface* Inter = ZILCHMANAGER->Interface;
  Handle* classInstance = new Handle();
  *classInstance = Inter->AllocateType(zilchClass);
  if (initFunc != NULL)
  {
    Call call(initFunc, Inter->state_);
    call.Set<Handle>(Call::This, *classInstance);
    call.Invoke(Inter->report_);
  }
}
void OurZilchComponent::Update(float dt)
{

}
void OurZilchComponent::SendMessages(Message* message)
{

}
void OurZilchComponent::SerializeRead(Serializer& str)
{
  StreamRead(str, classScript);
}
void OurZilchComponent::SerializeWrite(Serializer& str)
{
  StreamWrite(str, classScript);
  StreamWrite(str);
}