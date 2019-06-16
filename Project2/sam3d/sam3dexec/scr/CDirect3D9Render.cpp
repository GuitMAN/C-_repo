#include "CDirect3D9Render.h"
//#include "CDirectX9Texture.h"

/*
namespace Sam3d
{

CDirect3D9Render::CDirect3D9Render(HWND hwnd, Dimension2d<int> screenSize, bool fullScreen, bool vsync):
pD(0),pDD(0),hWnd(hwnd),ScreenSize(screenSize),FullScreen(fullScreen),Vsync(vsync)
{
		pD	= NULL;
		pDD	= NULL;
};
bool CDirect3D9Render::Init()
{   
	//HRESULT hr;
	D3DLibrary = LoadLibrary( "d3d9.dll" );
	
	if (!pD)
	{
		if (!D3DLibrary)
		{
			return false;
		}

		typedef IDirect3D9 * (__stdcall *D3DCREATETYPE)(UINT);
		D3DCREATETYPE Direct3DCreate9 = (D3DCREATETYPE) GetProcAddress(D3DLibrary, "Direct3DCreate9");

		if( NULL == (pD = Direct3DCreate9(D3D_SDK_VERSION)))
			return 0;

		D3DDISPLAYMODE Display;
		if( FAILED( pD->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &Display ) ) )
			return 0;

		D3DPRESENT_PARAMETERS Direct3DParametr; 
		ZeroMemory( &Direct3DParametr, sizeof(Direct3DParametr) );

		Direct3DParametr.Windowed		= FullScreen ? FALSE : TRUE;
		Direct3DParametr.EnableAutoDepthStencil	= TRUE;
		Direct3DParametr.AutoDepthStencilFormat = D3DFMT_D24S8;
		Direct3DParametr.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;
		Direct3DParametr.BackBufferFormat = D3DFMT_A8R8G8B8;//Display.Format;
		Direct3DParametr.BackBufferCount = 3;
		Direct3DParametr.SwapEffect = D3DSWAPEFFECT_DISCARD;	
		Direct3DParametr.MultiSampleType = D3DMULTISAMPLE_NONE;
		Direct3DParametr.MultiSampleQuality = 0;
		if (FullScreen)
		{
			Direct3DParametr.BackBufferWidth = ScreenSize.Width;
			Direct3DParametr.BackBufferHeight = ScreenSize.Height;
			Direct3DParametr.BackBufferFormat = D3DFMT_A8R8G8B8;
			Direct3DParametr.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;

			if (Vsync)
				Direct3DParametr.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
		}
    
		if( FAILED(pD -> CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                      &Direct3DParametr, &pDD)))
		{
			return 0;
		}
	}
//	RenderMaterial = new CDirect3D9MaterialRender(pDD);
	resetAllmaterial = true;

	return true;
}

IVertexDeclaration* CDirect3D9Render::addVertexDeclaration()
{
	IVertexDeclaration* f;
	f = new CDirect3D9VertexDeclaration(pDD);
	VertexDeclaration.push_back(f);
	return f;
};

void CDirect3D9Render::BeginScene(bool backBuffer, bool zBuffer, SColor color)
{
	DWORD flags = 0;

	if (backBuffer)
		flags |= D3DCLEAR_TARGET;

	if (zBuffer)
		flags |= D3DCLEAR_ZBUFFER;

//	if (StencilBuffer)
//		flags |= D3DCLEAR_STENCIL;

	pDD->Clear( 0, 0, flags, color.color, 1.0f, 0L );
    // Ќачало сцены
	pDD->BeginScene(); 
}

void CDirect3D9Render::EndScene()
{
    // «десь происходит прорисовка сцены
	pDD->EndScene();       
    // онец сцены
    pDD->Present( NULL, NULL, NULL, NULL );
};

CDirect3D9Render::~CDirect3D9Render()
{
	removeAllTexture();
	removeBuffers();

	if( pDD != NULL) 
        pDD->Release();

    if( pD != NULL)
        pD->Release();
};

IRender* CDirect3D9Render::getRender()
{
	return this;
}

void CDirect3D9Render::draw2DRectangle(const Position2d<int> &position, const Position2d<int> &clip,const SColor &color)
{
	int xPlus = -(ScreenSize.Width>>1);
	float xFact = 1.0f / (ScreenSize.Width>>1);

	int yPlus = ScreenSize.Height-(ScreenSize.Height>>1);
	float yFact = 1.0f / (ScreenSize.Height>>1);

	S3DVertex vtx[4];
	vtx[0] = S3DVertex((position.x + xPlus)*xFact, (yPlus - position.y )*yFact, 1.0f, 0.0f, 0.0f, 0.0f, color, 0.0f, 0.0f); //верх-левый угол
	vtx[1] = S3DVertex((position.x + clip.x + xPlus)*xFact, (yPlus - position.y)*yFact, 1.0f, 0.0f, 0.0f, 0.0f, color, 1.0f, 0.0f); //правый верхний
	vtx[2] = S3DVertex((position.x + clip.x + xPlus)*xFact, (yPlus - position.y - clip.y)*yFact, 1.0f, 0.0f, 0.0f, 0.0f, color, 1.0f, 1.0f); //правый нижний
	vtx[3] = S3DVertex((position.x + xPlus)*xFact, (yPlus - position.y - clip.y)*yFact, 1.0f, 0.0f, 0.0f, 0.0f, color, 0.0f, 1.0f); //нижний левый угол
	
	SHORT indices[6] = {0,1,2,0,2,3};
	pDD->SetFVF(FVF_VERTEX_TEX1);
	setTexture(0,0);
	setRenderStates2DMode(color.getAlpha() < 255, false, false);

	pDD->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, &indices[0], 
								D3DFMT_INDEX16, &vtx[0], 
								sizeof(S3DVertex));

};

void CDirect3D9Render::draw2DImage(const Position2d<int> &position, const Position2d<int> &clip, ITexture* texture, const SColor &color, bool useAlphaChannelOfTexture)
{
	int xPlus = -(ScreenSize.Width>>1);
	float xFact = 1.0f / (ScreenSize.Width>>1);

	int yPlus = ScreenSize.Height-(ScreenSize.Height>>1);
	float yFact = 1.0f / (ScreenSize.Height>>1);

	if (useAlphaChannelOfTexture)
		setRenderStates2DMode(false, true, true);
	else
		setRenderStates2DMode(false, true, false);

	
	S3DVertex vtx[4];
	vtx[0] = S3DVertex((position.x + xPlus)*xFact, (yPlus - position.y )*yFact, 1.0f, 0.0f, 0.0f, 0.0f, color, 0.0f, 0.0f); //верх-левый угол
	vtx[1] = S3DVertex((position.x + clip.x + xPlus)*xFact, (yPlus - position.y)*yFact, 1.0f, 0.0f, 0.0f, 0.0f, color, 1.0f, 0.0f); //правый верхний
	vtx[2] = S3DVertex((position.x + clip.x + xPlus)*xFact, (yPlus - position.y - clip.y)*yFact, 1.0f, 0.0f, 0.0f, 0.0f, color, 1.0f, 1.0f); //правый нижний
	vtx[3] = S3DVertex((position.x + xPlus)*xFact, (yPlus - position.y - clip.y)*yFact, 1.0f, 0.0f, 0.0f, 0.0f, color, 0.0f, 1.0f); //нижний левый угол
	
	SHORT indices[6] = {0,1,2,0,2,3};

	pDD->SetFVF(FVF_VERTEX_TEX1);
	
	setTexture(0,texture);

	pDD->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, &indices[0], 
								D3DFMT_INDEX16, &vtx[0], 
								sizeof(S3DVertex));

};


void CDirect3D9Render::draw2DImage(const Position2d<int> &position, const Position2d<int> &clip, ITexture* texture, const Position2d<int> &soursePos, const Position2d<int> &sourseClip, const SColor &color, bool useAlphaChannelOfTexture)
{
	int xPlus = -(ScreenSize.Width>>1);
	float xFact = 1.0f / (ScreenSize.Width>>1);

	int yPlus = ScreenSize.Height-(ScreenSize.Height>>1);
	float yFact = 1.0f / (ScreenSize.Height>>1);
	float xTexF, yTexF;
	if (texture)
	{
		xTexF = 1/(float)texture->getSize().Width;
		yTexF = 1/(float)texture->getSize().Height;
	};
	Position2d<float> TextCoordUP;
	TextCoordUP.x = xTexF*soursePos.x;
	TextCoordUP.y = yTexF*soursePos.y;

	Position2d<float> TextClipSize;
	TextClipSize.x = xTexF*sourseClip.x;
	TextClipSize.y = yTexF*sourseClip.y;

	if (useAlphaChannelOfTexture)
		setRenderStates2DMode(false, true, true);
	else
		setRenderStates2DMode(false, true, false);

	S3DVertex vtx[4];
	vtx[0] = S3DVertex((position.x + xPlus)*xFact, (yPlus - position.y )*yFact, 1.0f, 0.0f, 0.0f, 0.0f, color, TextCoordUP.x, TextCoordUP.y); //верх-левый угол
	vtx[1] = S3DVertex((position.x + clip.x + xPlus)*xFact, (yPlus - position.y)*yFact, 1.0f, 0.0f, 0.0f, 0.0f, color, TextCoordUP.x+TextClipSize.x, TextCoordUP.y); //правый верхний
	vtx[2] = S3DVertex((position.x + clip.x + xPlus)*xFact, (yPlus - position.y - clip.y)*yFact, 1.0f, 0.0f, 0.0f, 0.0f, color, TextCoordUP.x+TextClipSize.x, TextCoordUP.y+TextClipSize.y); //правый нижний
	vtx[3] = S3DVertex((position.x + xPlus)*xFact, (yPlus - position.y - clip.y)*yFact, 1.0f, 0.0f, 0.0f, 0.0f, color, TextCoordUP.x, TextCoordUP.y+TextClipSize.y); //нижний левый угол
	
	SHORT indices[6] = {0,1,2,0,2,3};

	pDD->SetFVF(FVF_VERTEX_TEX1);
	
	setTexture(0,texture);

	pDD->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, &indices[0], 
								D3DFMT_INDEX16, &vtx[0], 
								sizeof(S3DVertex));

};

void CDirect3D9Render::draw2DImage(const RECT &position, ITexture* texture, const RECT &sourse, const SColor &color, bool useAlphaChannelOfTexture)
{
	Position2d<int> Pos;
	Position2d<int> PosClip;
	Pos.x = position.left;
	Pos.y = position.top;
	PosClip.x = position.right;
	PosClip.y = position.bottom;
	
	Position2d<int> Sourse;
	Position2d<int> SourseClip;
	Sourse.x = sourse.left;
	Sourse.y = sourse.top;
	SourseClip.x = sourse.right;
	SourseClip.y = sourse.bottom;

	draw2DImage(Pos, PosClip,texture, Sourse, SourseClip, color, useAlphaChannelOfTexture);
};
void CDirect3D9Render::drawIndexedTriangleList(const S3DVertex* Vertices,	 int vertexCount, const uShort* indexList, int triangleCount)
{
	pDD->SetFVF(FVF_VERTEX_TEX1);
	pDD->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, vertexCount, 
			triangleCount, indexList, D3DFMT_INDEX16, Vertices,	sizeof(S3DVertex));

};

void CDirect3D9Render::drawIndexedTriangleStrip(S3DVertex *vertices, int vertexCount,  const uShort* indexList,  int indexCount)
{
	pDD->SetFVF(FVF_VERTEX_TEX1);
	pDD->DrawIndexedPrimitiveUP(D3DPT_TRIANGLESTRIP, 0, vertexCount, indexCount-2, &indexList[0], 
								D3DFMT_INDEX16, &vertices[0], 20);
};



void CDirect3D9Render::drawBuffer(SRenderOp Op, int vertexStart, int vertexCount, int indexStart, int primCount)
{

	// Determine rendering operation
	D3DPRIMITIVETYPE primType = D3DPT_TRIANGLELIST;
	//	DWORD primCount = 0;
	switch( Op.Type )
	{
        case OT_POINT_LIST:
			primType = D3DPT_POINTLIST;
//			primCount = (DWORD)(op.useIndexes ? op.indexData->indexCount : op.vertexData->vertexCount);
		break;

		case OT_LINE_LIST:
			primType = D3DPT_LINELIST;
//			primCount = (DWORD)(op.useIndexes ? op.indexData->indexCount : op.vertexData->vertexCount) / 2;
		break;

		case OT_LINE_STRIP:
			primType = D3DPT_LINESTRIP;
//			primCount = (DWORD)(op.useIndexes ? op.indexData->indexCount : op.vertexData->vertexCount) - 1;
			break;

		case OT_TRIANGLE_LIST:
			primType = D3DPT_TRIANGLELIST;
//			primCount = (DWORD)(op.useIndexes ? op.indexData->indexCount : op.vertexData->vertexCount) / 3;
		break;

		case OT_TRIANGLE_STRIP:
			primType = D3DPT_TRIANGLESTRIP;
//			primCount = (DWORD)(op.useIndexes ? op.indexData->indexCount : op.vertexData->vertexCount) - 2;
		break;

		case OT_TRIANGLE_FAN:
			primType = D3DPT_TRIANGLEFAN;
//			primCount = (DWORD)(op.useIndexes ? op.indexData->indexCount : op.vertexData->vertexCount) - 2;
		break;
	};
	
	Op.pDcl->SetDeclaration();
	Op.pVB->SetBufferBinding();
	if (Op.pIB)
	{
		Op.pIB->SetBufferBinding();
		pDD->DrawIndexedPrimitive(primType,vertexStart,0,vertexCount,indexStart,primCount);
	}
	else
		pDD->DrawPrimitive(primType,vertexStart,primCount);
};



IVertexShader* CDirect3D9Render::addVertexShader(LPCTSTR pSrcFile)
{
	IVertexShader* pSh;
	pSh = new CDirect3D9VertexShader(pSrcFile, pDD);
	return pSh;
};


void CDirect3D9Render::setRenderStates2DMode(bool alpha, bool texture, bool alphaChannel)
{
		Matrix4f mat;
		resetAllmaterial = true;
		pDD->SetTransform(D3DTS_VIEW, (D3DMATRIX*)((void*)&mat));
		pDD->SetTransform(D3DTS_WORLD, (D3DMATRIX*)((void*)&mat));
		pDD->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)((void*)&mat));

		pDD->SetRenderState(D3DRS_ZENABLE, FALSE);

		pDD->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		pDD->SetRenderState(D3DRS_LIGHTING, FALSE);
		pDD->SetRenderState(D3DRS_FOGENABLE, FALSE);

		pDD->SetTextureStageState( 1, D3DTSS_COLOROP,   D3DTOP_DISABLE);
		pDD->SetTextureStageState(1, D3DTSS_ALPHAOP,  D3DTOP_DISABLE );

		pDD->SetRenderState( D3DRS_STENCILENABLE, FALSE );
		pDD->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW);

		if (texture)
	{
		pDD->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
		pDD->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
		pDD->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);

		if (alphaChannel)
		{
			pDD->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
			pDD->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			pDD->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );

			pDD->SetTextureStageState (0, D3DTSS_ALPHAOP,  D3DTOP_SELECTARG1 );
			pDD->SetTextureStageState (0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );

			pDD->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			pDD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA); 
			pDD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA ); 
		}
		else
		{
			if (alpha)
			{
				pDD->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG2);
				pDD->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
				pDD->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
				pDD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
				pDD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
			}
			else
			{
				pDD->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
				pDD->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
				pDD->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
				pDD->SetTextureStageState (0, D3DTSS_ALPHAOP,  D3DTOP_DISABLE);
				pDD->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			}
		}

	}
	else
	{
		if (alpha)
		{
			pDD->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
			pDD->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			pDD->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
			pDD->SetTextureStageState (0, D3DTSS_ALPHAOP,  D3DTOP_SELECTARG1);
			pDD->SetTextureStageState (0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE );
			pDD->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			pDD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
		}
		else
		{
			pDD->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
			pDD->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
			pDD->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
			pDD->SetTextureStageState (0, D3DTSS_ALPHAOP,  D3DTOP_DISABLE);
			pDD->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		}
	}
};


void CDirect3D9Render::removeTexture(ITexture* texture)
{
	for (std::vector<SSurface>::iterator it=Textures.begin(); it<Textures.end(); ++it)
	{
		SSurface &Text = *(it);
		if (Text.Surface == texture)
		{
            texture->Release();
            Textures.erase(it);
		}
	}
}

ITexture* CDirect3D9Render::findTexture(std::string Name)
{
	for (std::vector<SSurface>::iterator it=Textures.begin(); it<Textures.end(); ++it)
	{
		SSurface &Text = *(it);
		if (Text.Filename == Name)
		{
			return Text.Surface;
		}
	}
	return 0;
}


void CDirect3D9Render::removeAllTexture()
{
	for (std::vector<SSurface>::iterator it=Textures.begin(); it<Textures.end(); ++it)
	{
		SSurface &Text = *(it);
        Text.Surface->Release();
	}
	Textures.clear();
}


ITexture* CDirect3D9Render::LoadTextureFromFile(char* Name)
{
	if (Name=="") return 0;
	ITexture* Texture = findTexture(Name);
	if (Texture)
	{ 
		return Texture;
	}
	std::ifstream file;
	file.open(Name, std::ios::in | std::ios::binary );
	
	if (file.fail())
	{
		return 0;
	}
	IImageLoader* ImageLoader = createImageLoaderTGA();
	IImage* Image = ImageLoader->loadImage(&file);
	if (Image)
	{
		Texture = new CDirectX9Texture(Image,pDD,ETCF_ALWAYS_32_BIT);
		addTexture(Texture, Name);
	}
	ImageLoader->Release();
	setTexture(0, Texture);

	return Texture;
};


void CDirect3D9Render::addTexture(ITexture* texture, std::string Name)
{
	if (texture)
	{
	//	if (Name!=0)
	//		Name = "";
		SSurface s;
		s.Filename = Name;
		s.Surface = texture;
		Textures.push_back(s);
	}
};

void CDirect3D9Render::setTexture(int stage, ITexture* texture)
{
	if (!texture)
		pDD->SetTexture(stage, 0);
	else
	{
		pDD->SetTexture(stage, ((CDirectX9Texture*)texture)->getDX9Texture());
	}
};

void CDirect3D9Render::setTextureUnitFiltering(uInt unit, TextureFilterOptions tfo)
{
	DWORD tfo_min = D3DTEXF_POINT;
	DWORD tfo_mag = D3DTEXF_POINT;
	DWORD tfo_mip = D3DTEXF_NONE;
	switch (tfo)
	{
        case TFO_NONE:
            tfo_min = D3DTEXF_POINT;
			tfo_mag = D3DTEXF_POINT;
			tfo_mip = D3DTEXF_NONE;
            break;
        case TFO_BILINEAR:
            tfo_min = D3DTEXF_LINEAR;
			tfo_mag = D3DTEXF_LINEAR;
			tfo_mip = D3DTEXF_POINT;
            break;
        case TFO_TRILINEAR:
            tfo_min = D3DTEXF_LINEAR;
			tfo_mag = D3DTEXF_LINEAR;
			tfo_mip = D3DTEXF_LINEAR;
            break;
        case TFO_ANISOTROPIC:
            tfo_min = D3DTEXF_ANISOTROPIC;
			tfo_mag = D3DTEXF_ANISOTROPIC;
			tfo_mip = D3DTEXF_LINEAR;
            break;
	}

	pDD->SetSamplerState(unit, D3DSAMP_MINFILTER, tfo_min);
	pDD->SetSamplerState(unit, D3DSAMP_MAGFILTER, tfo_mag);
	pDD->SetSamplerState(unit, D3DSAMP_MIPFILTER, tfo_mip);
};


void CDirect3D9Render::setMaterial(const SMaterial& material)
{
	CurMaterial = material;
	if (!CurMaterial.Wireframe)
	{
		setTexture(0, CurMaterial.Texture[0]);
		setTexture(1, CurMaterial.Texture[1]);
	}
	else 
	{
		setTexture(0, 0);
		setTexture(1, 0);
	}
	//”становка свойств материала
	if (resetAllmaterial ||
		LastMaterial.AmbientColor != material.AmbientColor ||
		LastMaterial.DiffuseColor != material.DiffuseColor ||
		LastMaterial.SpecularColor != material.SpecularColor ||
		LastMaterial.EmissiveColor != material.EmissiveColor ||
		LastMaterial.Shininess != material.Shininess)
	{
		D3DMATERIAL9 mat;
		mat.Diffuse = colorToD3D(material.DiffuseColor);
		mat.Ambient = colorToD3D(material.AmbientColor);
		mat.Specular = colorToD3D(material.SpecularColor);
		mat.Emissive = colorToD3D(material.EmissiveColor);
		mat.Power = material.Shininess;
		pDD->SetMaterial(&mat);
	}

	RenderMaterial->OnSetMaterial(CurMaterial.MaterialType);

	// fillmode
	if (resetAllmaterial || LastMaterial.Wireframe != material.Wireframe)
	{
		if (material.Wireframe)
			pDD->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		else
			pDD->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	// shademode
/*
	if (LastMaterial.GouraudShading != material.GouraudShading)
	{
		if (material.GouraudShading)
			pDD->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		else
			pDD->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	}

	// lighting
	if (resetAllmaterial || LastMaterial.Lighting != material.Lighting)
	{
		if (material.Lighting)
			pDD->SetRenderState(D3DRS_LIGHTING, TRUE);
		else
			pDD->SetRenderState(D3DRS_LIGHTING, FALSE);
	}

	// zbuffer
	if (resetAllmaterial || LastMaterial.ZBuffer != material.ZBuffer)
	{
		if (material.ZBuffer)
		{
			//pDD->SetRenderState(D3DRS_ZFUNC, D3DCMP_EQUAL);
			pDD->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
			pDD->SetRenderState(D3DRS_ZENABLE, TRUE);
		}
		else
			pDD->SetRenderState(D3DRS_ZENABLE, FALSE);
	}

	// zwrite
	if (resetAllmaterial || LastMaterial.ZWriteEnable != material.ZWriteEnable)
	{
		if (material.ZWriteEnable)
			pDD->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);
		else
			pDD->SetRenderState( D3DRS_ZWRITEENABLE, FALSE);
	}

	// back face culling
	if (resetAllmaterial || LastMaterial.BackfaceCulling != material.BackfaceCulling)
	{
		if (material.BackfaceCulling)
			pDD->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW);
		else
			pDD->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE);
	}

	// fog
	if (resetAllmaterial || LastMaterial.FogEnable != material.FogEnable)
	{
		pDD->SetRenderState(D3DRS_FOGENABLE, material.FogEnable);
	}

	// specular highlights
	if (resetAllmaterial || LastMaterial.Shininess!=material.Shininess)
	{
		bool enable = (material.Shininess!=0.0f);
		pDD->SetRenderState(D3DRS_SPECULARENABLE, enable);
		pDD->SetRenderState(D3DRS_NORMALIZENORMALS, enable);
		pDD->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);
	}

	// normalization
//	if (LastMaterial.NormalizeNormals != material.NormalizeNormals)
	{
//		pID3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS,  material.NormalizeNormals);
	}

	// Bilinear, trilinear, and anisotropic filter
	for (uInt st=0; st<2; ++st)
	{
		setTextureUnitFiltering(st, material.FilterOptions);
	}
	LastMaterial = material;
	resetAllmaterial = false;
};

IVertexBuffer* CDirect3D9Render::addVertexBuffer(void* Vertices, uInt numSize, uInt vertexSise, bool dinamic)
{	
	IVertexBuffer* f;
	f = new CDirect3D9VertexBuffer(numSize, vertexSise, dinamic, pDD);
	f->writeData(0,vertexSise*numSize,Vertices);
	VertexesBuffer.push_back(f);
	return f;

};


IIndexBuffer* CDirect3D9Render::addIndexBuffer(short* Indices, int numIndices, bool dinamic)
{
	IIndexBuffer* f;
	f = new CDirect3D9IndexBuffer(numIndices, dinamic, pDD);
	f->writeData(0,sizeof(short)*numIndices,Indices);
	IndexesBuffer.push_back(f);
	return f;
};

void CDirect3D9Render::removeBuffers()
{
	for (std::vector<IVertexBuffer*>::iterator it=VertexesBuffer.begin();it<VertexesBuffer.end();++it)
	{
		IVertexBuffer* vb = *it;
		if (vb)vb->Release();
	}
	VertexesBuffer.clear();
	
	for (std::vector<IIndexBuffer*>::iterator it=IndexesBuffer.begin();it<IndexesBuffer.end();++it)
	{
		IIndexBuffer* ib = *it;
		if (ib) ib->Release();
	}
	IndexesBuffer.clear();

	for (std::vector<IVertexDeclaration*>::iterator it=VertexDeclaration.begin();it<VertexDeclaration.end();++it)
	{
		IVertexDeclaration* id = *it;
		if (id) id->Release();
	}
	VertexDeclaration.clear();


};

void CDirect3D9Render::registerFrame(uInt time)
{
	Fps.registerFrame(time);
}

int CDirect3D9Render::getFPS()
{
	return Fps.getFPS();
}

void CDirect3D9Render::setTransform(MATRIX matrix_mode, Matrix4f* Mat)
{
	switch (matrix_mode)
	{
		case MATRIX_WORLD:
		{
			pDD->SetTransform(D3DTS_WORLD, (D3DMATRIX*)((void*)Mat));
		}
		return;

		case MATRIX_VIEW:
		{
			pDD->SetTransform(D3DTS_VIEW, (D3DMATRIX*)((void*)Mat));
		}
		return;

		case MATRIX_PROJECTION:
		{
			pDD->SetTransform(D3DTS_PROJECTION, (D3DMATRIX*)((void*)Mat));
		}
		return;
	}
};

void CDirect3D9Render::setAmbientLight(float r, float g, float b)
{
	pDD->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_COLORVALUE(r, g, b, 1.0f));
};

void CDirect3D9Render::setLightingEnabled(bool enabled)
{
	pDD->SetRenderState(D3DRS_LIGHTING,enabled);
};

};

*/