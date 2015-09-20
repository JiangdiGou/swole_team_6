#pragma once
#include "all the header" //Math/Vec3.h

class Transform : public IComponent
{
public:
	friend class RigidBody;
	Transform(IEntity* Owner = NULL, Vector3 pos = Vector3(), Vector3 rot = Vector3(),
		Vector3 scal = Vector3());
	~Transform() override;

	//Inherited Methods
	bool Initialize() override;
	void Update(float dt) override;
	void Release() override;

	//Getters
	Vector3& GetPosition();
	Vector3& GetRotation();
	Vector3& GetScale();

	//Setters
	void SetPosition(const Vector3 pos);
	void SetPosition(const Vector2 pos);
	void SetPosition(float x, float y, float z);
	void SetPositionX(float x);
	void SetPositionY(float y);
	void SetPositionZ(float z);

	void SetRotation(Vector3 rot);
	void SetRotation(const Vector2 rot);
	void SetRotationX(float x);
	void SetRotationY(float y);
	void SetRotationZ(float z);
	void SetRotation(float x, float y, float z);

	void SetScale(Vector3 scal);
	void SetScale(const Vector2 scal);
	void SetScaleX(float x);
	void SetScaleY(float y);
	void SetScaleZ(float z);
	void SetScale(float x, float y, float z);


private:
	Vector3 position;
	Vector3 scale;
	Vector3 rotation;
};