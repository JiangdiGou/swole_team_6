#pragma once

#include "BaseComponent.hpp"

class Transform : public BaseComponent
{
public:
  Transform();
  ~Transform();

  void Init();
  void Shutdown();

  int            property_int_;
  float          property_float_;
  unsigned short property_ushort_;
  bool           property_bool_;
  char           property_char_;

private:

};



Transform::Transform()
{

}

Transform::~Transform()
{

}

void Transform::Init()
{
  scale_ = 1.0f;
}

void Transform::Shutdown()
{

}