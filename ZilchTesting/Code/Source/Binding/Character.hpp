#pragma once


#include <iostream>

#include "BindInternal.hpp"
#include <ZILCH/Zilch.hpp>

using namespace Zilch;




struct MyReal3
{
  float my_x;
  float my_y;
  float my_z;
  MyReal3(float x  = 0, float y = 0, float z = 0) : my_x(x), my_y(y), my_z(z) {}
};

ZilchDeclareRedirectType(MyReal3, Zilch::Real3);

class Character : public EventHandler
{
public:
  // Using internal binding we'll declare that this class should be registered with Zilch
  // This macro is only a declaration, and somewhere in a single cpp file we must use the 'ZilchDefineBaseType' macro
  // ReferenceType means it will be allocated on the heap and always referenced by handle
  //ZilchDeclareBaseType(Character, TypeCopyMode::ReferenceType);
  ZilchDeclareDerivedType(Character, EventHandler);

  // Constructor / Destructor
  Character();
  virtual ~Character();


  // Member Functions

  virtual void Speak() const;

  void Yell(float volume) const;
  void Yell() const;

  float GetHealth() const;
  void SetHealth(float value);

  static int ComputeLives(float mana, int level);


  // Member Variables

  static const int MaxLives = 100;
  int Lives;

  MyReal3 MyPosition;

  // Non-bound variables
  float InternalHealth;

private:
};