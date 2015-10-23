#ifndef TRANSFORM_H
#define TRANSFORM_H
//#include "all the header" //Math/Vec3.h
#include "../Composition.h"
#include "../engineGraphics/Graphics.h"
#include "math_utility.h"

//Transform Component
class Transform : public GameComponent
{
public:
	friend class Body;
	Transform( Vector3 pos = Vector3(), Vector3 rot = Vector3(),
		Vector3 scal = Vector3());
	~Transform() override;

	//Inherited Methods
	void Initialize() override;
	void Update(float dt) override;
	void Release() override;
	//Vector2 Position;

	//Getters
	Vector3& GetPosition();
	Vector3& GetRotation();
	Vector3& GetScale();
	Vector2 GetPositionXY();
	float GetPositionX();
	float GetPositionY();

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

  glm::mat4 calculateTransformMatrix();

private:
	
	Vector3 position;
	Vector3 scale;
	Vector3 rotation;
	bool dontRotate;

public:
	Vector2 pos2d;//...
};

#endif TRANSFORM_H