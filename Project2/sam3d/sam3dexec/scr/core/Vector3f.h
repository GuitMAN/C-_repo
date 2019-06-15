#pragma once

#include "Usermath.h"

///////////////////////////////////////////////////////////////////////////
// Vector
///////////////////////////////////////////////////////////////////////////

// Вектор с тремя компонентами типа float
class Vector3f 
{
public:

    Vector3f()
    { x = 0; y = 0; z = 0; }

	Vector3f( const float X, const float Y, const float Z)
    { x = X; y = Y; z = Z; }

	void Set( const float X, const float Y, const float Z)
    { x = X; y = Y; z = Z; }

	Vector3f operator-() const { return Vector3f(-x, -y, -z);   }

	Vector3f& operator=(const Vector3f& other)	{ x = other.x; y = other.y; z = other.z; return *this; }

		Vector3f operator+(const Vector3f& other) const { return Vector3f(x + other.x, y + other.y, z + other.z);	}
		Vector3f& operator+=(const Vector3f& other)	{ x+=other.x; y+=other.y; z+=other.z; return *this; }

		Vector3f operator-(const Vector3f& other) const { return Vector3f(x - other.x, y - other.y, z - other.z);	}
		Vector3f& operator-=(const Vector3f& other)	{ x-=other.x; y-=other.y; z-=other.z; return *this; }

		Vector3f operator*(const Vector3f& other) const { return Vector3f(x * other.x, y * other.y, z * other.z);	}
		Vector3f& operator*=(const Vector3f& other)	{ x*=other.x; y*=other.y; z*=other.z; return *this; }
		Vector3f operator*(const float v) const { return Vector3f(x * v, y * v, z * v);	}
		Vector3f& operator*=(const float v) { x*=v; y*=v; z*=v; return *this; }

		Vector3f operator/(const Vector3f& other) const { return Vector3f(x / other.x, y / other.y, z / other.z);	}
		Vector3f& operator/=(const Vector3f& other)	{ x/=other.x; y/=other.y; z/=other.z; return *this; }
		Vector3f operator/(const float v) const { float i=(float)1.0/v; return Vector3f(x * i, y * i, z * i);	}
		Vector3f& operator/=(const float v) { float i=(float)1.0/v; x*=i; y*=i; z*=i; return *this; }

		bool operator<=(const Vector3f&other) const { return x<=other.x && y<=other.y && z<=other.z;};
		bool operator>=(const Vector3f&other) const { return x>=other.x && y>=other.y && z>=other.z;};

		bool operator==(const Vector3f& other) const { return other.x==x && other.y==y && other.z==z; }
		bool operator!=(const Vector3f& other) const { return other.x!=x || other.y!=y || other.z!=z; }


	inline float dot(const Vector3f& other) const 
	{
		return x*other.x + y*other.y + z*other.z;
	}

	//! Returns length of the vector.
	inline float getLength() const 
	{
		float leng2 = x*x + y*y + z*z;
		return ulrsqrt(leng2); 
	}
private:
#define ONE_AS_INTEGER ((DWORD)(0x3F800000))
	float __inline InvSqrt(const float &x)
	{
		DWORD   tmp = ((ONE_AS_INTEGER << 1) + ONE_AS_INTEGER - *(DWORD*)&x) >> 1;
		 float y = *(float*)&tmp;
		return y * (1.47f - 0.47f * x * y * y);
	}
public:
	inline void Normalize()
	{
		float L_squared, one_over_L;
		L_squared = (x * x) + (y * y) + (z * z);
		one_over_L = InvSqrt(L_squared);
		//  uSqrt(L_squared);
		x = x * one_over_L;
		y = y * one_over_L;
		z = z * one_over_L;
	}

	inline BOOL IsZero()
	{
		if (!FLOAT_EQ(x,0)) return FALSE;
		if (!FLOAT_EQ(y,0)) return FALSE;
		if (!FLOAT_EQ(z,0)) return FALSE;
		return TRUE;
	}

	inline Vector3f Cross(const Vector3f& p)  const
	{
		return Vector3f(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
	}

	inline Vector3f getInterpolated( const Vector3f& other, float d) const
	{
		float inv = 1.0f - d;
		return Vector3f(other.x*inv + x*d, other.y*inv + y*d,	other.z*inv + z*d);
	}
	// Вращает вектор вокруг оси OX
	inline void RotateX(float angle)
	{
		float oy=y,oz=z;
		angle=DEGTORAD(angle);
		y=(float)((oy * cos(angle) )+(oz * (-sin(angle) ) ));
		z=(float)((oy * sin(angle) )+(oz * (cos(angle) ) ));
	}
	// Вращает вектор вокруг оси OY
	inline void RotateY(float angle)
	{
		float ox=x,oz=z;
		angle=DEGTORAD(angle);
		x=(float)((ox * cos(angle) )+(oz * (-sin(angle) ) ));
		z=(float)((ox * sin(angle) )+(oz * (cos(angle) ) ));
	}
	// Вращает вектор вокруг оси OZ
	inline void RotateZ(float angle)
	{
		float ox=x,oy=y;
		angle=DEGTORAD(angle);
		x=(float)((ox * cos(angle) )+(oy * (-sin(angle) ) ));
		y=(float)((ox * sin(angle) )+(oy * (cos(angle) ) ));
	}
	
	//operator const float*() const {return &x;}
	float x, y, z;
};


