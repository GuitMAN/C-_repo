#include "usermath.h"
#include <math.h>

////////////////////////////////////////////////////////////
//USERMATH - Прочая математика для быстрых вычислений
////////////////////////////////////////////////////////////
namespace Sam3d
{

	static float _0_47 = 0.47f;
	static float _1_47 = 1.47f;
	static float _2 = 2.f;








	float __inline ulrsqrt(float x)
	{

		
		float r;

#ifdef _WIN64
		
		r = sqrtf(x);

#else
		DWORD y;
		_asm
		{
			mov     eax, 07F000000h + 03F800000h // (ONE_AS_INTEGER<<1) + ONE_AS_INTEGER
			sub     eax, x
			sar     eax, 1

			mov     y, eax           // y
			fld     _0_47            // 0.47
			fmul    DWORD PTR x      // x*0.47

			fld     DWORD PTR y
			fld     st(0)            // y y x*0.47
			fmul    st(0), st(1)     // y*y y x*0.47

			fld     _1_47            // 1.47 y*y y x*0.47
			fxch    st(3)            // x*0.47 y*y y 1.47
			fmulp   st(1), st(0)     // x*0.47*y*y y 1.47
			fsubp   st(2), st(0)     // y 1.47-x*0.47*y*y
			fmulp   st(1), st(0)      // result
			fstp    y
			and y, 07FFFFFFFh

		}
		r = *(float*)& y;
		// optional
		r = (3.0f - x * (r * r)) * r * 0.5f; // remove for low accuracy
		
#endif
		return r;
	}



	void __inline MyFtoL(int* i, float& f)
	{

#ifdef _WIN64

		int a = (int)f;

		i = &a;

#else

		_asm
		{
			fld f;
			mov edx, i;
			fistp[edx];

		}
	

#endif
	
	}
	__inline const int roundf(const float& x)
	{
		

#ifdef _WIN64
		int n = round(x);

#else
		_asm
		{
			fld     x;
			fistp   n;
		}
#endif
		return n;
	}

	//Арктангенс
	float __inline ArcTan(float& a)
	{

#ifdef _WIN64

		a = atanf(a);
		
#else
		__asm fld1
		__asm fld a
		__asm fpatan
		__asm fstp a;
#endif
		return a;
	}


	//Аркосинус 
	float __inline ArcCos(float& a)
	{
#ifdef _WIN64

		a = acosf(a);

#else
		__asm fld1
		__asm fsub a
		__asm fsqrt
		__asm fld1
		__asm fadd a
		__asm fsqrt
		__asm fpatan
		__asm fld  _2
		__asm fmul
		__asm fstp a;
#endif
		return a;
	}

	DWORD __inline HI_LOW(WORD& HI, WORD& LOW)
	{
#ifdef _WIN64

		DWORD t1, t2;
		t1 = HI;
		t2 = LOW;
		t1 << 16;
		t1  =+ t2;

#else
		DWORD t1, t2;
		t1 = HI;
		t2 = LOW;


		_asm
		{
			mov eax, t1
			shl eax, 10h
			add eax, t2
			mov t1, eax
		}

#endif
		return t1;
	};


	int __inline Abs(int& a)
	{
		if (a < 0) a = -a;
		return a;
	};

	float __inline Abs(float& a)
	{
		if (a < 0) a = -a;
		return a;
	};

	

	
}