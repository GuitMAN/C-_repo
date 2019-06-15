#pragma once


	//! Specifies a 2 dimensional size.
	template <class T>
	class Dimension2d
	{
		public:

			Dimension2d()
				: Width(0), Height(0) {};

			Dimension2d(T width, T height)
				: Width(width), Height(height) {};

			Dimension2d(const Dimension2d<T>& other)
				: Width(other.Width), Height(other.Height) {};


			bool operator == (const Dimension2d<T>& other) const
			{
				return Width == other.Width && Height == other.Height;
			}


			bool operator != (const Dimension2d<T>& other) const
			{
				return Width != other.Width || Height != other.Height;
			}

			const Dimension2d<T>& operator=(const Dimension2d<T>& other) 
			{
				Width = other.Width;
				Height = other.Height;
				return *this;
			}

			T Width, Height;
	};
