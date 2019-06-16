#pragma once
#include <windows.h>
#include <math.h>
#include <iostream>

namespace Sam3d
{


	// Число пи
#define PI							3.14159265358979323846f
#define GRAD_PI						(180.000f/PI)
// Градусы -> радианы
#define DEGTORAD(a)					((a) * ( PI / 180.0f ))
// Радианы -> градусы
#define	RADTODEG(x)					((x) * ( 180.0f / PI ))
// Квадрат числа
#define SQR(x)						((x) * (x))
// Наименьшее
#define MAX(a,b)					((a < b) ? (b) : (a))
// Наибольшее
#define MIN(a,b)					((a < b) ? (a) : (b))



// Эпсилон для вычисления
	const float	EPSILON = 0.0001f;
	// Свести к нулю, если рядом
#define ZERO_CLAMP(x)	((EPSILON > fabs(x))?0.0f:(x))
// Равенство float'ов
#define FLOAT_EQ(x,v)	( ((v) - EPSILON) < (x) && (x) < ((v) + EPSILON) )		// float equality test
// Обрезать, если выходит за пределы
#define LIMIT_RANGE(low, value, high)	{	if (value < low)	value = low;	else if(value > high)	value = high;	}
// Урезать, если выходит за пределы
#define CUT_RANGE(low, value, high)	{	if (value < low)	value = value - low + high;	else if(value >= high)	value -= high;	}




	float __inline ulrsqrt(float& x);
	/*
		sqrt(x) = x / sqrt(x)
	*/
	void MyFtoL(int* i, float& f);//быстрое преобразование float -> int

	const int __inline roundf(const float& x);


	float __inline ArcTan(float& a); //Арктангенс

	float __inline ArcCos(float& a); //Аркосинус

	DWORD HI_LOW(WORD& HI, WORD& LOW); //Складиывает двойное слово DWORD из двух WORD

	int __inline Abs(int& a);

	float __inline Abs(float& a);



	//! returns minimum of two values. Own implementation to get rid of the STL (VS6 problems)
	template<class T>
	inline const T& min_(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	//! returns minimum of three values. Own implementation to get rid of the STL (VS6 problems)
	template<class T>
	inline const T& min_(const T& a, const T& b, const T& c)
	{
		return a < b ? min_(a, c) : min_(b, c);
	}

	//! returns maximum of two values. Own implementation to get rid of the STL (VS6 problems)
	template<class T>
	__inline const T& max_(const T& a, const T& b)
	{
		return a < b ? b : a;
	}

	//! returns maximum of three values. Own implementation to get rid of the STL (VS6 problems)
	template<class T>
	__inline const T& max_(const T& a, const T& b, const T& c)
	{
		return a < b ? max_(b, c) : max_(a, c);
	};

};