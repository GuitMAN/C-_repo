#pragma once

#include "IBase.h" 
#include "core/Scolor.h"
#include "../scr/core/Dimension2d.h"

namespace Sam3d
{

enum ECOLOR_FORMAT
{
	ECF_A8 = 0,
	ECF_L8,
	ECF_A1R5G5B5 ,	
	ECF_R5G6B5,
	ECF_R8G8B8,
	ECF_A8R8G8B8,
};

class IImage : public IBase
{
public:
	virtual ~IImage(){};

	//! Указатель на данные
	virtual void* lock()=0;
	//! Закрываем даные
	virtual void unlock()=0;
	//! Returns width and height of image data.
	virtual const Dimension2d<int>& getDimension()=0;
	//! Returns bits per pixel. 
	virtual int getBitsPerPixel()=0;
	//! Returns bytes per pixel
	virtual int getBytesPerPixel()=0;
	//! Returns image data size in bytes
	virtual int getImageDataSizeInBytes()=0;
	//! Returns image data size in pixels
	virtual int getImageDataSizeInPixels()=0;
	//! returns a pixel
	virtual SColor getPixel(int x, int y)=0;
	//! returns the color format
	virtual ECOLOR_FORMAT getColorFormat()=0;
	//! resizes the surface to a new size
	virtual void resizeTo(const Dimension2d<int>& size)=0;
	//! fills the surface with black or white
	virtual void fill(short color)=0;
};

};