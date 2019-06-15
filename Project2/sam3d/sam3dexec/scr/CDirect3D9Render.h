#pragma once
#include <d3d9.h>
#include <d3dx9tex.h>
#include <vector>
#include "CFPSCounter.h"
#include "CImageLoaderTGA.h"
#include "CDirect3D9Shader.h"
#include "CDirect3D9MaterialRender.h"
#include "CDirect3D9VertexBuffer.h"
#include "CDirect3D9VertexDeclaration.h"
#include "../Includes/IRender.h"
#include "core/matrix4f.h"
#include "log.h"

#define	FVF_VERTEX_TEX2 (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define	FVF_VERTEX_TEX1 (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

namespace Sam3d
{

class CDirect3D9Render:public IRender
{
public:
	CDirect3D9Render(HWND hwnd, Dimension2d<int> screenSize, bool fullScreen, bool vsync);
	virtual ~CDirect3D9Render();

	virtual bool Init();

	virtual void BeginScene(bool backBuffer, bool zBuffer, SColor color);
	virtual void draw2DRectangle(const Position2d<int> &position, const Position2d<int> &clip, const SColor &color);
	virtual void draw2DImage(const Position2d<int> &position, const Position2d<int> &clip, ITexture* texture, const SColor &color, bool useAlphaChannelOfTexture);
	virtual void draw2DImage(const Position2d<int> &position, const Position2d<int> &clip, ITexture* texture, const Position2d<int> &soursePos, const Position2d<int> &sourseClip, const SColor &color, bool useAlphaChannelOfTexture);
	virtual void draw2DImage(const RECT &position, ITexture* texture, const RECT &sourse, const SColor &color, bool useAlphaChannelOfTexture);
	virtual void drawIndexedTriangleList(const S3DVertex* Vertices,	 int vertexCount, const uShort* indexList, int triangleCount);
	virtual void drawIndexedTriangleStrip(S3DVertex *vertices, int vertexCount,  const uShort* indexList,  int indexCount);
	virtual void drawBuffer(SRenderOp Op, int vertexStart, int vertexCount, int indexStart, int primCount);
	virtual void EndScene();

	virtual IRender* getRender();
	virtual ITexture* LoadTextureFromFile(char* Name);
	virtual void addTexture(ITexture* texture, std::string Name);
	virtual void setTexture(int stage, ITexture* texture);
	virtual void removeTexture(ITexture* texture);
	virtual void removeAllTexture();
	virtual void setMaterial(const SMaterial& material);
	
	virtual IVertexBuffer* addVertexBuffer(void* Vertices, uInt numSize, uInt vertexSise, bool dinamic);
	virtual IIndexBuffer* addIndexBuffer(short* Indices, int numIndices, bool dinamic);
	virtual IVertexDeclaration* addVertexDeclaration();
	
	virtual IVertexShader* addVertexShader(LPCTSTR pSrcFile);

	virtual int getFPS();
	virtual void registerFrame(uInt time);
	virtual void setRenderStates2DMode(bool alpha, bool texture, bool alphaChannel);
	virtual void setTransform(MATRIX matrix_mode, Matrix4f* Mat);

	virtual void setTextureUnitFiltering(uInt unit, TextureFilterOptions tfo);

	virtual void setLightingEnabled(bool enabled);
	virtual void setAmbientLight(float r, float g, float b);
	

protected:
	ITexture* findTexture(std::string Name);
	void removeBuffers();
	
	struct SSurface
	{
		std::string Filename;
		ITexture* Surface;

		bool operator < (const SSurface& other) const
		{
			return (Filename < other.Filename);
		}
	};
	
	inline D3DCOLORVALUE colorToD3D(const SColor& col)
	{
		const float f = 1.0f / 255.0f;
		D3DCOLORVALUE v;
		v.r = col.getRed() * f;
		v.g = col.getGreen() * f;
		v.b = col.getBlue() * f;
		v.a = col.getAlpha() * f;
		return v;
	};



	
	std::vector<SSurface> Textures;
	std::vector<SMaterial> Materials;
	SMaterial CurMaterial, LastMaterial;
	CDirect3D9MaterialRender* RenderMaterial;
	bool resetAllmaterial;

	std::vector<IVertexBuffer*> VertexesBuffer;
	std::vector<IIndexBuffer*> IndexesBuffer;
	std::vector<IVertexDeclaration*> VertexDeclaration;
	std::vector<IVertexShader*> VertexShader;

	Matrix4f	MatProjectoin;
	Matrix4f	MatView;
	Matrix4f	MatWorld;

	HWND hWnd; 
	Dimension2d<int> ScreenSize;
	bool FullScreen;
	bool Vsync;
    
	CFPSCounter		Fps;

	HINSTANCE D3DLibrary;
	LPDIRECT3D9				pD;
	LPDIRECT3DDEVICE9		pDD;
	D3DCAPS9 mCaps;
	
};

};