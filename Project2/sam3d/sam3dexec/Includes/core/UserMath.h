#pragma once
#include <windows.h>
#include <math.h>


// ����� ��
#define PI							3.14159265358979323846f
#define GRAD_PI						(180.000f/PI)
// ������� -> �������
#define DEGTORAD(a)					((a) * ( PI / 180.0f ))
// ������� -> �������
#define	RADTODEG(x)					((x) * ( 180.0f / PI ))
// ������� �����
#define SQR(x)						((x) * (x))
// ����������
#define MAX(a,b)					((a < b) ? (b) : (a))
// ����������
#define MIN(a,b)					((a < b) ? (a) : (b))



// ������� ��� ����������
const float	EPSILON						= 0.0001f;
// ������ � ����, ���� �����
#define ZERO_CLAMP(x)	((EPSILON > fabs(x))?0.0f:(x))
// ��������� float'��
#define FLOAT_EQ(x,v)	( ((v) - EPSILON) < (x) && (x) < ((v) + EPSILON) )		// float equality test
// ��������, ���� ������� �� �������
#define LIMIT_RANGE(low, value, high)	{	if (value < low)	value = low;	else if(value > high)	value = high;	}
// �������, ���� ������� �� �������
#define CUT_RANGE(low, value, high)	{	if (value < low)	value = value - low + high;	else if(value >= high)	value -= high;	}




float __inline ulrsqrt(float &x);
/*
    sqrt(x) = x / sqrt(x)
*/
void MyFtoL(int* i, float &f);//������� �������������� float -> int

int __inline roundf(float &x); 


float __inline ArcTan(float &a); //����������

float __inline ArcCos(float &a); //���������

DWORD HI_LOW(WORD &HI,WORD &LOW); //����������� ������� ����� DWORD �� ���� WORD

int __inline Abs(int &a);

float __inline Abs(float &a);