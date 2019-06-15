#include "CTerrainSceneNode.h"
#include "CImageLoaderTGA.h"
#include "../Includes/IRender.h"

namespace Sam3d
{

	CTerrainSceneNode::CTerrainSceneNode(ISceneNode* parent, ISceneManager* mgr, int id, 
					const Vector3f& position, 
					const Vector3f& rotation, 
					const Vector3f& scale):
			ITerrainSceneNode(parent, mgr, id, position, rotation, scale)
	{

	};

	CTerrainSceneNode::~CTerrainSceneNode()
	{
		MeshTerrain->Release();
		Indices.clear();
		IRender* driver = SceneManager->getRender();
		for (int i=0;i<8; i++)
		{	//Удаление материалов
			driver->removeTexture(Material.Texture[i]);
		};
	};


bool CTerrainSceneNode::LoadTerrain(const char* FileName, TerrainOption mOption)
{
	Options = mOption;
	if (!FileName)		return false;
	std::ifstream file;
	file.open(FileName, std::ios::in | std::ios::binary );
	if (file.fail())	return false;

	IImageLoader*  ImageLoader = createImageLoaderTGA();
	IImage* heightMap = ImageLoader->loadImage(&file);

	if (!heightMap)		return false;

	Initialize(heightMap->getDimension().Width, heightMap->getDimension().Height, heightMap);
	

	return true;
};

void CTerrainSceneNode::Initialize(int x,int y, IImage* pHeight)
{
	MeshTerrain = new VertexData();
	MeshTerrain->VertexCount = x*y;
	MeshTerrain->vertexDeclaration = getSceneManager()->getRender()->addVertexDeclaration();
	int offset = 0;
	MeshTerrain->vertexDeclaration->addElement(0, offset, VET_FLOAT3, VES_POSITION);
	offset+= VertexElement::getTypeSize(VET_FLOAT3);
	if (Options.light)
	{
		MeshTerrain->vertexDeclaration->addElement(0, offset, VET_FLOAT3, VES_NORMAL);
		offset+= VertexElement::getTypeSize(VET_FLOAT3);
	};
	if (Options.coloured)
	{
		MeshTerrain->vertexDeclaration->addElement(0, offset, VET_COLOR, VES_COLOR, 0);
		offset+= VertexElement::getTypeSize(VET_COLOR);
	};
	MeshTerrain->vertexDeclaration->addElement(0, offset, VET_FLOAT2, VES_TEXCOORD, 0);
	offset+= VertexElement::getTypeSize(VET_FLOAT2);
	MeshTerrain->vertexDeclaration->addElement(0, offset, VET_FLOAT2, VES_TEXCOORD, 1);
	offset+= VertexElement::getTypeSize(VET_FLOAT2);
	MeshTerrain->vertexDeclaration->UpdateDeclaration();
	
	mPositionBuffer = new float[MeshTerrain->VertexCount*3];
//Построение массива вершин
	TerrainSize = x;
	const VertexElement* poselem = MeshTerrain->vertexDeclaration->findElementBySemantic(VES_POSITION);
	const VertexElement* texelem0 = MeshTerrain->vertexDeclaration->findElementBySemantic(VES_TEXCOORD, 0);
	const VertexElement* texelem1 = MeshTerrain->vertexDeclaration->findElementBySemantic(VES_TEXCOORD, 1);
	
	float* pSysPos = mPositionBuffer;

	uChar* pBase = new uChar[x*y*offset];

	void* pFirstBuffElement = (void*)pBase;

	float height; 
	for ( int j = 0; j < TerrainSize; j++ )
	{
		for ( int i = 0; i < TerrainSize; i++ )
		{
			float *pPos, *pTex0, *pTex1;
			poselem->baseVertexPointerToElement(pBase, &pPos);
			texelem0->baseVertexPointerToElement(pBase, &pTex0);
			texelem1->baseVertexPointerToElement(pBase, &pTex1);
    
			SColor pixelColor(pHeight->getPixel(i,j));
			height = float(pixelColor.getRed() + pixelColor.getGreen() + pixelColor.getBlue())*Scale.y/3;  // scale height 

			*pSysPos++ = *pPos++ = (float) (i) * Scale.x; //x
			*pSysPos++ = *pPos++ = (float) height; // y
			*pSysPos++ = *pPos++ = (float) (j) * Scale.z; //z

			*pTex0++ = (float) i / (float)(Options.pageSize);
			*pTex0++ = (float) j / (float)(Options.pageSize);

			*pTex1++ = ((float) i / (float) (Options.tileSize)) * Options.detailTile;
			*pTex1++ = ((float) j / (float) (Options.tileSize)) * Options.detailTile;
	
			pBase += offset;
		}
    }

	delete pHeight;
	pBufferHardware = getSceneManager()->getRender()->addVertexBuffer(pFirstBuffElement,MeshTerrain->VertexCount,offset, false);
//-------------------------------------------------------------------------		
	generateIndices_STRIP();
	Op.pIB = getSceneManager()->getRender()->addIndexBuffer((short*)&Indices[0],(int)Indices.size(),false);
//-------------------------------------------------------------------------	
	getTransformation().makeIdentity();
	Op.pVB = pBufferHardware;
	Op.Type = OT_TRIANGLE_STRIP;
	Op.pDcl = MeshTerrain->vertexDeclaration;

};


void CTerrainSceneNode::OnPreRender()
{
	SceneManager->registerNodeForRendering(this, SNRT_DEFAULT);
	ISceneNode::OnPreRender();
};

void CTerrainSceneNode::Render()
{
	IRender* driver = SceneManager->getRender();
	driver->setTransform(MATRIX_WORLD, &this->getTransformation());
	driver->setMaterial(Material);
	
	for (int i=0; i<TerrainSize-1; ++i)
		driver->drawBuffer(Op,i*TerrainSize,2*TerrainSize,0,(TerrainSize*2-2));

};

	void CTerrainSceneNode::generateIndices_STRIP()
	{
		//Построение списка индексов
		Indices.resize(2*TerrainSize);
		uShort Index =0;
		for (int i=0; i < TerrainSize; ++i)
		{
			Indices[Index + 0] = _index(i,0);
			Indices[Index + 1] = _index(i,1);
			Index +=2;// Увеличиваем колличество "подготовленных" вершин и т.п.
		}
	};
		
	void CTerrainSceneNode::generateIndices_LIST()
	{
		//Построение списка индексов
		Indices.resize(6*TerrainSize);
		uShort Index =0;
		for (int i=0; i < TerrainSize; ++i)
		{
			Indices[Index + 0] = _index(i,0);
			Indices[Index + 1] = _index(i,1);
			Indices[Index + 2] = _index(i+1,0);
			Indices[Index + 3] = _index(i,1);
			Indices[Index + 4] = _index(i+1,1);
			Indices[Index + 5] = _index(i+1,0);

			Index +=6;// Увеличиваем колличество "подготовленных" вершин и т.п.
		}

	};



};