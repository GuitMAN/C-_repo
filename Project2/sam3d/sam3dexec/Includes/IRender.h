#pragma once

#include <string>
#include "IBase.h"
//#include "IShaders.h"
//#include "ITexture.h"
//#include "IVertexBuffer.h"
//#include "IVertexDeclaration.h"
#include "../scr/core/Dimension2d.h"
//#include "../scr/core/SLight.h"
#include "../scr/core/Position2d.h"
#include "../scr/core/SColor.h"
//#include "../scr/core/SMaterial.h"
//#include "../scr/core/Matrix4f.h"
#include "../scr/core/S3DVertex.h"


#include <d3d9.h>

namespace Sam3d
{

enum MATRIX
{
	MATRIX_PROJECTION,
	MATRIX_VIEW,
	MATRIX_WORLD
};

/// The rendering operation type to perform
enum OperationType 
{
	/// A list of points, 1 vertex per point
	OT_POINT_LIST = 1,
	/// A list of lines, 2 vertices per line
    OT_LINE_LIST = 2,
	/// A strip of connected lines, 1 vertex per line plus 1 start vertex
    OT_LINE_STRIP = 3,
	/// A list of triangles, 3 vertices per triangle
    OT_TRIANGLE_LIST = 4,
	/// A strip of triangles, 3 vertices for the first triangle, and 1 per triangle after that 
    OT_TRIANGLE_STRIP = 5,
	/// A fan of triangles, 3 vertices for the first triangle, and 1 per triangle after that
    OT_TRIANGLE_FAN = 6
};


struct SRenderOp
{
	OperationType  Type;
//	IVertexBuffer*	pVB;
//	IIndexBuffer*	pIB;
//	IVertexDeclaration* pDcl;
};



class IRender: public IBase
{
public:
	virtual ~IRender(){};

	virtual bool Init()=0;
	virtual void BeginScene(bool backBuffer, bool zBuffer, SColor color)=0;
	virtual void draw2DRectangle(const Position2d<int> &position, const Position2d<int> &clip, const SColor &color)=0;
//	virtual void draw2DImage(const Position2d<int> &position, const Position2d<int> &clip, ITexture* texture, const SColor &color, bool useAlphaChannelOfTexture)=0;
//	virtual void draw2DImage(const Position2d<int> &position, const Position2d<int> &clip, ITexture* texture, const Position2d<int> &soursePos, const Position2d<int> &sourseClip, const SColor &color, bool useAlphaChannelOfTexture)=0;
//	virtual void draw2DImage(const RECT &position, ITexture* texture, const RECT &sourse, const SColor &color, bool useAlphaChannelOfTexture)=0;
	virtual void drawIndexedTriangleList(const S3DVertex* Vertices,	 int vertexCount, const uShort* indexList, int triangleCount)=0;
	virtual void drawIndexedTriangleStrip(S3DVertex *vertices, int vertexCount,  const uShort* indexList,  int indexCount)=0;
	virtual void drawBuffer(SRenderOp Op, int vertexStart, int vertexCount, int indexStart, int primCount)=0;

	virtual void EndScene()=0;

	virtual IRender* getRender()=0;
//	virtual ITexture* LoadTextureFromFile(char* Name)=0;
//	virtual void addTexture(ITexture* texture, std::string Name)=0;
//	virtual void setTexture(int stage, ITexture* texture)=0;
//	virtual void removeTexture(ITexture* texture)=0;
	virtual void removeAllTexture()=0;
//	virtual void setMaterial(const SMaterial& material)=0;
	
//	virtual IVertexBuffer* addVertexBuffer(void* Vertices, uInt numSize, uInt vertexSise, bool dinamic)=0;
//	virtual IIndexBuffer* addIndexBuffer(short* Indices, int numIndices, bool dinamic)=0;
	
//	virtual IVertexDeclaration* addVertexDeclaration()=0;	
//	virtual IVertexDeclaration* getVertexDeclaration(DECL_TYPE mode)=0;

//	virtual IVertexShader* addVertexShader(LPCTSTR pSrcFile)=0;
	
	virtual int getFPS()=0;
	virtual void registerFrame(uInt time)=0;
//	virtual void setTransform(MATRIX matrix_mode, Matrix4f* Mat)=0;
//	virtual void setTextureUnitFiltering(uInt unit, TextureFilterOptions tfo)=0;

	virtual void setLightingEnabled(bool enabled)=0;
	virtual void setAmbientLight(float r, float g, float b)=0;
};

};