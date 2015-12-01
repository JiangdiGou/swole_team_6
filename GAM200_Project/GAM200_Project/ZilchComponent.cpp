#include "ZilchComponent.h"

OurZilchComponent::OurZilchComponent(std::string scriptName)
{
  LibraryRef library = ZILCHMANAGER->library;
  classScript = scriptName;
  if (library->BoundTypes.findValue("EXAMPLE", nullptr) == NULL)
  {
    return;
  }
  else
  {
    zilchClass = library->BoundTypes.findValue("EXAMPLE", nullptr);
    initFunc = zilchClass->FindFunction("Initialize", Array<Type*>(ZeroInit, ZilchTypeId(GameObjectComposition)), ZilchTypeId(void), FindMemberOptions::None);
    updateFunc = zilchClass->FindFunction("OnUpdate", Array<Type*>(ZeroInit, ZilchTypeId(Real)), ZilchTypeId(void), FindMemberOptions::None);

    OnCollideStart = zilchClass->FindFunction("OnCollideStart", Array<Type*>(ZeroInit, ZilchTypeId(GameObjectComposition)), ZilchTypeId(void), FindMemberOptions::None);
    OnCollidePersist = zilchClass->FindFunction("OnCollidePersist", Array<Type*>(ZeroInit, ZilchTypeId(GameObjectComposition)), ZilchTypeId(void), FindMemberOptions::None);
    OnCollideEnd = zilchClass->FindFunction("OnCollideEnd", Array<Type*>(ZeroInit, ZilchTypeId(GameObjectComposition)), ZilchTypeId(void), FindMemberOptions::None);

    OnCustomEvent = zilchClass->FindFunction("OnCustomEvent", Array<Type*>(), ZilchTypeId(void), FindMemberOptions::None);

    OnKeyboardDown = zilchClass->FindFunction("OnKeyboardDown", Array<Type*>(ZeroInit, ZilchTypeId(Integer)), ZilchTypeId(void), FindMemberOptions::None);

    OnMouseLeftDown = zilchClass->FindFunction("OnMouseLeftDown", Array<Type*>(ZeroInit, ZilchTypeId(Vec2D)), ZilchTypeId(void), FindMemberOptions::None);
    OnMouseRightDown = zilchClass->FindFunction("OnMouseRightDown", Array<Type*>(ZeroInit, ZilchTypeId(Vec2D)), ZilchTypeId(void), FindMemberOptions::None);
    OnMouseLeftUp = zilchClass->FindFunction("OnMouseLeftUp", Array<Type*>(ZeroInit, ZilchTypeId(Vec2D)), ZilchTypeId(void), FindMemberOptions::None);
    OnMouseRightUp = zilchClass->FindFunction("OnMouseRightUp", Array<Type*>(ZeroInit, ZilchTypeId(Vec2D)), ZilchTypeId(void), FindMemberOptions::None);

    OnMouseMove = zilchClass->FindFunction("OnMouseMove", Array<Type*>(ZeroInit, ZilchTypeId(Vec2D)), ZilchTypeId(void), FindMemberOptions::None);

    Destroy = zilchClass->FindFunction("Destroy", Array<Type*>(), ZilchTypeId(void), FindMemberOptions::None);
  }
}
OurZilchComponent::~OurZilchComponent()
{
  
  if (Destroy != NULL)
  {
    Call call(Destroy, ZILCHMANAGER->state);
    call.Set<Handle>(Call::This, classInstance);
    call.Invoke(report);
  }
  //delete classInstance;
}
void OurZilchComponent::Initialize()
{
  classInstance = ZILCHMANAGER->state->AllocateDefaultConstructedHeapObject(zilchClass, report, HeapFlags::ReferenceCounted);
  if (initFunc != NULL)
  {
    Call call(initFunc, ZILCHMANAGER->state);
    call.Set<Handle>(Call::This, classInstance);
    call.Set<>(0, GetOwner());
    call.Invoke(report);
  }
}
void OurZilchComponent::Update(float dt)
{
  if (updateFunc != NULL)
  {
    Call call(updateFunc, ZILCHMANAGER->state);
    call.Set<Handle>(Call::This, classInstance);
    call.Set<Real>(0, dt);
    call.Invoke(report);
  }
}
void OurZilchComponent::SendMessages(Message* message)
{
  switch (message->MessageId)
  {
  case Mid::CharacterKey:
    if (OnKeyboardDown != NULL)
    {
      int key = ((MessageCharacterKey*)message)->character;
      Call call(OnKeyboardDown, ZILCHMANAGER->state);
      call.Set<Handle>(Call::This, classInstance);
      call.Set<Integer>(0, key);
      call.Invoke(report);
    }
    break;
  case Mid::MouseButton:
    if (((MouseButton*)message)->ButtonIsPressed)
    {
      if (((MouseButton*)message)->MouseButtonIndex == MouseButton::MouseButtonIndexId::LeftMouse)
      {
        if (OnMouseLeftDown != NULL)
        {
          Call call(OnMouseLeftDown, ZILCHMANAGER->state);
          call.Set<Handle>(Call::This, classInstance);
          call.Set<>(0, ((MouseButton*)message)->MousePosition);
          call.Invoke(report);
        }
      }
      else
      {
        if (OnMouseRightDown != NULL)
        {
          Call call(OnMouseRightDown, ZILCHMANAGER->state);
          call.Set<Handle>(Call::This, classInstance);
          call.Set<>(0, ((MouseButton*)message)->MousePosition);
          call.Invoke(report);
        }
      }
    }
    else
    {
      if (((MouseButton*)message)->MouseButtonIndex == MouseButton::MouseButtonIndexId::LeftMouse)
      {
        if (OnMouseLeftUp != NULL)
        {
          Call call(OnMouseLeftUp, ZILCHMANAGER->state);
          call.Set<Handle>(Call::This, classInstance);
          call.Set<>(0, ((MouseButton*)message)->MousePosition);
          call.Invoke(report);
        }
      }
      else
      {
        if (OnMouseRightUp != NULL)
        {
          Call call(OnMouseRightUp, ZILCHMANAGER->state);
          call.Set<Handle>(Call::This, classInstance);
          call.Set<>(0, ((MouseButton*)message)->MousePosition);
          call.Invoke(report);
        }
      }
    }
    break;
  case Mid::MouseMove:
    if (OnMouseMove != NULL)
    {
      Call call(OnMouseMove, ZILCHMANAGER->state);
      call.Set<Handle>(Call::This, classInstance);
      call.Invoke(report);
    }
    break;
  case Mid::CollisionStarted:
    if (OnCollideStart != NULL)
    {
      Call call(OnCollideStart, ZILCHMANAGER->state);
      call.Set<Handle>(Call::This, classInstance);
      call.Set<>(0, ((CollisionStarted*)message)->otherObj->GetOwner());
      call.Invoke(report);
    }
    break;
  case Mid::CollisionPersisted:
    if (OnCollidePersist != NULL)
    {
      Call call(OnCollidePersist, ZILCHMANAGER->state);
      call.Set<Handle>(Call::This, classInstance);
      call.Set<>(0, ((CollisionStarted*)message)->otherObj->GetOwner());
      call.Invoke(report);
    }
    break;
  case Mid::CollisionEnded:
    if (OnCollideEnd != NULL)
    {
      Call call(OnCollideEnd, ZILCHMANAGER->state);
      call.Set<Handle>(Call::This, classInstance);
      call.Set<>(0, ((CollisionStarted*)message)->otherObj->GetOwner());
      call.Invoke(report);
    }
    break;
  }
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
ZilchDefineType(OurZilchComponent, "OurZilchComponent", ZLib_Internal, builder, type)
{
}