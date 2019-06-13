#pragma once
#include <string>

namespace Sam3d
{

//! 8 bit unsigned variable.
typedef unsigned char		uChar; 
typedef signed char			sChar; 

//! 16 bit unsigned variable.
typedef unsigned short		uShort;
typedef signed short		sShort; 

//! 32 bit unsigned variable.
typedef  signed int sInt; 
typedef  unsigned int uInt; 


typedef  std::string String;


#ifdef SAM3D_DEBUG_MODE 
//Макрос создания нового элемента
//#define SAM3D_NEW new (__FILE__, __LINE__, __FUNCTION__)
//#define SAM3D_DELETE delete




#else
//#define SAM3D_NEW new 
//#define SAM3D_DELETE delete

#endif


#define DLL_API __declspec(dllexport)
#define DLLCALLCONV __stdcall  // Declare the calling convention.



};