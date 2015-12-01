/*****************************************************************************/
/*!
\file    math_utility.cpp
\author  Jiangdi Gou
\par     contact: jiangdi.g@digipen.edu
\brief
base 2D/3D vector struct with its related math functions.
\remarks


All content 2015 DigiPen (USA) Corporation, all rights reserved.
*/
/*****************************************************************************/

#include "Precompiled.h"
#include "math_utility.h"

float minimum(float a, float b)
{
	return a < b ? a : b;
}

float maximum(float a, float b)
{
	return a > b ? a : b;
}

bool equal_floats(float a, float b)
{
	const float epsilon = 1.0f / 8192.0f;/* should be small enough for 1.0f == pixel width */
	return fabsf(a - b) < epsilon;
}




float degrees_to_radian(float degrees)
{
	return degrees * FLOAT_PI / 180.0f;
}

float radian_to_degrees(float radian)
{
	return radian * 180.0f / FLOAT_PI;
}

void Vec2D::Set(float newX, float newY)
{
	x = newX;
	y = newY;
}

void  Vec2D::Clear()
{
	x = 0.0f;
	y = 0.0f;
}

float  Vec2D::Magnitude()
{
	return sqrtf(x*x + y*y);
}

Vec2D Vec2D::Normalize()
{
	Vec2D result;

	// Find the magnitude
	float mag = this->Magnitude();

	result.x = x / mag;
	result.y = y / mag;

	return result;
}

void  Vec2D::Invert()
{
	x = -x;
	y = -y;
}

float  Vec2D::SqrMagnitude()
{
	return(x*x + y*y);
}

// Add
void  Vec2D::operator+=(const Vec2D &vec)
{
	x += vec.x;
	y += vec.y;
}

Vec2D  Vec2D::operator+(const Vec2D& vec) const
{
	return Vec2D(x + vec.x, y + vec.y);
}

static Vec2D add_vector(const Vec2D* a, const Vec2D* b)
{
	const Vec2D r = { a->x + b->x, a->y + b->y };
	return r;
}


// Subtract


void  Vec2D::operator-=(const Vec2D &vec)
{
	x -= vec.x;
	y -= vec.y;
}

Vec2D  Vec2D::operator-(const Vec2D& vec) const
{
	return Vec2D(x - vec.x, y - vec.y);
}

Vec2D  Vec2D::operator-(void)
{
	return (Vec2D(-1 * x, -1 * y));
}

Vec2D operator*(const Vec2D& vec, const float scale)
{
	return Vec2D(vec.x*scale, vec.y*scale);
}

Vec2D operator*(const float scale, const Vec2D& vec)
{
	return Vec2D(vec.x*scale, vec.y*scale);
}

void  Vec2D::operator*=(const float scale)
{
	x *= scale;
	y *= scale;
}

void  Vec2D::operator/=(const float scale)
{
	if (scale == 0.0f)
	{
		throw "Division by zero";
	}

	x /= scale;
	y /= scale;
}

Vec2D operator/(const Vec2D& vec, const float scale)
{
	if (scale == 0.0f)
	{
		throw "Division by zero";
	}
	return Vec2D(vec.x / scale, vec.y / scale);
}
Vec2D operator/(const float scale, const Vec2D& vec)
{
	if (scale == 0.0f)
		return Vec2D(0.0f, 0.0f);
	else
		return Vec2D(vec.x / scale, vec.y / scale);
}

//inline float Vec2D::operator[](const int i)
//{
//	return (float) *this)[i]);
//}

// Returns true if the vectors are equal.
bool  Vec2D::operator==(const Vec2D& rhs)
{
	return (x == rhs.x && y == rhs.y);
}

// Returns true if vectors are not equal
bool  Vec2D::operator!=(const Vec2D& rhs)
{
	return !(*this == rhs);
}

// Adds the vector to this, scaled by the given amount
void  Vec2D::AddScale(const Vec2D& vec, float scale)
{
	x += vec.x * scale;
	y += vec.y * scale;
}

void  Vec2D::SubScale(const Vec2D& vec, float scale)
{
	x -= vec.x * scale;
	y -= vec.y * scale;
}

void Vector3D::Set(float newX, float newY, float newZ)
{
	x = newX;
	y = newY;
	z = newZ;
}

// Zero all the components of the vector
void Vector3D::Clear()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

float Vector3D::Magnitude()
{
	return sqrtf(x*x + y*y + z*z);
}

Vector3D Vector3D::Normalize()
{
	Vector3D result;

	// Find the magnitude
	float mag = this->Magnitude();

	result.x = x / mag;
	result.y = y / mag;
	result.z = z / mag;

	return result;
}

void Vector3D::Invert()
{
	x = -x;
	y = -y;
	z = -z;
}

float Vector3D::SqrMagnitude()
{
	return(x*x + y*y + z*z);
}

// Add
void Vector3D::operator+=(const Vector3D &vec)
{
	x += vec.x;
	y += vec.y;
	z += vec.z;
}

Vector3D Vector3D::operator+(const Vector3D& vec) const
{
	return Vector3D(x + vec.x, y + vec.y, z + vec.z);
}

// Subtract
void Vector3D::operator-=(const Vector3D &vec)
{
	x -= vec.x;
	y -= vec.y;
	z -= vec.z;
}

Vector3D Vector3D::operator-(const Vector3D& vec) const
{
	return Vector3D(x - vec.x, y - vec.y, z - vec.z);
}

Vector3D Vector3D::operator-(void)
{
	return (Vector3D(-1 * x, -1 * y, -1 * z));
}

void Vector3D::operator*=(const float scale)
{
	x *= scale;
	y *= scale;
	z *= scale;
}

Vector3D operator*(const Vector3D& vec, const float scale)
{
	return Vector3D(vec.x*scale, vec.y*scale, vec.z*scale);
}

Vector3D operator*(const float scale, const Vector3D& vec)
{
	return Vector3D(vec.x*scale, vec.y*scale, vec.z*scale);
}

void Vector3D::operator/=(const float scale)
{
	if (scale == 0.0f)
	{
		throw "Division by zero";
	}
	x /= scale;
	y /= scale;
	z /= scale;
}

Vector3D operator/(const Vector3D& vec, const float scale)
{
	if (scale == 0.0f)
	{
		throw "Division by zero";
	}
	return Vector3D(vec.x / scale, vec.y / scale, vec.z / scale);
}

Vector3D operator/(const float scale, const Vector3D& vec)
{
	if (scale == 0.0f)
		return Vector3D(0.0f, 0.0f, 0.0f);
	else
		return Vector3D(vec.x / scale, vec.y / scale, vec.z / scale);
}

// Returns true if the vectors are equal.
bool Vector3D::operator==(const Vector3D& rhs)
{
	return (x == rhs.x && y == rhs.y && z == rhs.z);
}

// Returns true if vectors are not equal
bool Vector3D::operator!=(const Vector3D& rhs)
{
	return !(*this == rhs);
}

// Adds the vector to this, scaled by the given amount
void Vector3D::addScale(const Vector3D& vec, float scale)
{
	x += vec.x * scale;
	y += vec.y * scale;
	z += vec.z * scale;
}

void Vector3D::subScale(const Vector3D& vec, float scale)
{
	x -= vec.x * scale;
	y -= vec.y * scale;
	z -= vec.z * scale;
}
ZilchDefineType(Vec2D, "Vec2D", ZLib_Internal, builder, type)
{
  type->HandleManager = ZilchManagerId(PointerManager);
  ZilchBindConstructor(builder, type, Vec2D, "x, y", const float, const float);
  ZilchBindConstructor(builder, type, Vec2D, ZilchNoNames);
  ZilchBindDestructor(builder, type, Vec2D, ZilchNoNames);

  ZilchBindField(builder, type, &Vec2D::x, "x", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &Vec2D::y, "y", PropertyBinding::GetSet);
}
ZilchDefineType(Vector3D, "Vector3D", ZLib_Internal, builder, type)
{
  type->HandleManager = ZilchManagerId(PointerManager);
  ZilchBindConstructor(builder, type, Vector3D, "x, y, z", const float, const float, const float);
  ZilchBindConstructor(builder, type, Vector3D, "vec, z", const Vector2&, const float);
  ZilchBindConstructor(builder, type, Vector3D, "vec", const Vector2&);
  ZilchBindConstructor(builder, type, Vector3D, ZilchNoNames);
  ZilchBindDestructor(builder, type, Vector3D, ZilchNoNames);

  ZilchBindField(builder, type, &Vector3D::x, "x", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &Vector3D::y, "y", PropertyBinding::GetSet);
  ZilchBindField(builder, type, &Vector3D::z, "z", PropertyBinding::GetSet);
}