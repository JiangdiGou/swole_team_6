#pragma once


#include "Character.hpp"

#include "BindInternal.hpp"
#include <ZILCH/Zilch.hpp>

class Player : public Character
{
public:
  // Note here that we use the 'Derived' macro to inform Zilch that Player derives from Character
  // This allows implicit casting operations in Zilch as well as dynamic down-casts
  // The TypeCopyMode of the base type is used here (ReferenceType can only inherit from ReferenceType, and so on)
  ZilchDeclareDerivedType(Player, Character);


  // Constructor / Destructor
  Player(const Zilch::String& name, float startingHealth);
  virtual ~Player();


  // Member Functions

  // Note that we don't bind Speak again because it gets inherited from the base
  virtual void Speak() const;


  // Member Variables

  Zilch::String Name;
};
