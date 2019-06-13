#pragma once

#include "IBase.h"
#include "ICameraSceneNode.h"
#include "ICursor.h"
#include "IFont.h"
#include "Input.h"
#include "IRender.h"
#include "ITerrainSceneNode.h"


namespace Sam3d
{



enum E_SCENE_NODE_RENDER_TIME
{
	SNRT_LIGHT_AND_CAMERA,	
	SNRT_SKY_BOX,
	SNRT_DEFAULT,			
	SNRT_SHADOW,			
	SNRT_COUNT				
};

class ISceneNode;
class ITerrainSceneNode;

class ISceneManager: public virtual IBase
{
public:
	//! destructor
	virtual ~ISceneManager() {};
	virtual ISceneNode* addSkyBoxNode(ITexture *top, ITexture *bottom, ITexture *left, ITexture *right,
		ITexture *front, ITexture *back, ISceneNode* parent = 0, int id = -1) = 0;
	virtual ITerrainSceneNode* addTerrainNode(const char* heightMapFileName, TerrainOption mOption, const Vector3f& position = Vector3f(0,0,0),
									const Vector3f& rotation = Vector3f(0,0,0),	const Vector3f& scale = Vector3f(1.0f, 1.0f, 1.0f), 
									ISceneNode* parent = 0, int id = -1) = 0;
	virtual ICameraSceneNode* addCamera(ISceneNode* parent = 0, int id = -1)=0;
	virtual ICameraSceneNode* getCamera() = 0;
	virtual void setCamera(ISceneNode* camera){};
	virtual IFont* addFont(char* name, ISceneNode* parent = 0, int id = -1)=0;
	virtual void registerNodeForRendering(ISceneNode* node, E_SCENE_NODE_RENDER_TIME = SNRT_DEFAULT){};
	virtual void Render()=0;
	virtual IRender* getRender()=0;
	virtual uInt getTime()=0;
	virtual bool postInputFromUser(CInput* input)=0;
};


};