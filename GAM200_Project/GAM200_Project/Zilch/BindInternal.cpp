#include "BindInternal.hpp"
#include "../Component.h"
#include "../engineAudio/SoundEmitter.h"
#include "../engineGraphics/Camera.h"
#include "../engineGraphics/Sprite.h"
#include "../physicsLib/Collision.h"
#include "../physicsLib/Transform.h"
#include "../mouseVector.h"
#include "../ZilchComponent.h"
#include "../physicsLib/PlayerState.h"

/*******************************************************************************
Converts std::string to Zilch::String and back
*******************************************************************************/
inline const Zilch::String StdStringToZeroString(const std::string& aString)
{
  return Zilch::String(aString.c_str(), aString.size());
}
inline const std::string ZeroStringToStdString(const Zilch::String& aString)
{
  return std::string(aString.c_str(), aString.size());
}

ZilchDefineStaticLibrary(ZLib_Internal)
{
  // We have to initialize all types that we have bound to our library
  // Ideally we could use pre-main or automatic registration, but there's a major issue where
  // compilers will automatically remove "unreferenced" classes, even if they are referenced
  // by globals/pre-main initializations. This method ensures that all classes will be properly bound
  //ZilchInitializeType(Character);
  //ZilchInitializeType(Player);
  ZilchInitializeType(GameComponent);
  ZilchInitializeType(GameObjectComposition);
  ZilchInitializeType(ComponentTypeId);
  ZilchInitializeType(SoundEmitter);
  ZilchInitializeType(Camera);
  ZilchInitializeType(Sprite);
  ZilchInitializeType(SpriteText);
  ZilchInitializeType(Body);
  ZilchInitializeType(Shape);
  ZilchInitializeType(ShapeAAB);
  ZilchInitializeType(Transform);
  ZilchInitializeType(MouseVector);
  ZilchInitializeType(PlayerState);
  ZilchInitializeType(OurZilchComponent);
  ZilchInitializeType(Vec2D);
  ZilchInitializeType(Vector3);

}
ZilchDefineRedirectType(std::string, StdStringToZeroString, ZeroStringToStdString);