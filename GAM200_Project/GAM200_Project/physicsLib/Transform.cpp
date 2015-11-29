/*****************************************************************************/
/*!
\file    Transform.cpp
\author  Jiangdi Gou
\par     contact: jiangdi.g@digipen.edu
\brief
The functions for general usage of transform in the game.
\remarks


All content 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/
#include"Transform.h"
#include "../PleaseWork/ActionSystem.h"

Transform::Transform( Vector3 pos, Vector3 rot, Vector3 scal) :
position(pos), rotation(rot), scale(scal)
{
  scale = Vector3(1.0f, 1.0f, 1.0f);
  position = Vector3(-1.0f, 1.0f, 1.0f);
}

Transform::~Transform()
{
}

void Transform::Initialize()
{
}

void Transform::Update(float dt)
{
	pos2d.x = position.x;
	pos2d.y = position.y;
}

void Transform::SerializeRead(Serializer& str)
{
  StreamRead(str, position);
  StreamRead(str, scale);
  StreamRead(str, rotation);
  StreamRead(str, dontRotate);
}

void Transform::SerializeWrite(Serializer& str)
{
  StreamWrite(str, (int&)TypeId);
  StreamWrite(str);
  StreamWrite(str, position);
  StreamWrite(str);
  StreamWrite(str, scale);
  StreamWrite(str);
  StreamWrite(str, rotation);
  StreamWrite(str);
  StreamWrite(str, dontRotate);
  StreamWrite(str);
}

void Transform::Release()
{
}

Vector3& Transform::GetPosition()
{
	return position;
}

Vector3& Transform::GetRotation()
{
	return rotation;
}

Vector3& Transform::GetScale()
{
	return scale;
}

Vector2 Transform::GetPositionXY()
{
	return Vector2(position.x, position.y);
}
float Transform::GetPositionX()
{
  return position.x;
}
float Transform::GetPositionY()
{
  return position.y;
}

void Transform::SetPosition(const Vector2 pos)
{
	position.x = pos.x;
	position.y = pos.y;
}

void Transform::SetPosition(const Vector3 vec)
{
	position = vec;
}

void Transform::SetPositionX(float x)
{
	position.x = x;
}

void Transform::SetPositionY(float y)
{
	position.y = y;
}

void Transform::SetPositionZ(float z)
{
	position.z = z;
}

void Transform::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Transform::SetRotation(Vector3 rot)
{
	rotation = rot;
}

void Transform::SetRotationX(float x)
{
	rotation.x = x;
}

void Transform::SetRotationY(float y)
{
	rotation.y = y;
}

void Transform::SetRotationZ(float z)
{
	rotation.z = z;
}

void Transform::SetRotation(float x, float y, float z)
{
	rotation.x = x;
	rotation.y = y;
	rotation.z = z;
}

void Transform::SetRotation(const Vector2 rot)
{
	rotation.x = rot.x;
	rotation.y = rot.y;
}

void Transform::SetScale(Vector3 scal)
{
	scale = scal;
}

void Transform::SetScaleX(float x)
{
	scale.x = x;
}

void Transform::SetScaleY(float y)
{
	scale.y = y;
}

void Transform::SetScaleZ(float z)
{
	scale.z = z;
}

void Transform::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

void Transform::SetScale(const Vector2 scal)
{
	scale.x = scal.x;
	scale.y = scal.y;
}

glm::mat4 Transform::calculateTransformMatrix()
{
  glm::mat4 transform;
  glm::mat4 scaleMat, translateMat, rotMat;

  scaleMat = glm::scale(scaleMat, glm::vec3(scale.x, scale.y, scale.z));

  translateMat = glm::translate(translateMat, glm::vec3(
    position.x, position.y, position.z));
  //Since we're in 2d, rotation occurs about the Z axis
  //Can be changed later if you want different types of rotation
  rotMat = glm::rotate(rotMat, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

  transform = translateMat * rotMat * scaleMat;

  return transform;
}

ZilchDefineType(Transform, "Transform", ZLib_Internal, builder, type)
{
  ZilchBindConstructor(builder, type, Transform, "pos, rot, scale", Vector3, Vector3, Vector3);
  ZilchBindDestructor(builder, type, Transform);
  //Getters
  ZilchBindMethod(builder, type, &Transform::GetPosition, ZilchNoOverload, "GetPosition", ZilchNoNames);
  ZilchBindMethod(builder, type, &Transform::GetRotation, ZilchNoOverload, "GetRotation", ZilchNoNames);
  ZilchBindMethod(builder, type, &Transform::GetScale, ZilchNoOverload, "GetScale", ZilchNoNames);
  ZilchBindMethod(builder, type, &Transform::GetPositionXY, ZilchNoOverload, "GetPositionXY", ZilchNoNames);
  ZilchBindMethod(builder, type, &Transform::GetPositionX, ZilchNoOverload, "GetPositionX", ZilchNoNames);
  ZilchBindMethod(builder, type, &Transform::GetPositionY, ZilchNoOverload, "GetPositionY", ZilchNoNames);
  //Setters
  ZilchBindMethod(builder, type, &Transform::SetPosition, (void (Transform::*)(const Vector3)), "SetPosition", "pos");
  ZilchBindMethod(builder, type, &Transform::SetPosition, (void (Transform::*)(const Vector2)), "SetPosition", "pos");
  ZilchBindMethod(builder, type, &Transform::SetPosition, (void (Transform::*)(float, float, float)), "SetPosition", "x, y, z");

  ZilchBindMethod(builder, type, &Transform::SetPositionX, ZilchNoOverload, "SetPositionX", ZilchNoNames);
  ZilchBindMethod(builder, type, &Transform::SetPositionY, ZilchNoOverload, "SetPositionY", ZilchNoNames);
  ZilchBindMethod(builder, type, &Transform::SetPositionZ, ZilchNoOverload, "SetPositionZ", ZilchNoNames);

  ZilchBindMethod(builder, type, &Transform::SetRotation, (void (Transform::*)(Vector3)), "SetRotation", "rot");
  ZilchBindMethod(builder, type, &Transform::SetRotation, (void (Transform::*)(const Vector2)), "SetRotation", "rot");
  ZilchBindMethod(builder, type, &Transform::SetRotation, (void (Transform::*)(float, float, float)), "SetRotation", "x, y, z");

  ZilchBindMethod(builder, type, &Transform::SetRotationX, ZilchNoOverload, "SetRotationX", ZilchNoNames);
  ZilchBindMethod(builder, type, &Transform::SetRotationY, ZilchNoOverload, "SetRotationY", ZilchNoNames);
  ZilchBindMethod(builder, type, &Transform::SetRotationZ, ZilchNoOverload, "SetRotationZ", ZilchNoNames);

  ZilchBindMethod(builder, type, &Transform::SetScale, (void (Transform::*)(Vector3)), "SetRotation", "scal");
  ZilchBindMethod(builder, type, &Transform::SetScale, (void (Transform::*)(const Vector2)), "SetRotation", "scal");
  ZilchBindMethod(builder, type, &Transform::SetScale, (void (Transform::*)(float, float, float)), "SetRotation", "x, y, z");

  ZilchBindMethod(builder, type, &Transform::SetScaleX, ZilchNoOverload, "SetScaleX", ZilchNoNames);
  ZilchBindMethod(builder, type, &Transform::SetScaleY, ZilchNoOverload, "SetScaleY", ZilchNoNames);
  ZilchBindMethod(builder, type, &Transform::SetScaleZ, ZilchNoOverload, "SetScaleZ", ZilchNoNames);
}