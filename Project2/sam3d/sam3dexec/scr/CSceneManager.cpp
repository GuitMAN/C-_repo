#include "CSceneManager.h"
#include "CCameraFPSNode.h"
#include "CTerrainSceneNode.h"

#include "CFont.h"
#include "CSkyBox.h"

////////////////////////////////////////////////////////////
//Draw - отрисовка сцены
////////////////////////////////////////////////////////////
namespace Sam3d
{

/*CSceneManager::CSceneManager(IRender *render, ITimer* timer):
CurRender(render),ISceneManager(),ISceneNode(0, 0),ActiveCamera(0),
Timer(timer)
{
//	MainConsole->Add(0,"Манеджер сцены создан");
};
*/

CSceneManager::~CSceneManager()
{
	
	removeAll();
//	MainConsole->Add(0,"Манеджер сцены удален");
}


/*ISceneNode* CSceneManager::addSkyBoxNode(ITexture *top, ITexture *bottom, ITexture *left, ITexture *right,
		ITexture *front, ITexture *back, ISceneNode* parent, int id)
{
	ISceneNode* node = new CSkyBox(top, bottom, left, right, 

		front, back, parent, this, id);

	addChild(node);
	return node;
};
*/
ICameraSceneNode*  CSceneManager::addCamera(ISceneNode* parent, int id)
{
	ICameraSceneNode* node = new CCameraFPSNode(parent, this, id);
	setCamera(node);
	addChild(node);
	return node;
};

ITerrainSceneNode* CSceneManager::addTerrainNode(const char* heightMapFileName, TerrainOption mOption,
												 const Vector3f& position,
													const Vector3f& rotation,
													const Vector3f& scale, ISceneNode* parent,int id)
{

	ITerrainSceneNode* terrain = new CTerrainSceneNode(parent, this, id, position, rotation, scale);

	if (!terrain->LoadTerrain(heightMapFileName, mOption))
	{
		terrain->remove();
		return 0;
	}
	addChild(terrain);
	return terrain;
};

IFont*  CSceneManager::addFont(char* name, ISceneNode* parent, int id)
{
/*	IFont* node = new CFont(parent, this, id, CurRender);
	node->Load(name);
	addChild(node);
	return node;
	*/
};



ICameraSceneNode* CSceneManager::getCamera()
{
	return ActiveCamera;
}

void CSceneManager::setCamera(ICameraSceneNode* camera)
{
	if (ActiveCamera)
		ActiveCamera->Release();
	ActiveCamera = camera;
}

void CSceneManager::registerNodeForRendering(ISceneNode* node, E_SCENE_NODE_RENDER_TIME time)
{
	switch(time)
	{
		case SNRT_LIGHT_AND_CAMERA:
			LightAndCameraList.push_back(node);
		break;
		case SNRT_SKY_BOX:
			SkyBoxList.push_back(node);
		break;
		case SNRT_DEFAULT:
			TransparentNodeList.push_back(node);
		break;
	};
};


void CSceneManager::Render()
{
	// calculate camera pos.
	camTransPos.Set(0,0,0);
	if (ActiveCamera)
		camTransPos = ActiveCamera->getPosition();
	OnPreRender();
//	MainRender->deleteAllDynamicLights();

	for (uInt i=0; i<LightAndCameraList.size(); ++i)
		LightAndCameraList[i]->Render();
	LightAndCameraList.clear();

	for (uInt i=0; i<SkyBoxList.size(); ++i)
		SkyBoxList[i]->Render();
	SkyBoxList.clear();

	for (uInt i=0; i<TransparentNodeList.size(); ++i)
		TransparentNodeList[i]->Render();
	TransparentNodeList.clear();
	
//	OnPostRender(Timer->getTime());
};


IRender* CSceneManager::getRender()
{
	return CurRender;
}

uInt CSceneManager::getTime()
{
	return 0; //Timer->getTime();
};

//bool CSceneManager::postInputFromUser(CInput *input)
//{
//	if (ActiveCamera)
//		ActiveCamera->OnInput(input);

//	return true;
//};

//ISceneManager* CreateSceneManager(IRender *render, ITimer* timer)
//{
//	return new CSceneManager(render, timer);
//};


};