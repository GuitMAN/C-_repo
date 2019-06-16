#pragma once

#include "UserMath.h"


class Vector2f
{
public:

	Vector2f()
	{
		x = 0; y = 0; z = 0;
	}

	Vector2f(const float X, const float Y)
	{
		x = X; y = Y; 
	}

	void Set(const float X, const float Y)
	{
		x = X; y = Y; 
	}

	Vector2f operator-() const { return Vector2f(-x, -y); }

	Vector2f& operator=(const Vector2f& other) { x = other.x; y = other.y;  return *this; }

	Vector2f operator+(const Vector2f& other) const { return Vector2f(x + other.x, y + other.y); }
	Vector2f& operator+=(const Vector2f& other) { x += other.x; y += other.y; z += other.z; return *this; }

	Vector2f operator-(const Vector2f& other) const { return Vector2f(x - other.x, y - other.y); }
	Vector2f& operator-=(const Vector2f& other) { x -= other.x; y -= other.y; return *this; }

	Vector2f operator*(const Vector2f& other) const { return Vector2f(x * other.x, y * other.y); }
	Vector2f& operator*=(const Vector2f& other) { x *= other.x; y *= other.y;  return *this; }
	Vector2f operator*(const float v) const { return Vector2f(x * v, y * v); }
	Vector2f& operator*=(const float v) { x *= v; y *= v;  return *this; }

	Vector2f operator/(const Vector2f& other) const { return Vector2f(x / other.x, y / other.y); }
	Vector2f& operator/=(const Vector2f& other) { x /= other.x; y /= other.y;  return *this; }
	Vector2f operator/(const float v) const { float i = (float)1.0 / v; return Vector2f(x * i, y * i); }
	Vector2f& operator/=(const float v) { float i = (float)1.0 / v; x *= i; y *= i; return *this; }

	bool operator<=(const Vector2f& other) const { return x <= other.x && y <= other.y };
	bool operator>=(const Vector2f& other) const { return x >= other.x && y >= other.y };

	bool operator==(const Vector2f& other) const { return other.x == x && other.y == y }
	bool operator!=(const Vector2f& other) const { return other.x != x || other.y != y }


	inline float dot(const Vector2f& other) const
	{
		return x * other.x + y * other.y ;
	}

	//! Returns length of the vector.
	inline float getLength() const
	{
		float leng2 = x * x + y * y ;
		return Sam3d::ulrsqrt(leng2);
	}
private:
#define ONE_AS_INTEGER ((DWORD)(0x3F800000))
	float __inline InvSqrt(const float& a)
	{
		DWORD   tmp = ((ONE_AS_INTEGER << 1) + ONE_AS_INTEGER - *(DWORD*)& a) >> 1;
		float y = *(float*)& tmp;
		return y * (1.47f - 0.47f * a * y * y);
	}
public:
	inline void Normalize()
	{
		float L_squared, one_over_L;
		L_squared = (x * x) + (y * y);
		one_over_L = InvSqrt(L_squared);
		//  uSqrt(L_squared);
		x = x * one_over_L;
		y = y * one_over_L;
		z = z * one_over_L;
	}

	inline BOOL IsZero()
	{
		if (!FLOAT_EQ(x, 0)) return FALSE;
		if (!FLOAT_EQ(y, 0)) return FALSE;
		return TRUE;
	}

//	inline Vector2f Cross(const Vector2f& p)  const
	//{
	//	return Vector2f(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
//	}

	inline Vector2f getInterpolated(const Vector2f& other, float d) const
	{
		float inv = 1.0f - d;
		return Vector2f(other.x * inv + x * d, other.y * inv + y * d);
	}
	// Вращает вектор вокруг оси OX
	inline void RotateX(float angle)
	{
		float oy = y;
		angle = DEGTORAD(angle);
		y = (float)(oy * cos(angle));
		
	}
	// Вращает вектор вокруг оси OY
	inline void RotateY(float angle)
	{
		float ox = x;
		angle = DEGTORAD(angle);
		x = (float)(ox * cos(angle));
		
	}
	

	//operator const float*() const {return &x;}
	float x, y;
};
