#pragma once
#include <windows.h>
#include <vector>
#include "../scr/core/Vector3f.h"
#include "../scr/core/S3Dvertex.h"
#include "../Include/ICameraSceneNode.h"

#include "../Include/IRender.h"
#include "../Include/ITimer.h"
#include "../Include/ISceneManager.h"
#include "../Include/ITerrainSceneNode.h"

namespace Sam3d
{

class CSceneManager: public ISceneManager, ISceneNode
{
public:	
	CSceneManager(IRender *render, ITimer* Timer);
	//! destructor
	virtual ~CSceneManager();
	virtual ISceneNode* addSkyBoxNode(ITexture *top, ITexture *bottom, ITexture *left, ITexture *right,
		ITexture *front, ITexture *back, ISceneNode* parent = 0, int id = -1);
	virtual ITerrainSceneNode* addTerrainNode(const char* heightMapFileName, TerrainOption mOption, const Vector3f& position = Vector3f(0,0,0),
									const Vector3f& rotation = Vector3f(0,0,0),	const Vector3f& scale = Vector3f(1.0f, 1.0f, 1.0f), 
									ISceneNode* parent = 0, int id = -1);
	virtual ICameraSceneNode* addCamera(ISceneNode* parent=0, int id = -1);
	//! registers a node for rendering it at a specific time.
	virtual IFont* addFont(char* name, ISceneNode* parent = 0, int id = -1);
	virtual void registerNodeForRendering(ISceneNode* node, E_SCENE_NODE_RENDER_TIME = SNRT_DEFAULT);
	virtual void Render();
	virtual void setCamera(ICameraSceneNode* camera);
	virtual ICameraSceneNode* getCamera();
	virtual IRender* getRender();
	virtual uInt getTime();
	
	virtual bool postInputFromUser(CInput* input);

private:
	
	//”казатель на класс рендера
	IRender* CurRender;
	ITimer* Timer;

	std::vector<ISceneNode*> LightAndCameraList;
	std::vector<ISceneNode*> SkyBoxList;
	std::vector<ISceneNode*> TransparentNodeList;
	
	//јктивна€ камера
	ICameraSceneNode* ActiveCamera;
	Vector3f camTransPos; // Position of camera for transparent nodes.
};

ISceneManager* CreateSceneManager(IRender *render, ITimer* timer);

};
