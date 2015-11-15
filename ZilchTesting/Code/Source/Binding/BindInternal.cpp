#include "BindInternal.hpp"

#include "Character.hpp"
#include "Player.hpp"


ZilchDefineStaticLibrary(ZLib_Internal)
{
  // We have to initialize all types that we have bound to our library
  // Ideally we could use pre-main or automatic registration, but there's a major issue where
  // compilers will automatically remove "unreferenced" classes, even if they are referenced
  // by globals/pre-main initializations. This method ensures that all classes will be properly bound
  ZilchInitializeType(Character);
  ZilchInitializeType(Player);
}