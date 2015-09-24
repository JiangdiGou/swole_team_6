//#include "our precompiled header"
#include"Transform.h"
#include"../Composition.h"


Transform::Transform(GameObjectComposition* Owner, Vector3 pos, Vector3 rot, Vector3 scal) :
GameComponent(ComponentTypeId::CT_Transform, Owner), position(pos),rotation(rot), scale(scal)
{
}

Transform::~Transform()
{
}

void Transform::Initialize()
{
}

void Transform::Update()
{
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