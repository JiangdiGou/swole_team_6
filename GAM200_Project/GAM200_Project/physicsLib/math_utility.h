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
