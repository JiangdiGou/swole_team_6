#ifndef MATH_UTILITY_H
#define MATH_UTILITY_H
#include <math.h>
#include <algorithm>

#define FLOAT_PI 3.14159265358979323846f

//const float MathF::eps = 100 * FLT_EPSILON;

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


//MathFunctions

class Vec2D
{
public:
	float x;
	float y;
private:

public:
	Vec2D() : x(0), y(0) {}

	Vec2D(const float x, const float y) : x(x), y(y) {}

	void Set(float newX, float newY)
	{
		x = newX;
		y = newY;
	}

	void Clear()
	{
		x = 0.0f;
		y = 0.0f;
	}

	float Magnitude()
	{
		return sqrtf(x*x + y*y);
	}

	Vec2D Normalize()
	{
		Vec2D result;

		// Find the magnitude
		float mag = this->Magnitude();

		result.x = x / mag;
		result.y = y / mag;

		return result;
	}

	void Invert()
	{
		x = -x;
		y = -y;
	}

	float SqrMagnitude()
	{
		return(x*x + y*y);
	}

	// Add
	void operator+=(const Vec2D &vec)
	{
		x += vec.x;
		y += vec.y;
	}

	Vec2D operator+(const Vec2D& vec) const
	{
		return Vec2D(x + vec.x, y + vec.y);
	}


	// Subtract
	void operator-=(const Vec2D &vec)
	{
		x -= vec.x;
		y -= vec.y;
	}

	Vec2D operator-(const Vec2D& vec) const
	{
		return Vec2D(x - vec.x, y - vec.y);
	}

	Vec2D operator-(void)
	{
		return (Vec2D(-1 * x, -1 * y));
	}

	friend Vec2D operator*(const Vec2D& vec, const float scale)
	{
		return Vec2D(vec.x*scale, vec.y*scale);
	}

	friend Vec2D operator*(const float scale, const Vec2D& vec)
	{
		return Vec2D(vec.x*scale, vec.y*scale);
	}

	void operator*=(const float scale)
	{
		x *= scale;
		y *= scale;
	}

	void operator/=(const float scale)
	{
		if (scale == 0.0f)
		{
			throw "Division by zero";
		}

		x /= scale;
		y /= scale;
	}

	friend Vec2D operator/(const Vec2D& vec, const float scale)
	{
		if (scale == 0.0f)
		{
			throw "Division by zero";
		}
		return Vec2D(vec.x / scale, vec.y / scale);
	}
	friend Vec2D operator/(const float scale, const Vec2D& vec)
	{
		if (scale == 0.0f)
			return Vec2D(0.0f, 0.0f);
		else
			return Vec2D(vec.x / scale, vec.y / scale);
	}

	// Returns true if the vectors are equal.
	bool operator==(const Vec2D& rhs)
	{
		return (x == rhs.x && y == rhs.y);
	}

	// Returns true if vectors are not equal
	bool operator!=(const Vec2D& rhs)
	{
		return !(*this == rhs);
	}

	// Adds the vector to this, scaled by the given amount
	void AddScale(const Vec2D& vec, float scale)
	{
		x += vec.x * scale;
		y += vec.y * scale;
	}

	void SubScale(const Vec2D& vec, float scale)
	{
		x -= vec.x * scale;
		y -= vec.y * scale;
	}


	/* STATIC FUNCTIONS */

	// Distance
	static float Distance(Vec2D &pVec0, Vec2D &pVec1)
	{
		float xd = pVec1.x - pVec0.x;
		float yd = pVec1.y - pVec0.y;

		return sqrtf(xd*xd + yd*yd);
	}

	// Dot Product
	static float DotProduct(Vec2D &pVec0, Vec2D &pVec1)
	{
		return pVec0.x*pVec1.x + pVec0.y*pVec1.y;
	}

	static Vec2D CrossProduct(float a, const Vec2D &pVec)
	{
		return Vec2D(-a*pVec.y, a*pVec.x);
	}

	static Vec2D CrossProduct(const Vec2D &pVec, float a)
	{
		return Vec2D(a*pVec.y, -a*pVec.x);
	}

	static float CrossProduct(const Vec2D &pVec0, const Vec2D &pVec1)
	{
		return(pVec0.x * pVec1.y - pVec0.y * pVec1.x);
	}

	// Max
	// Returns a vector that is made from the largest components of two vectors.
	static Vec2D Max(Vec2D &pVec0, Vec2D &pVec1)
	{
		Vec2D max;
		if (pVec0.x > pVec1.x)
		{
			max.x = pVec0.x;
		}
		else
		{
			max.x = pVec1.x;
		}

		if (pVec0.y > pVec1.y)
		{
			max.y = pVec0.y;
		}
		else
		{
			max.y = pVec1.y;
		}

		return max;
	}

	// Min
	static Vec2D Min(Vec2D &pVec0, Vec2D &pVec1)
	{
		Vec2D min;
		if (pVec0.x < pVec1.x)
		{
			min.x = pVec0.x;
		}
		else
		{
			min.x = pVec1.x;
		}

		if (pVec0.y < pVec1.y)
		{
			min.y = pVec0.y;
		}
		else
		{
			min.y = pVec1.y;
		}

		return min;
	}

};
typedef Vec2D Vector2;

class Vector3D
{
public:
	float x;
	float y;
	float z;
private:

public:
	Vector3D() : x(0), y(0), z(0) {} // constructor to zero out

	Vector3D(const float x, const float y, const float z)
		: x(x), y(y), z(z) {}

	void Set(float newX, float newY, float newZ)
	{
		x = newX;
		y = newY;
		z = newZ;
	}

	// Zero all the components of the vector
	void Clear()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	float Magnitude()
	{
		return sqrtf(x*x + y*y + z*z);
	}

	Vector3D Normalize()
	{
		Vector3D result;

		// Find the magnitude
		float mag = this->Magnitude();

		result.x = x / mag;
		result.y = y / mag;
		result.z = z / mag;

		return result;
	}

	void Invert()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	float SqrMagnitude()
	{
		return(x*x + y*y + z*z);
	}

	// Add
	void operator+=(const Vector3D &vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
	}

	Vector3D operator+(const Vector3D& vec) const
	{
		return Vector3D(x + vec.x, y + vec.y, z + vec.z);
	}

	// Subtract
	void operator-=(const Vector3D &vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
	}

	Vector3D operator-(const Vector3D& vec) const
	{
		return Vector3D(x - vec.x, y - vec.y, z - vec.z);
	}

	Vector3D operator-(void)
	{
		return (Vector3D(-1 * x, -1 * y, -1 * z));
	}

	void operator*=(const float scale)
	{
		x *= scale;
		y *= scale;
		z *= scale;
	}

	friend Vector3D operator*(const Vector3D& vec, const float scale)
	{
		return Vector3D(vec.x*scale, vec.y*scale, vec.z*scale);
	}

	friend Vector3D operator*(const float scale, const Vector3D& vec)
	{
		return Vector3D(vec.x*scale, vec.y*scale, vec.z*scale);
	}

	void operator/=(const float scale)
	{
		if (scale == 0.0f)
		{
			throw "Division by zero";
		}
		x /= scale;
		y /= scale;
		z /= scale;
	}

	friend Vector3D operator/(const Vector3D& vec, const float scale)
	{
		if (scale == 0.0f)
		{
			throw "Division by zero";
		}
		return Vector3D(vec.x / scale, vec.y / scale, vec.z / scale);
	}

	friend Vector3D operator/(const float scale, const Vector3D& vec)
	{
		if (scale == 0.0f)
			return Vector3D(0.0f, 0.0f, 0.0f);
		else
			return Vector3D(vec.x / scale, vec.y / scale, vec.z / scale);
	}

	// Returns true if the vectors are equal.
	bool operator==(const Vector3D& rhs)
	{
		return (x == rhs.x && y == rhs.y && z == rhs.z);
	}

	// Returns true if vectors are not equal
	bool operator!=(const Vector3D& rhs)
	{
		return !(*this == rhs);
	}

	// Adds the vector to this, scaled by the given amount
	void addScale(const Vector3D& vec, float scale)
	{
		x += vec.x * scale;
		y += vec.y * scale;
		z += vec.z * scale;
	}

	void subScale(const Vector3D& vec, float scale)
	{
		x -= vec.x * scale;
		y -= vec.y * scale;
		z -= vec.z * scale;
	}


	/* STATIC FUNCTIONS */

	// Distance
	static float Distance(Vector3D &pVec0, Vector3D &pVec1)
	{
		float xd = pVec1.x - pVec0.x;
		float yd = pVec1.y - pVec0.y;
		float zd = pVec1.z - pVec0.z;

		return sqrt(xd*xd + yd*yd + zd*zd);
	}

	// Dot Product
	static float DotProduct(Vector3D &pVec0, Vector3D &pVec1)
	{
		return pVec0.x*pVec1.x + pVec0.y*pVec1.y + pVec0.z*pVec1.z;
	}
	// Cross Product
	static Vector3D CrossProduct(Vector3D &pVec0, Vector3D &pVec1)
	{
		return Vector3D(pVec0.y*pVec1.z - pVec0.z*pVec1.y, pVec0.z*pVec1.x - pVec0.x*pVec1.z,
			pVec0.x*pVec1.y - pVec0.y*pVec1.x);
	}

	// Projects a vector onto another vector.
	static Vector3D Projection(Vector3D &pVec0, Vector3D &pVec1)
	{
		// Dot product between pVec0 and pVec1
		float dot = DotProduct(pVec0, pVec1);

		// Calculate bottom
		float bot = pVec1.x*pVec1.x + pVec1.y*pVec1.y + pVec1.z*pVec1.z;
		// Find the scalar projection
		float scalarProj = dot / bot;

		// Vector scalar multiplication 
		return Vector3D(scalarProj*pVec1.x, scalarProj*pVec1.y, scalarProj*pVec1.z);
	}

	// Reflects a vector off the plane defined by a normal.
	static Vector3D Reflection(Vector3D &inDir, Vector3D &inNorm)
	{
		float scale = DotProduct(inDir, inNorm);
		// s = (v dot n)n
		Vector3D s(scale*inNorm.x, scale*inNorm.y, scale*inNorm.z);

		// 2*s
		s.x *= 2.0f;
		s.y *= 2.0f;
		s.z *= 2.0f;

		// r = 2 * (v dot n)n - v
		// r = s - v
		return Vector3D(s.x - inDir.x, s.y - inDir.y, s.z - inDir.z);
	}

	static Vector3D Max(Vector3D &pVec0, Vector3D &pVec1)
	{
		Vector3D max;
		if (pVec0.x > pVec1.x)
		{
			max.x = pVec0.x;
		}
		else
		{
			max.x = pVec1.x;
		}

		if (pVec0.y > pVec1.y)
		{
			max.y = pVec0.y;
		}
		else
		{
			max.y = pVec1.y;
		}

		if (pVec0.z > pVec1.z)
		{
			max.z = pVec0.z;
		}
		else
		{
			max.z = pVec1.z;
		}

		return max;
	}

	// Min
	static Vector3D Min(Vector3D &pVec0, Vector3D &pVec1)
	{
		Vector3D min;
		if (pVec0.x < pVec1.x)
		{
			min.x = pVec0.x;
		}
		else
		{
			min.x = pVec1.x;
		}

		if (pVec0.y < pVec1.y)
		{
			min.y = pVec0.y;
		}
		else
		{
			min.y = pVec1.y;
		}

		if (pVec0.z < pVec1.z)
		{
			min.z = pVec0.z;
		}
		else
		{
			min.z = pVec1.z;
		}

		return min;
	}
};
typedef Vector3D Vector3;

#endif