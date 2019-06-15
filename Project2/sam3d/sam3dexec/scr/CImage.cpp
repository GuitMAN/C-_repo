#include "CImage.h"


namespace Sam3d
{

	//! constructor
	CImage::CImage(ECOLOR_FORMAT format, const Dimension2d<int>& size)
		: Format(format), Size(size), Data(0)
	{
		initData();
	}


	//! constructor
	CImage::CImage(ECOLOR_FORMAT format, const Dimension2d<int>& size, void* data)
		: Format(format), Size(size), Data(0)
	{
		Data = (void*)0xbadf00d;

		initData();
		Data = data;
	}

	//! assumes format and size has been set and creates the rest
	void CImage::initData()
	{
		switch (Format)
		{
		case ECF_L8:
			BitsPerPixel = 8; break;
		case ECF_A1R5G5B5:
			BitsPerPixel = 16; break;
		case ECF_R5G6B5:
			BitsPerPixel = 16; break;
		case ECF_R8G8B8:
			BitsPerPixel = 24; break;
		case ECF_A8R8G8B8:
			BitsPerPixel = 32; break;
		};
		BytesPerPixel = BitsPerPixel / 8;

		if (!Data)
			Data = new char[Size.Height * Size.Width * BytesPerPixel];
	}

	//! destructor
	CImage::~CImage()
	{
		delete[](char*)Data;
	}

	//! Lock function.
	void* CImage::lock()
	{
		return Data;
	}


	//! Unlock function.
	void CImage::unlock()
	{
	}

	//! Returns width and height of image data.
	const Dimension2d<int>& CImage::getDimension()
	{
		return Size;
	}



	//! Returns bits per pixel. 
	int CImage::getBitsPerPixel()
	{
		return BitsPerPixel;
	}

	//! returns a pixel
	SColor CImage::getPixel(int x, int y)
	{
		if (x < 0 || y < 0 || x >= Size.Width || y >= Size.Height)
			return SColor(0);

		switch (Format)
		{
		case ECF_L8:
			return ((char*)Data)[y * Size.Width + x];
		case ECF_A1R5G5B5:
			return A1R5G5B5toA8R8G8B8(((short*)Data)[y * Size.Width + x]);
		case ECF_R5G6B5:
			return R5G6B5toA8R8G8B8(((short*)Data)[y * Size.Width + x]);
		case ECF_A8R8G8B8:
			return ((int*)Data)[y * Size.Width + x];
		case ECF_R8G8B8:
		{
			char* p = &((char*)Data)[(y * 3) * Size.Width + (x * 3)];
			return SColor(255, p[0], p[1], p[2]);
		}
		}

		return SColor(0);
	}


	//! returns the color format
	ECOLOR_FORMAT CImage::getColorFormat()
	{
		return Format;
	}


	//! Returns bytes per pixel
	int CImage::getBytesPerPixel()
	{
		return BytesPerPixel;
	}



	//! Returns image data size in bytes
	int CImage::getImageDataSizeInBytes()
	{
		return BytesPerPixel * Size.Width * Size.Height;
	}



	//! Returns image data size in pixels
	int CImage::getImageDataSizeInPixels()
	{
		return Size.Width * Size.Height;
	}


}