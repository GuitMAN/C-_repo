#pragma once
#include <windows.h>
#include <GL/GL.h>
#include    <GL/glu.h>

#include "../scr/glext/glext.h"
//#include "../scr/glext/glxext.h"

#ifdef  _WIN32
#include "../scr/glext/wglext.h"
#else
#include    <GL/glx.h>
#include    <GL/glxext.h>
#endif

#include "../Includes/IRender.h"
//#include "core/S3DVertex.h"

namespace Sam3d
{


	class COpenGLRender : public IRender
	{
	public:
		COpenGLRender(HWND hwnd, Dimension2d<int> screenSize, bool fullScreen, bool vsync);
		virtual ~COpenGLRender();

		bool Init();
		void BeginScene(bool backBuffer, bool zBuffer, SColor color) {};
		void draw2DRectangle(const Position2d<int>& position, const Position2d<int>& clip, const SColor& color) {};
		//	virtual void draw2DImage(const Position2d<int> &position, const Position2d<int> &clip, ITexture* texture, const SColor &color, bool useAlphaChannelOfTexture)=0;
		//	virtual void draw2DImage(const Position2d<int> &position, const Position2d<int> &clip, ITexture* texture, const Position2d<int> &soursePos, const Position2d<int> &sourseClip, const SColor &color, bool useAlphaChannelOfTexture)=0;
		//	virtual void draw2DImage(const RECT &position, ITexture* texture, const RECT &sourse, const SColor &color, bool useAlphaChannelOfTexture)=0;
		void drawIndexedTriangleList(const S3DVertex* Vertices, int vertexCount, const uShort* indexList, int triangleCount) {};
		void drawIndexedTriangleStrip(S3DVertex* vertices, int vertexCount, const uShort* indexList, int indexCount) {};
		void drawBuffer(SRenderOp Op, int vertexStart, int vertexCount, int indexStart, int primCount) {};

		void EndScene() {};

		IRender* getRender() { return  NULL; };
		//	virtual ITexture* LoadTextureFromFile(char* Name)=0;
		//	virtual void addTexture(ITexture* texture, std::string Name)=0;
		//	virtual void setTexture(int stage, ITexture* texture)=0;
		//	virtual void removeTexture(ITexture* texture)=0;
		void removeAllTexture() {};
		//	virtual void setMaterial(const SMaterial& material)=0;

		//	virtual IVertexBuffer* addVertexBuffer(void* Vertices, uInt numSize, uInt vertexSise, bool dinamic)=0;
		//	virtual IIndexBuffer* addIndexBuffer(short* Indices, int numIndices, bool dinamic)=0;

		//	virtual IVertexDeclaration* addVertexDeclaration()=0;	
		//	virtual IVertexDeclaration* getVertexDeclaration(DECL_TYPE mode)=0;

		//	virtual IVertexShader* addVertexShader(LPCTSTR pSrcFile)=0;

		int getFPS() { return 0; };
		void registerFrame(uInt time) {};
		//	virtual void setTransform(MATRIX matrix_mode, Matrix4f* Mat)=0;
		//	virtual void setTextureUnitFiltering(uInt unit, TextureFilterOptions tfo)=0;

		void setLightingEnabled(bool enabled) {};
		void setAmbientLight(float r, float g, float b) {};

	protected:
		HWND hWnd;
		HGLRC  hRC = NULL;
		Dimension2d<int> ScreenSize;
		bool FullScreen;
		bool Vsync;




	};

};