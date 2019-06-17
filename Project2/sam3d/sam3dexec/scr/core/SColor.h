#pragma once

#include "UserMath.h"
#include "../../Includes/Types.h"



namespace Sam3d
{

	//! An enum for the color format of textures used by the Irrlicht Engine.
		/** A color format specifies how color information is stored.
			NOTE: Byte order in memory is usually flipped (it's probably correct in bitmap files, but flipped on reading).
			So for example ECF_A8R8G8B8 is BGRA in memory same as in DX9's D3DFMT_A8R8G8B8 format.
		*/
	enum ECOLOR_FORMAT
	{
		//! 16 bit color format used by the software driver.
		/** It is thus preferred by all other irrlicht engine video drivers.
		There are 5 bits for every color component, and a single bit is left
		for alpha information. */
		ECF_A1R5G5B5 = 0,

		//! Standard 16 bit color format.
		ECF_R5G6B5,

		//! 24 bit color, no alpha channel, but 8 bit for red, green and blue.
		ECF_R8G8B8,

		//! Default 32 bit color format. 8 bits are used for every component: red, green, blue and alpha.
		//! Warning: This tends to be BGRA in memory (it's ARGB on file, but with usual big-endian memory it's flipped)
		ECF_A8R8G8B8,

		/** Compressed image formats. **/

		//! DXT1 color format.
		ECF_DXT1,

		//! DXT2 color format.
		ECF_DXT2,

		//! DXT3 color format.
		ECF_DXT3,

		//! DXT4 color format.
		ECF_DXT4,

		//! DXT5 color format.
		ECF_DXT5,

		//! PVRTC RGB 2bpp.
		ECF_PVRTC_RGB2,

		//! PVRTC ARGB 2bpp.
		ECF_PVRTC_ARGB2,

		//! PVRTC RGB 4bpp.
		ECF_PVRTC_RGB4,

		//! PVRTC ARGB 4bpp.
		ECF_PVRTC_ARGB4,

		//! PVRTC2 ARGB 2bpp.
		ECF_PVRTC2_ARGB2,

		//! PVRTC2 ARGB 4bpp.
		ECF_PVRTC2_ARGB4,

		//! ETC1 RGB.
		ECF_ETC1,

		//! ETC2 RGB.
		ECF_ETC2_RGB,

		//! ETC2 ARGB.
		ECF_ETC2_ARGB,

		/** The following formats may only be used for render target textures. */

		/** Floating point formats. */

		//! 16 bit format using 16 bits for the red channel.
		ECF_R16F,

		//! 32 bit format using 16 bits for the red and green channels.
		ECF_G16R16F,

		//! 64 bit format using 16 bits for the red, green, blue and alpha channels.
		ECF_A16B16G16R16F,

		//! 32 bit format using 32 bits for the red channel.
		ECF_R32F,

		//! 64 bit format using 32 bits for the red and green channels.
		ECF_G32R32F,

		//! 128 bit format using 32 bits for the red, green, blue and alpha channels.
		ECF_A32B32G32R32F,

		/** Unsigned normalized integer formats. */

		//! 8 bit format using 8 bits for the red channel.
		ECF_R8,

		//! 16 bit format using 8 bits for the red and green channels.
		ECF_R8G8,

		//! 16 bit format using 16 bits for the red channel.
		ECF_R16,

		//! 32 bit format using 16 bits for the red and green channels.
		ECF_R16G16,

		/** Depth and stencil formats. */

		//! 16 bit format using 16 bits for depth.
		ECF_D16,

		//! 32 bit format using 32 bits for depth.
		ECF_D32,

		//! 32 bit format using 24 bits for depth and 8 bits for stencil.
		ECF_D24S8,

		//! Unknown color format:
		ECF_UNKNOWN
	};

	//! Names for ECOLOR_FORMAT types
	const char* const ColorFormatNames[ECF_UNKNOWN + 2] =
	{
		"A1R5G5B5",
		"R5G6B5",
		"R8G8B8",
		"A8R8G8B8",
		"DXT1",
		"DXT2",
		"DXT3",
		"DXT4",
		"DXT5",
		"PVRTC_RGB2",
		"PVRTC_ARGB2",
		"PVRTC_RGB4",
		"PVRTC_ARGB4",
		"PVRTC2_ARGB2",
		"PVRTC2_ARGB4",
		"ETC1",
		"ETC2_RGB",
		"ETC2_ARGB",
		"R16F",
		"G16R16F",
		"A16B16G16R16F",
		"R32F",
		"G32R32F",
		"A32B32G32R32F",
		"R8",
		"R8G8",
		"R16",
		"R16G16",
		"D16",
		"D32",
		"D24S8",
		"UNKNOWN",
		0
	};


	//! Creates a 16 bit A1R5G5B5 color
	inline short RGBA16(uInt r, uInt g, uInt b, uInt a = 0xFF)
	{
		return (uShort)((a & 0x80) << 8 |
			(r & 0xF8) << 7 |
			(g & 0xF8) << 2 |
			(b & 0xF8) >> 3);
	}


	//! Creates a 16 bit A1R5G5B5 color
	inline uShort RGB16(uInt r, uInt g, uInt b)
	{
		return RGBA16(r, g, b);
	}


	//! Creates a 16bit A1R5G5B5 color, based on 16bit input values
	inline uShort RGB16from16(uShort r, uShort g, uShort b)
	{
		return (0x8000 |
			(r & 0x1F) << 10 |
			(g & 0x1F) << 5 |
			(b & 0x1F));
	}


	//! Converts a 32bit (X8R8G8B8) color to a 16bit A1R5G5B5 color
	inline uShort X8R8G8B8toA1R5G5B5(uInt color)
	{
		return (uShort)(0x8000 |
			(color & 0x00F80000) >> 9 |
			(color & 0x0000F800) >> 6 |
			(color & 0x000000F8) >> 3);
	}


	//! Converts a 32bit (A8R8G8B8) color to a 16bit A1R5G5B5 color
	inline uShort A8R8G8B8toA1R5G5B5(uInt color)
	{
		return (uShort)((color & 0x80000000) >> 16 |
			(color & 0x00F80000) >> 9 |
			(color & 0x0000F800) >> 6 |
			(color & 0x000000F8) >> 3);
	}


	//! Converts a 32bit (A8R8G8B8) color to a 16bit R5G6B5 color
	inline uShort A8R8G8B8toR5G6B5(uInt color)
	{
		return (uShort)((color & 0x00F80000) >> 8 |
			(color & 0x0000FC00) >> 5 |
			(color & 0x000000F8) >> 3);
	}


	//! Convert A8R8G8B8 Color from A1R5G5B5 color
	/** build a nicer 32bit Color by extending dest lower bits with source high bits. */
	inline uInt A1R5G5B5toA8R8G8B8(uShort color)
	{
		return (((-((sInt)color & 0x00008000) >> (sInt)31) & 0xFF000000) |
			((color & 0x00007C00) << 9) | ((color & 0x00007000) << 4) |
			((color & 0x000003E0) << 6) | ((color & 0x00000380) << 1) |
			((color & 0x0000001F) << 3) | ((color & 0x0000001C) >> 2)
			);
	}


	//! Returns A8R8G8B8 Color from R5G6B5 color
	inline uInt R5G6B5toA8R8G8B8(uShort color)
	{
		return 0xFF000000 |
			((color & 0xF800) << 8) |
			((color & 0x07E0) << 5) |
			((color & 0x001F) << 3);
	}


	//! Returns A1R5G5B5 Color from R5G6B5 color
	inline uShort R5G6B5toA1R5G5B5(uShort color)
	{
		return 0x8000 | (((color & 0xFFC0) >> 1) | (color & 0x1F));
	}


	//! Returns R5G6B5 Color from A1R5G5B5 color
	inline uShort A1R5G5B5toR5G6B5(uShort color)
	{
		return (((color & 0x7FE0) << 1) | (color & 0x1F));
	}



	//! Returns the alpha component from A1R5G5B5 color
	/** In Irrlicht, alpha refers to opacity.
	\return The alpha value of the color. 0 is transparent, 1 is opaque. */
	inline uInt getAlpha(uShort color)
	{
		return ((color >> 15) & 0x1);
	}


	//! Returns the red component from A1R5G5B5 color.
	/** Shift left by 3 to get 8 bit value. */
	inline uInt getRed(uShort color)
	{
		return ((color >> 10) & 0x1F);
	}


	//! Returns the green component from A1R5G5B5 color
	/** Shift left by 3 to get 8 bit value. */
	inline uInt getGreen(uShort color)
	{
		return ((color >> 5) & 0x1F);
	}


	//! Returns the blue component from A1R5G5B5 color
	/** Shift left by 3 to get 8 bit value. */
	inline uInt getBlue(uShort color)
	{
		return (color & 0x1F);
	}


	//! Returns the average from a 16 bit A1R5G5B5 color
	inline sInt getAverage(sShort color)
	{
		return ((getRed(color) << 3) + (getGreen(color) << 3) + (getBlue(color) << 3)) / 3;
	}


	//! Class representing a 32 bit ARGB color.
	/** The color values for alpha, red, green, and blue are
	stored in a single int. So all four values may be between 0 and 255.
	Alpha in Irrlicht is opacity, so 0 is fully transparent, 255 is fully opaque (solid).
	This class is used by most parts of the Irrlicht Engine
	to specify a color. Another way is using the class SColorf, which
	stores the color values in 4 floats.
	This class must consist of only one int and must not use virtual functions.
	*/
	class SColor
	{
	public:

		//! Constructor of the Color. Does nothing.
		/** The color value is not initialized to save time. */
		SColor() {}

		//! Constructs the color from 4 values representing the alpha, red, green and blue component.
		/** Must be values between 0 and 255. */
		SColor(uInt a, uInt r, uInt g, uInt b): color(((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff)) {}

		//! Constructs the color from a 32 bit value. Could be another color.
		SColor(uInt clr)
			: color(clr) {}

		//! Returns the alpha component of the color.
		/** The alpha component defines how opaque a color is.
		\return The alpha value of the color. 0 is fully transparent, 255 is fully opaque. */
		uInt getAlpha() const { return color >> 24; }

		//! Returns the red component of the color.
		/** \return Value between 0 and 255, specifying how red the color is.
		0 means no red, 255 means full red. */
		uInt getRed() const { return (color >> 16) & 0xff; }

		//! Returns the green component of the color.
		/** \return Value between 0 and 255, specifying how green the color is.
		0 means no green, 255 means full green. */
		uInt getGreen() const { return (color >> 8) & 0xff; }

		//! Returns the blue component of the color.
		/** \return Value between 0 and 255, specifying how blue the color is.
		0 means no blue, 255 means full blue. */
		uInt getBlue() const { return color & 0xff; }

		

		//! Get luminance of the color in the range [0,255].
		float getLuminance() const
		{
			return 0.3f * getRed() + 0.59f * getGreen() + 0.11f * getBlue();
		}

		//! Get average intensity of the color in the range [0,255].
		uInt getAverage() const
		{
			return (getRed() + getGreen() + getBlue()) / 3;
		}

		//! Sets the alpha component of the Color.
		/** The alpha component defines how transparent a color should be.
		\param a The alpha value of the color. 0 is fully transparent, 255 is fully opaque. */
		void setAlpha(uInt a) { color = ((a & 0xff) << 24) | (color & 0x00ffffff); }

		//! Sets the red component of the Color.
		/** \param r: Has to be a value between 0 and 255.
		0 means no red, 255 means full red. */
		void setRed(uInt r) { color = ((r & 0xff) << 16) | (color & 0xff00ffff); }

		//! Sets the green component of the Color.
		/** \param g: Has to be a value between 0 and 255.
		0 means no green, 255 means full green. */
		void setGreen(uInt g) { color = ((g & 0xff) << 8) | (color & 0xffff00ff); }

		//! Sets the blue component of the Color.
		/** \param b: Has to be a value between 0 and 255.
		0 means no blue, 255 means full blue. */
		void setBlue(uInt b) { color = (b & 0xff) | (color & 0xffffff00); }

		//! Calculates a 16 bit A1R5G5B5 value of this color.
		/** \return 16 bit A1R5G5B5 value of this color. */
		uShort toA1R5G5B5() const { return A8R8G8B8toA1R5G5B5(color); }

		//! Converts color to OpenGL color format
		/** From ARGB to RGBA in 4 byte components for endian aware
		passing to OpenGL
		\param dest: address where the 4x8 bit OpenGL color is stored. */
		void toOpenGLColor(uChar* dest) const
		{
			*dest = (uChar)getRed();
			*++dest = (uChar)getGreen();
			*++dest = (uChar)getBlue();
			*++dest = (uChar)getAlpha();
		}

		//! Sets all four components of the color at once.
		/** Constructs the color from 4 values representing the alpha,
		red, green and blue components of the color. Must be values
		between 0 and 255.
		\param a: Alpha component of the color. The alpha component
		defines how transparent a color should be. Has to be a value
		between 0 and 255. 255 means not transparent (opaque), 0 means
		fully transparent.
		\param r: Sets the red component of the Color. Has to be a
		value between 0 and 255. 0 means no red, 255 means full red.
		\param g: Sets the green component of the Color. Has to be a
		value between 0 and 255. 0 means no green, 255 means full
		green.
		\param b: Sets the blue component of the Color. Has to be a
		value between 0 and 255. 0 means no blue, 255 means full blue. */
		void set(uInt a, uInt r, uInt g, uInt b)
		{
			color = (((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff));
		}
		void set(uInt col) { color = col; }

		//! Compares the color to another color.
		/** \return True if the colors are the same, and false if not. */
		bool operator==(const SColor& other) const { return other.color == color; }

		//! Compares the color to another color.
		/** \return True if the colors are different, and false if they are the same. */
		bool operator!=(const SColor& other) const { return other.color != color; }

		//! comparison operator
		/** \return True if this color is smaller than the other one */
		bool operator<(const SColor& other) const { return (color < other.color); }

		//! Adds two colors, result is clamped to 0..255 values
		/** \param other Color to add to this color
		\return Addition of the two colors, clamped to 0..255 values */
		SColor operator+(const SColor& other) const
		{
			return SColor(min_(getAlpha() + other.getAlpha(), 255u),
				min_(getRed() + other.getRed(), 255u),
				min_(getGreen() + other.getGreen(), 255u),
				min_(getBlue() + other.getBlue(), 255u));

		}

		

		

		//! set the color by expecting data in the given format
		/** \param data: must point to valid memory containing color information in the given format
			\param format: tells the format in which data is available
		*/
		void setData(const void* data, ECOLOR_FORMAT format)
		{
			switch (format)
			{
			case ECF_A1R5G5B5:
				color = A1R5G5B5toA8R8G8B8(*(uShort*)data);
				break;
			case ECF_R5G6B5:
				color = R5G6B5toA8R8G8B8(*(uShort*)data);
				break;
			case ECF_A8R8G8B8:
				color = *(uInt*)data;
				break;
			case ECF_R8G8B8:
			{
				uChar* p = (uChar*)data;
				set(255, p[0], p[1], p[2]);
			}
			break;
			default:
				color = 0xffffffff;
				break;
			}
		}

		//! Write the color to data in the defined format
		/** \param data: target to write the color. Must contain sufficiently large memory to receive the number of bytes neede for format
			\param format: tells the format used to write the color into data
		*/
		void getData(void* data, ECOLOR_FORMAT format) const
		{
			switch (format)
			{
			case ECF_A1R5G5B5:
			{
				uShort* dest = (uShort*)data;
				*dest = A8R8G8B8toA1R5G5B5(color);
			}
			break;

			case ECF_R5G6B5:
			{
				uShort* dest = (uShort*)data;
				*dest = A8R8G8B8toR5G6B5(color);
			}
			break;

			case ECF_R8G8B8:
			{
				uChar* dest = (uChar*)data;
				dest[0] = (uChar)getRed();
				dest[1] = (uChar)getGreen();
				dest[2] = (uChar)getBlue();
			}
			break;

			case ECF_A8R8G8B8:
			{
				uInt* dest = (uInt*)data;
				*dest = color;
			}
			break;

			default:
				break;
			}
		}

		//! color in A8R8G8B8 Format
		uInt color = 0;
	};


	//! Class representing a color with four floats.
	/** The color values for red, green, blue
	and alpha are each stored in a 32 bit floating point variable.
	So all four values may be between 0.0f and 1.0f.
	Another, faster way to define colors is using the class SColor, which
	stores the color values in a single 32 bit integer.
	*/
	class SColorf
	{
	public:
		//! Default constructor for SColorf.
		/** Sets red, green and blue to 0.0f and alpha to 1.0f. */
		SColorf() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}

		//! Constructs a color from up to four color values: red, green, blue, and alpha.
		/** \param r: Red color component. Should be a value between
		0.0f meaning no red and 1.0f, meaning full red.
		\param g: Green color component. Should be a value between 0.0f
		meaning no green and 1.0f, meaning full green.
		\param b: Blue color component. Should be a value between 0.0f
		meaning no blue and 1.0f, meaning full blue.
		\param a: Alpha color component of the color. The alpha
		component defines how transparent a color should be. Has to be
		a value between 0.0f and 1.0f, 1.0f means not transparent
		(opaque), 0.0f means fully transparent. */
		SColorf(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a) {}

		//! Constructs a color from 32 bit Color.
		/** \param c: 32 bit color from which this SColorf class is
		constructed from. */
		SColorf(SColor c)
		{
			const float inv = 1.0f / 255.0f;
			r = c.getRed() * inv;
			g = c.getGreen() * inv;
			b = c.getBlue() * inv;
			a = c.getAlpha() * inv;
		}

		//! Converts this color to a SColor without floats.
		SColor toSColor() const
		{
			return SColor((uInt)roundf(a * 255.0f), (uInt)roundf(r * 255.0f), (uInt)roundf(g * 255.0f), (uInt)roundf(b * 255.0f));
		}

		//! Sets three color components to new values at once.
		/** \param rr: Red color component. Should be a value between 0.0f meaning
		no red (=black) and 1.0f, meaning full red.
		\param gg: Green color component. Should be a value between 0.0f meaning
		no green (=black) and 1.0f, meaning full green.
		\param bb: Blue color component. Should be a value between 0.0f meaning
		no blue (=black) and 1.0f, meaning full blue. */
		void set(float rr, float gg, float bb) { r = rr; g = gg; b = bb; }

		//! Sets all four color components to new values at once.
		/** \param aa: Alpha component. Should be a value between 0.0f meaning
		fully transparent and 1.0f, meaning opaque.
		\param rr: Red color component. Should be a value between 0.0f meaning
		no red and 1.0f, meaning full red.
		\param gg: Green color component. Should be a value between 0.0f meaning
		no green and 1.0f, meaning full green.
		\param bb: Blue color component. Should be a value between 0.0f meaning
		no blue and 1.0f, meaning full blue. */
		void set(float aa, float rr, float gg, float bb) { a = aa; r = rr; g = gg; b = bb; }

	

		//! Sets a color component by index. R=0, G=1, B=2, A=3
		void setColorComponentValue(sInt index, float value)
		{
			switch (index)
			{
			case 0: r = value; break;
			case 1: g = value; break;
			case 2: b = value; break;
			case 3: a = value; break;
			}
		}

		//! Returns the alpha component of the color in the range 0.0 (transparent) to 1.0 (opaque)
		float getAlpha() const { return a; }

		//! Returns the red component of the color in the range 0.0 to 1.0
		float getRed() const { return r; }

		//! Returns the green component of the color in the range 0.0 to 1.0
		float getGreen() const { return g; }

		//! Returns the blue component of the color in the range 0.0 to 1.0
		float getBlue() const { return b; }

		//! red color component
		float r;

		//! green color component
		float g;

		//! blue component
		float b;

		//! alpha color component
		float a;
	};


	
}