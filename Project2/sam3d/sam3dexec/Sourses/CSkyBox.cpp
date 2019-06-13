#include "CSkyBox.h"
#include "../Include/IRender.h"

struct SVertex
{
public:
	SVertex(){};
	SVertex(float x, float y, float z, float u, float v)
	{
		Pos.Set(x,y,z);
		TCoords = Position2d<float>::Position2d(u,v);
	};

	Vector3f Pos;
	Position2d<float> TCoords;
};

SVertex Vertex[24];

namespace Sam3d
{


CSkyBox::CSkyBox(ITexture* top, ITexture* bottom, ITexture* left,
			ITexture* right, ITexture* front, ITexture* back, ISceneNode* parent, ISceneManager* mgr, int id)
			:ISceneNode(parent, mgr, id)
{
	setVisible(true);
	//Заполняем массив индексов
	Indices[0] = 0;
	Indices[1] = 1; 
	Indices[2] = 3; 
	Indices[3] = 2; 


	float onepixel = 0.0f;

	ITexture*  tex = front;
	if (!tex) tex = left;
	if (!tex) tex = back;
	if (!tex) tex = right;
	if (!tex) tex = top;
	if (!tex) tex = bottom;

	if (tex)
		onepixel = 1.0f/(tex->getSize().Width * 1.5f);

	float l = 1.f;
	float t = 1.0f - onepixel;
	float o = 0.0f + onepixel;
	SMaterial mat;
	mat.Lighting = false;
	mat.Wireframe = false;
	mat.ZBuffer = false;
	mat.ZWriteEnable = false;
	mat.FilterOptions = TFO_NONE;
//	mat.AmbientColor = SColor(255,255,255,255);
//	mat.DiffuseColor = SColor(255,255,255,255);

	Mat[0] = mat;
	Mat[0].Texture[0] = front;

	Vertex[0] = SVertex(-l,-l,-l,  o, t);
	Vertex[1] = SVertex( l,-l,-l, t, t);
	Vertex[2] = SVertex( l, l,-l, t, o);
	Vertex[3] = SVertex(-l, l,-l, o, o);
	// create left side
	Mat[1] = mat;
	Mat[1].Texture[0] = left;
	Vertex[4] = SVertex( l,-l,-l, o, t);
	Vertex[5] = SVertex( l,-l, l, t, t);
	Vertex[6] = SVertex( l, l, l, t, o);
	Vertex[7] = SVertex( l, l,-l, o, o);
	// create back side
	Mat[2] = mat;
	Mat[2].Texture[0] = back;
	Vertex[8]  = SVertex( l,-l, l, o, t);
	Vertex[9]  = SVertex(-l,-l, l, t, t);
	Vertex[10] = SVertex(-l, l, l, t, o);
	Vertex[11] = SVertex( l, l, l, o, o);
	// create right side
	Mat[3] = mat;
	Mat[3].Texture[0] = right;
	Vertex[12] = SVertex(-l,-l, l, o, t);
	Vertex[13] = SVertex(-l,-l,-l, t, t);
	Vertex[14] = SVertex(-l, l,-l, t, o);
	Vertex[15] = SVertex(-l, l, l, o, o);
	// create top side
	Mat[4] = mat;
	Mat[4].Texture[0] = top;
	Vertex[16] = SVertex( l, l, l, o, t);
	Vertex[17] = SVertex(-l, l, l, t, t);
	Vertex[18] = SVertex(-l, l,-l, t, o);
	Vertex[19] = SVertex( l, l,-l, o, o);
	// create bottom side
	Mat[5] = mat;
	Mat[5].Texture[0] = bottom;
	Vertex[20] = SVertex( l,-l,-l, o, o);
	Vertex[21] = SVertex(-l,-l,-l, t, o);
	Vertex[22] = SVertex(-l,-l, l, t, t);
	Vertex[23] = SVertex( l,-l, l, o, t);
	IRender* driver = SceneManager->getRender();
	Op.pVB = driver->addVertexBuffer(Vertex, 24, sizeof(SVertex),false);
	Op.pIB = driver->addIndexBuffer((short*)Indices,4,false);
	Op.pDcl = driver->addVertexDeclaration();
	Op.pDcl->addElement(0, 0, VET_FLOAT3, VES_POSITION);
	Op.pDcl->addElement(0, sizeof(float)*3, VET_FLOAT2, VES_TEXCOORD, 0);
	Op.pDcl->UpdateDeclaration();
	Op.Type = OT_TRIANGLE_STRIP;
};


void CSkyBox::OnPreRender()
{
	SceneManager->registerNodeForRendering(this, SNRT_SKY_BOX);
	ISceneNode::OnPreRender();
}

void CSkyBox::Render()
{
	Matrix4f mat;
	ISceneNode* Camera = SceneManager->getCamera();
	if (!Camera) return;
	IRender* driver = SceneManager->getRender();
	mat.setTranslation(Camera->getPosition());
	driver->setTransform(MATRIX_WORLD, &mat);

	for (int i=0; i<6; ++i)
	{
		driver->setMaterial(Mat[i]);
		// Вывод объекта
		driver->drawBuffer(Op,4*i,4,0,2);
	}
};

CSkyBox::~CSkyBox()
{
	ISceneNode* Camera = SceneManager->getCamera();
	IRender* driver = SceneManager->getRender();
	Op.pDcl->Release();
	Op.pVB->Release();
	Op.pIB->Release();
	for (int i=0;i<6; i++)
	{	//Удаление материалов
		for (int j=0;j<8;j++)
			driver->removeTexture(Mat[i].Texture[j]);
	};
};

};