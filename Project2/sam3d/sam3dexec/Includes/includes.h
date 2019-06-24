#pragma once
/*
	Движок Sam3D. Дементьев Владимир 2008 
*/

#include "IBase.h"
//#include "ICameraSceneNode.h"
#include "ICursor.h"
//#include "IFont.h"
//#include "IImage.h"
//#include "IImageLoader.h"
//#include "Input.h"
//#include "ITexture.h"
#include "Types.h"
#include "IRender.h"
//#include "ISceneManager.h"
//#include "ISceneNode.h"
#include "IMesh.h"
//#include "ITerrainSceneNode.h"
//#include "ITexture.h"
//#include "ITimer.h"
//#include "IVertexBuffer.h"
#include "IWindow.h"
#include "../scr/core/Dimension2d.h"
//#include "core/Matrix4f.h"
//#include "core/Plane3d.h"
//#include "core/Quaternionf.h"
#include "../scr/core/S3DVertex.h"
//#include "../scr/core/SLight.h"
//#include "core/SMaterial.h"
#include "../scr/core/UserMath.h"
#include "../scr/core/Vector3f.h"

namespace Sam3d
{



	IWindow* createWindow(const String& caption, Dimension2d<int> windowSize, int bits, bool fullScreen, bool vsync);

/*
#define DLL_API __declspec(dllexport)
#define DLLCALLCONV __stdcall  // Declare the calling convention.

#ifdef __cplusplus
extern "C" {     // do not use C++ decorations
#endif

	DLL_API IWindow* DLLCALLCONV createWindow(const String& caption, Dimension2d<int> windowSize,  int bits, bool fullScreen, bool vsync);  

//	DLL_API ISceneManager* DLLCALLCONV  CreateSceneManager(IRender *render, ITimer* timer);

#ifdef __cplusplus
}; // close extern C
#endif
*/

};