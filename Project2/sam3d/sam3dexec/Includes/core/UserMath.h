#pragma once
#include <windows.h>
#include <math.h>


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
const float	EPSILON						= 0.0001f;
// Свести к нулю, если рядом
#define ZERO_CLAMP(x)	((EPSILON > fabs(x))?0.0f:(x))
// Равенство float'ов
#define FLOAT_EQ(x,v)	( ((v) - EPSILON) < (x) && (x) < ((v) + EPSILON) )		// float equality test
// Обрезать, если выходит за пределы
#define LIMIT_RANGE(low, value, high)	{	if (value < low)	value = low;	else if(value > high)	value = high;	}
// Урезать, если выходит за пределы
#define CUT_RANGE(low, value, high)	{	if (value < low)	value = value - low + high;	else if(value >= high)	value -= high;	}




float __inline ulrsqrt(float &x);
/*
    sqrt(x) = x / sqrt(x)
*/
void MyFtoL(int* i, float &f);//быстрое преобразование float -> int

int __inline roundf(float &x); 


float __inline ArcTan(float &a); //Арктангенс

float __inline ArcCos(float &a); //Аркосинус

DWORD HI_LOW(WORD &HI,WORD &LOW); //Складиывает двойное слово DWORD из двух WORD

int __inline Abs(int &a);

float __inline Abs(float &a);