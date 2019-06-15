#include "CCameraFPSNode.h"
#include "CTimer.h"
#include "../Includes/ISceneManager.h"

namespace Sam3d
{
////////////////////////////////////////////////////////////
//Camera - ќрганизаци€ работы камеры
////////////////////////////////////////////////////////////

CCameraFPSNode::CCameraFPSNode(ISceneNode* parent, ISceneManager* mgr, int id): 
ICameraSceneNode(parent, mgr, id, Vector3f(0.0f, 0.0f, 0.0f),	Vector3f(0.0f, 0.0f, 0.0f))
{
	fovy = DEGTORAD(60);	// Field of view, in radians. 
	aspect = 4.0f / 3.0f;	// Aspect ratio. 
	zn = 0.1f;				// value of the near view-plane. 
	zf = 4096.0f;			// Z-value of the far view-plane.

	recalculateProjectionMatrix();

	UpVector.Set(0.0f, 1.0f, 0.0f);
	Target.Set(0,0,1);
	setVisible(true);
	setPosition(Vector3f(0,0,0));
//	Cursor->setPosition(300,300);
/*
	// create default key map
	KeyMap.push_back(SCamKeyMap(0, KEY_UP));
	KeyMap.push_back(SCamKeyMap(1, KEY_DOWN));
	KeyMap.push_back(SCamKeyMap(2, KEY_LEFT));
	KeyMap.push_back(SCamKeyMap(3, KEY_RIGHT));
	KeyMap.push_back(SCamKeyMap(0, KEY_W));
	KeyMap.push_back(SCamKeyMap(1, KEY_S));
	KeyMap.push_back(SCamKeyMap(2, KEY_A));
	KeyMap.push_back(SCamKeyMap(3, KEY_D));
	
	for (int i=0; i<4;++i)CursorKeys[i]=false;
*/
}

CCameraFPSNode::~CCameraFPSNode()
{
}


// ѕрименение вектора движени€ к позиции камеры,
// зависит от скорости движени€ камеры и от прошедшего времени
void CCameraFPSNode::OnPreRender()
{
	IRender* render = SceneManager->getRender();

	render->setTransform(MATRIX_PROJECTION, &Proj);

	//¬ычисл€ем вектор направлени€
	View.makeIdentity();
	View.setInverseRotationDeg(getRotation());
	Matrix4f mat;
	mat.setInverseTranslation(getPosition());
	
	View = View*mat;

	SceneManager->registerNodeForRendering(this, SNRT_LIGHT_AND_CAMERA);
	ISceneNode::OnPreRender();
	//*/
}

void CCameraFPSNode::Render()
{
	IRender* render = SceneManager->getRender();
	render->setTransform(MATRIX_VIEW, &View);
};

void CCameraFPSNode::OnPostRender(uInt timeMs)
{
};

void CCameraFPSNode::moveRelative(const Vector3f& vec)
{
//	Quaternionf q = getRotateQuant();

};

void CCameraFPSNode::recalculateProjectionMatrix()
{
	Proj.buildProjectionMatrixPerspectiveFovLH(fovy, aspect, zn, zf);
};


};