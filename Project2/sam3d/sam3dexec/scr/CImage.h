#pragma once
#include "../Includes/IImage.h"


namespace Sam3d
{
	class CImage : public IImage
	{
	public:

	//! constructor
		CImage(ECOLOR_FORMAT format, const Dimension2d<int>& size);


	//! constructor
		CImage(ECOLOR_FORMAT format, const Dimension2d<int>& size, void* data);

	//! assumes format and size has been set and creates the rest
		void initData();

	//! destructor
		~CImage();

	//! Lock function.
		virtual void* lock();


	//! Unlock function.
		virtual void unlock();

	//! Returns width and height of image data.
		virtual const Dimension2d<int>& getDimension();



	//! Returns bits per pixel. 
		virtual int getBitsPerPixel();

	//! returns a pixel
		virtual SColor getPixel(int x, int y);


	//! returns the color format
		virtual ECOLOR_FORMAT getColorFormat();


	//! Returns bytes per pixel
		virtual int getBytesPerPixel();



	//! Returns image data size in bytes
		virtual int getImageDataSizeInBytes();



	//! Returns image data size in pixels
		virtual int getImageDataSizeInPixels();


};