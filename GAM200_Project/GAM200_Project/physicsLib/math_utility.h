#include <math.h>

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
//class MathF
//{
//public:
//
//	static float Lerp(float from, float to, float time);
//	static float InverseLerp(float from, float to, float current);
//	static float MoveTowards(float current, float target, float maxDelta);
//	static bool FloatsAreEqual(float a, float b);
//	static float maximum(float a, float b);
//	static float minimum(float a, float b);
//	static const float eps;
//
//
//};
//class Vector2D
//{
//public:
//	float x;
//	float y;
//private:
//
//public:
//	Vector2D() : x(0), y(0) {}
//
//	Vector2D(const float x, const float y) : x(x), y(y) {}
//
//	void Set(float newX, float newY)
//	{
//		x = newX;
//		y = newY;
//	}
//
//	void Clear()
//	{
//		x = 0.0f;
//		y = 0.0f;
//	}
//
//	float Magnitude()
//	{
//		return sqrtf(x*x + y*y);
//	}
//
//	Vector2D Normalize()
//	{
//		Vector2D result;
//
//		// Find the magnitude
//		float mag = this->Magnitude();
//
//		result.x = x / mag;
//		result.y = y / mag;
//
//		return result;
//	}
//
//	void Invert()
//	{
//		x = -x;
//		y = -y;
//	}
//
//	float SqrMagnitude()
//	{
//		return(x*x + y*y);
//	}
//
//	// Add
//	void operator+=(const Vector2D &vec)
//	{
//		x += vec.x;
//		y += vec.y;
//	}
//
//	Vector2D operator+(const Vector2D& vec) const
//	{
//		return Vector2D(x + vec.x, y + vec.y);
//	}
//
//
//	// Subtract
//	void operator-=(const Vector2D &vec)
//	{
//		x -= vec.x;
//		y -= vec.y;
//	}
//
//	Vector2D operator-(const Vector2D& vec) const
//	{
//		return Vector2D(x - vec.x, y - vec.y);
//	}
//
//	Vector2D operator-(void)
//	{
//		return (Vector2D(-1 * x, -1 * y));
//	}
//
//	friend Vector2D operator*(const Vector2D& vec, const float scale)
//	{
//		return Vector2D(vec.x*scale, vec.y*scale);
//	}
//
//	friend Vector2D operator*(const float scale, const Vector2D& vec)
//	{
//		return Vector2D(vec.x*scale, vec.y*scale);
//	}
//
//	void operator*=(const float scale)
//	{
//		x *= scale;
//		y *= scale;
//	}
//
//	void operator/=(const float scale)
//	{
//		if (scale == 0.0f)
//		{
//			throw "Division by zero";
//		}
//
//		x /= scale;
//		y /= scale;
//	}
//
//	friend Vector2D operator/(const Vector2D& vec, const float scale)
//	{
//		if (scale == 0.0f)
//		{
//			throw "Division by zero";
//		}
//		return Vector2D(vec.x / scale, vec.y / scale);
//	}
//	friend Vector2D operator/(const float scale, const Vector2D& vec)
//	{
//		if (scale == 0.0f)
//			return Vector2D(0.0f, 0.0f);
//		else
//			return Vector2D(vec.x / scale, vec.y / scale);
//	}
//
//	// Returns true if the vectors are equal.
//	bool operator==(const Vector2D& rhs)
//	{
//		return (x == rhs.x && y == rhs.y);
//	}
//
//	// Returns true if vectors are not equal
//	bool operator!=(const Vector2D& rhs)
//	{
//		return !(*this == rhs);
//	}
//
//	// Adds the vector to this, scaled by the given amount
//	void AddScale(const Vector2D& vec, float scale)
//	{
//		x += vec.x * scale;
//		y += vec.y * scale;
//	}
//
//	void SubScale(const Vector2D& vec, float scale)
//	{
//		x -= vec.x * scale;
//		y -= vec.y * scale;
//	}
//
//
//	/* STATIC FUNCTIONS */
//
//	// Distance
//	static float Distance(Vector2D &pVec0, Vector2D &pVec1)
//	{
//		float xd = pVec1.x - pVec0.x;
//		float yd = pVec1.y - pVec0.y;
//
//		return sqrtf(xd*xd + yd*yd);
//	}
//
//	// Dot Product
//	static float DotProduct(Vector2D &pVec0, Vector2D &pVec1)
//	{
//		return pVec0.x*pVec1.x + pVec0.y*pVec1.y;
//	}
//
//	static Vector2D CrossProduct(float a, const Vector2D &pVec)
//	{
//		return Vector2D(-a*pVec.y, a*pVec.x);
//	}
//
//	static Vector2D CrossProduct(const Vector2D &pVec, float a)
//	{
//		return Vector2D(a*pVec.y, -a*pVec.x);
//	}
//
//	static float CrossProduct(const Vector2D &pVec0, const Vector2D &pVec1)
//	{
//		return(pVec0.x * pVec1.y - pVec0.y * pVec1.x);
//	}
//
//	// Max
//	// Returns a vector that is made from the largest components of two vectors.
//	static Vector2D Max(Vector2D &pVec0, Vector2D &pVec1)
//	{
//		Vector2D max;
//		if (pVec0.x > pVec1.x)
//		{
//			max.x = pVec0.x;
//		}
//		else
//		{
//			max.x = pVec1.x;
//		}
//
//		if (pVec0.y > pVec1.y)
//		{
//			max.y = pVec0.y;
//		}
//		else
//		{
//			max.y = pVec1.y;
//		}
//
//		return max;
//	}
//
//	// Min
//	static Vector2D Min(Vector2D &pVec0, Vector2D &pVec1)
//	{
//		Vector2D min;
//		if (pVec0.x < pVec1.x)
//		{
//			min.x = pVec0.x;
//		}
//		else
//		{
//			min.x = pVec1.x;
//		}
//
//		if (pVec0.y < pVec1.y)
//		{
//			min.y = pVec0.y;
//		}
//		else
//		{
//			min.y = pVec1.y;
//		}
//
//		return min;
//	}
//
//};
//typedef Vector2D Vector2;